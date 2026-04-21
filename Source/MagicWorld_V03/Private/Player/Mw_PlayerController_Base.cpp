// Copyright JNJ,  All Rights Reserved.


#include "Player/Mw_PlayerController_Base.h"

#include "EnhancedInputSubsystems.h"
#include "Mw_DebugHelper.h"
#include "Input/Mw_EnhancedInputComponent.h"
#include "Input/Mw_InputConfig.h"
#include "Mw_GameplayTags.h"
#include "FunctionLibrary/Mw_BFL_Widget.h"
#include "Items/Component/Mw_ItemComponent.h"
#include "Items/Instances/Mw_ItemInstance.h"
#include "Items/ItemActor/Mw_SpawnedItemActor.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/Mw_HUD.h"
#include "UI/MwWidget/Overlay/Mw_UserWidget_Overlay.h"

AMw_PlayerController_Base::AMw_PlayerController_Base()
{
	PrimaryActorTick.bCanEverTick=true;
	InputConfig = nullptr;
	TraceLength = 500.f;
}

void AMw_PlayerController_Base::BeginPlay()
{
	Super::BeginPlay();
	
	Mw_HUD = UMw_BFL_Widget::GetMwHUD(GetWorld());
}

void AMw_PlayerController_Base::SetupInputComponent()
{
	Super::SetupInputComponent();
	//检测数据资产是否配置了如果没有返回报错
	ensureMsgf(InputConfig,TEXT("Forgot to assign start up data to %s"), *GetName());
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	
	if (!IsValid(InputSubsystem)) return;

	for (FMw_InputMapping& MwInputMapping : InputConfig->InputMappings)
	{
		InputSubsystem->AddMappingContext(MwInputMapping.InputMappingContexts,MwInputMapping.Priority);
	}
	UMw_EnhancedInputComponent* Mw_EnhancedInputComponent = CastChecked<UMw_EnhancedInputComponent>(InputComponent);
	if (!IsValid(Mw_EnhancedInputComponent)) return;

	InitPlayerInput(Mw_EnhancedInputComponent);
}

void AMw_PlayerController_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TraceForItem();
}

void AMw_PlayerController_Base::InitPlayerInput(UMw_EnhancedInputComponent* Mw_EnhancedInputComponent)
{
	TArray<uint32> BindHandles;
	Mw_EnhancedInputComponent->BindNativeAction(InputConfig,Mw_GameplayTags::InputTag_Move,ETriggerEvent::Triggered,this,&ThisClass::Input_Move,false);
	Mw_EnhancedInputComponent->BindNativeAction(InputConfig,Mw_GameplayTags::InputTag_Look,ETriggerEvent::Triggered,this,&ThisClass::Input_Look,false);
	Mw_EnhancedInputComponent->BindNativeAction(InputConfig,Mw_GameplayTags::InputTag_Interact,ETriggerEvent::Started,this,&ThisClass::Input_Interact,false);
	Mw_EnhancedInputComponent->BindNativeAction(InputConfig,Mw_GameplayTags::Input_ToggleInventory,ETriggerEvent::Started,this,&ThisClass::Input_ToggleInventory,false);
	
}

void AMw_PlayerController_Base::Input_Move(const FInputActionValue& InputActionValue)
{
	APawn* MwPawn = GetPawn<APawn>();
	
	if (!IsValid(MwPawn)) return;
	
	AController* Controller = MwPawn ? MwPawn->GetController() : nullptr;
	if (Controller)
	{
		const FVector2D Value = InputActionValue.Get<FVector2D>();
		const FRotator MovementRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);

		if (Value.X != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::RightVector);
			MwPawn->AddMovementInput(MovementDirection, Value.X);
		}

		if (Value.Y != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::ForwardVector);
			MwPawn->AddMovementInput(MovementDirection, Value.Y);
		}
	}
}

void AMw_PlayerController_Base::Input_Look(const FInputActionValue& InputActionValue)
{
	APawn* MwPawn = GetPawn<APawn>();

	if (!MwPawn)
	{
		return;
	}
	
	const FVector2D Value = InputActionValue.Get<FVector2D>();

	if (Value.X != 0.0f)
	{
		MwPawn->AddControllerYawInput(Value.X);
	}

	if (Value.Y != 0.0f)
	{
		MwPawn->AddControllerPitchInput(Value.Y);
	}
}

void AMw_PlayerController_Base::TraceForItem()
{
	// 缓存Overlay引用，避免每帧重复获取
	if (!CachedOverlayWidget.IsValid())
	{
		CachedOverlayWidget = UMw_BFL_Widget::GetUserWidgetOverlay(GetWorld());
	}
	UMw_UserWidget_Overlay* Overlay = CachedOverlayWidget.Get();
	
	if (!IsValid(GEngine) || !IsValid(GEngine->GameViewport)) return;

	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);

	const FVector2D ViewportCenter = ViewportSize / 2.0f;
	FVector TraceStart;
	FVector Forward;
	if (!UGameplayStatics::DeprojectScreenToWorld(this,ViewportCenter,TraceStart,Forward)) return;
	
	const FVector TraceEnd = TraceStart + Forward * TraceLength;
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetPawn()); // 忽略玩家角色
	QueryParams.bTraceComplex = false;  // 使用简单碰撞，提高性能
	
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel( HitResult,TraceStart,TraceEnd,ItemTraceChannel ,QueryParams);
	
	LastActor = ThisActor;
	ThisActor = HitResult.GetActor();
	
	if (!ThisActor.IsValid())
	{
		if (IsValid(UMw_BFL_Widget::GetUserWidgetOverlay(GetWorld())))
		{
			UMw_BFL_Widget::GetUserWidgetOverlay(GetWorld())->HidePickupMessage();
		}
			
	}
	if (ThisActor == LastActor) return;
	
	if (ThisActor.IsValid())
	{
		if (IsValid(UMw_BFL_Widget::GetUserWidgetOverlay(GetWorld())))
		{
			if (ThisActor->Implements<UMw_HighlightItemInterface>())
			{
				IMw_HighlightItemInterface::Execute_HighlightItem(ThisActor.Get());
			}
			// 安全转换为拾取物品Actor并显示提示
			/*if (AMw_SpawnedItemActor* PickupActor = Cast<AMw_SpawnedItemActor>(ThisActor.Get()))
			{
				if (Overlay && PickupActor->ItemInstance)
				{
					Overlay->ShowPickupMessage(PickupActor->ItemInstance->GetItemUseActionText().ToString());
				}
			}*/
			if (UMw_ItemComponent* ItemComponent =  ThisActor->FindComponentByClass<UMw_ItemComponent>())
			{
				if (Overlay && ItemComponent->GetItemInstance())
				{
					Overlay->ShowPickupMessage(ItemComponent->GetItemInstance()->GetItemUseActionText().ToString());
				}
			}
		}
	}
	if (LastActor.IsValid())
	{
		if (IsValid(UMw_BFL_Widget::GetUserWidgetOverlay(GetWorld())))
		{
			if (LastActor->Implements<UMw_HighlightItemInterface>())
			{
				IMw_HighlightItemInterface::Execute_UnHighlightItem(LastActor.Get());
			}
			if (Overlay) Overlay->HidePickupMessage();
		}
	}
}

void AMw_PlayerController_Base::Input_ToggleInventory()
{
	if (!Mw_HUD.IsValid()) return;
	
	Mw_HUD->ToggleInventoryMenu();
}

void AMw_PlayerController_Base::Input_Interact(const FInputActionValue& Value)
{
	if (!ThisActor.IsValid()) return;   // 当前没有高亮任何可拾取物品

	// 尝试转换为拾取物品 Actor
	UMw_ItemComponent* ItemComponent =  ThisActor->FindComponentByClass<UMw_ItemComponent>();
	if (ItemComponent)
	{
		ItemComponent->PickedUp(GetPawn());   // 拾取
	}
}
