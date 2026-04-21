// Copyright JNJ,  All Rights Reserved.


#include "Characters/Mw_Character_Player.h"

#include "AbilitySystem/Mw_AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/Mw_PlayerController_Base.h"
#include "Player/Mw_PlayerState_Base.h"
#include "UI/HUD/Mw_HUD.h"

AMw_Character_Player::AMw_Character_Player()
{
	// ===== 1. 创建弹簧臂 =====
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());  // 设置对应的各组件
	CameraBoom->TargetArmLength = 400.0f; // 弹簧臂长度(250 - 350)
	CameraBoom->SocketOffset = FVector(0.f,70.f,50.f);
	// 如果鼠标上下移动时整个角色都朝天看 → 检查是否误勾选了“使用Pawn控制旋转”在网格体上？应该只在弹簧臂上勾选
	CameraBoom->bUsePawnControlRotation = true; // 使用Pawn控制旋转(勾选后让相机跟随鼠标/手柄旋转)
	
	// ===== 2. 创建摄像机 =====
	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;  // 使用Pawn控制旋转
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;  // 如果是false那么 鼠标控制不了人物的朝向，如果是true，鼠标的人物跟着鼠标的移动移动转向
	bUseControllerRotationRoll = false;
	
	BaseEyeHeight = 80.0f;
	CrouchedEyeHeight = 50.0f;
}

void AMw_Character_Player::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	InitAbilityActorInfo();
}

void AMw_Character_Player::InitAbilityActorInfo()
{
	AMw_PlayerState_Base* MwPS = GetPlayerState<AMw_PlayerState_Base>();
	
	check(MwPS);
	// 从PlayerState中获取ASC，赋值给PlayerCharacter
	MwAbilitySystemComponent = MwPS->GetMwAbilitySystemComponent();
	// 从PlayerState中获取PS，赋值给PlayerCharacter
	MwAttributeSet = MwPS->GetMwAttributeSet();
	
	// 初始化ASC 指定OwnerActor和AvatarActor
	MwAbilitySystemComponent->InitAbilityActorInfo(MwPS,this);


	
	// 多人游戏中，服务器有所有玩家控制器，客户端自己的和其他的，但是其他的控制器指针是空，所以要检查
	// 将PC,PS,MwAbilitySystemComponent,MwAttributeSet 通过HUD传入到widgetcontroller中
	if (AMw_PlayerController_Base* MwPC = Cast<AMw_PlayerController_Base>(GetController()))
	{
		if (AMw_HUD* MwHud = Cast<AMw_HUD>(MwPC->GetHUD()))
		{
			MwHud->InitOverlay(MwPC,MwPS,MwAbilitySystemComponent,MwAttributeSet);
		}
	}
}
