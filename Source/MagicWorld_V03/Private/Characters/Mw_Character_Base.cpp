// Copyright JNJ,  All Rights Reserved.


#include "Characters/Mw_Character_Base.h"

#include "AbilitySystem/Mw_AbilitySystemComponent.h"
#include "Characters/Mw_CharacterMovementComponent.h"
#include "Component/Inventory/Mw_InventoryComponent.h"
#include "Components/CapsuleComponent.h"


AMw_Character_Base::AMw_Character_Base(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UMw_CharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = false; // // 不允许 Tick（但默认关闭）
	PrimaryActorTick.bStartWithTickEnabled = false; // 每帧检测初始禁用
	// 勾选并刷新骨骼变换，无论是否渲染，都用于骨骼更新——针对专用服务器
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPose;

	SetNetCullDistanceSquared(900000000.0f);

	// 设置胶囊体的碰撞预设
	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	check(CapsuleComp);
	CapsuleComp->InitCapsuleSize(40.0f, 90.0f);
	
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
	
	MwInventoryComponent = CreateDefaultSubobject<UMw_InventoryComponent>("InventoryComponent");
	
	
	UMw_CharacterMovementComponent* MwMoveComp = CastChecked<UMw_CharacterMovementComponent>(GetCharacterMovement());
	/*MwMoveComp->GravityScale = 1.0f;
	MwMoveComp->GroundFriction = 8.0f;
	MwMoveComp->bUseControllerDesiredRotation = false;
	MwMoveComp->bOrientRotationToMovement = false;
	MwMoveComp->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	MwMoveComp->bAllowPhysicsRotationDuringAnimRootMotion = false;
	MwMoveComp->GetNavAgentPropertiesRef().bCanCrouch = true;
	MwMoveComp->bCanWalkOffLedgesWhenCrouching = true;
	MwMoveComp->SetCrouchedHalfHeight(65.0f);
	MwMoveComp->MaxAcceleration = 2400.0f;
	MwMoveComp->BrakingFrictionFactor = 1.0f;
	MwMoveComp->BrakingFriction = 6.0f;
	MwMoveComp->BrakingDecelerationWalking = 1400.0f;*/
	

}

UMw_AbilitySystemComponent* AMw_Character_Base::GetMwAbilitySystemComponent() const
{
	return MwAbilitySystemComponent;
}

UAbilitySystemComponent* AMw_Character_Base::GetAbilitySystemComponent() const
{
	return GetMwAbilitySystemComponent();
}

void AMw_Character_Base::InitAbilityActorInfo()
{
}



