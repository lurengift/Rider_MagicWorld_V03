// Copyright JNJ,  All Rights Reserved.


#include "UI/HUD/Mw_HUD.h"

#include "Mw_DebugHelper.h"
#include "UI/MwWidget/Mw_UserWidget_Base.h"
#include "UI/WidgetController/Mw_WidgetController_Inventory.h"
#include "UI/WidgetController/Mw_WidgetController_Overlay.h"

void AMw_HUD::InitOverlay(AMw_PlayerController_Base* MwPC, AMw_PlayerState_Base* MwPs,
                          UMw_AbilitySystemComponent* MwAsc, UMw_AttributeSet_Base* MwAs)
{
	CreateOverlayWidget(MwPC, MwPs, MwAsc, MwAs);
	CreateInventoryWidget(MwPC, MwPs, MwAsc, MwAs);
}


void AMw_HUD::CreateOverlayWidget(AMw_PlayerController_Base* MwPC, AMw_PlayerState_Base* MwPs,
	UMw_AbilitySystemComponent* MwAsc, UMw_AttributeSet_Base* MwAs)
{
	HUDOwingController = Cast<APlayerController>(GetOwner());
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass 没有选择值，请在HUD的派生类中检查是否有未设置")) //该check会将崩溃记录到日志
	checkf(OverlayControllerClass, TEXT("OverlayWidgetControllerClass 没有选择值，请在HUD的派生类中检查是否有未设置"))

	OverlayWidget = Cast<UMw_UserWidget_Base>(CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass));
	
	if (!OverlayWidget)
	{
		Debug::Print(TEXT("OverlayWidget is valid."),EMwLogType::LogMw,ELogVerbosity::Error);
	}
	const FWidgetControllerParams WidgetControllerParams(MwPC, MwPs, MwAsc, MwAs);
	//初始化控制层实例,确保OverlayController有效
	UMw_WidgetController_Overlay* WidgetControllerOverlay = GetWidgetController_Overlay(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetControllerOverlay);//设置该widget的控制层
	// 广播初始值 05
	// 到这里的时候小部件初始化已经有了MwPC, MwPs, MwAsc, MwAs，此时调用最合适
	WidgetControllerOverlay->BroadcastInitialValues();
	// 控件添加到屏幕
	OverlayWidget->AddToViewport();
	
}

UMw_WidgetController_Overlay* AMw_HUD::GetWidgetController_Overlay(const FWidgetControllerParams& WcParams)
{
	if (OverlayController == nullptr)
	{
		OverlayController = NewObject<UMw_WidgetController_Overlay>(this,OverlayControllerClass);
		OverlayController->SetWidgetControllerParams(WcParams);
		// 将回调绑定到依赖项
		OverlayController->BindCallbacksToDependencies();
	
	}
	
	return OverlayController;
}

void AMw_HUD::CreateInventoryWidget(AMw_PlayerController_Base* MwPC, AMw_PlayerState_Base* MwPs,
						  UMw_AbilitySystemComponent* MwAsc, UMw_AttributeSet_Base* MwAs)
{
	checkf(InventoryWidgetClass, TEXT("InventoryWidgetClass 没有选择值，请在HUD的派生类中检查是否有未设置")) //该check会将崩溃记录到日志
	checkf(InventoryControllerClass, TEXT("InventoryControllerClass 没有选择值，请在HUD的派生类中检查是否有未设置"))

	HUDOwingController = Cast<APlayerController>(GetOwner());
	checkf(HUDOwingController.IsValid(),TEXT("Inventory Component should have a Player Controller as Owner."));
	
	if (!HUDOwingController->IsLocalController()) return;
	
	InventoryWidget = CreateWidget<UMw_UserWidget_Base>(HUDOwingController.Get(), InventoryWidgetClass);
	const FWidgetControllerParams WidgetControllerParams(MwPC, MwPs, MwAsc, MwAs);

	UMw_WidgetController_Inventory* Widget_Inventory = GetWidgetController_InventoryMenu(WidgetControllerParams);
	InventoryWidget->SetWidgetController(Widget_Inventory);
	Widget_Inventory->BroadcastInitialValues();
	
	InventoryWidget->AddToViewport();
	
	CloseInventoryMenu();
}

void AMw_HUD::OpenInventoryMenu()
{
	if (!IsValid(InventoryWidget)) return;
	
	InventoryWidget->SetVisibility(ESlateVisibility::Visible);
	IsShowingInventory = true;
	
	FInputModeGameAndUI InputMode;
	GetOwningPlayerController()->SetInputMode(InputMode);
	GetOwningPlayerController()->SetShowMouseCursor(true);
}

UMw_WidgetController_Inventory* AMw_HUD::GetWidgetController_InventoryMenu(const FWidgetControllerParams& WcParams)
{
	if (InventoryController == nullptr)
	{
		InventoryController = NewObject<UMw_WidgetController_Inventory>(this,InventoryControllerClass);
		InventoryController->SetWidgetControllerParams(WcParams);
		
		InventoryController->BindCallbacksToDependencies();
	}
	
	return InventoryController;
}

void AMw_HUD::CloseInventoryMenu()
{
	if (!IsValid(InventoryWidget)) return;
	
	InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
	IsShowingInventory = false;
	
	FInputModeGameOnly InputMode;
	GetOwningPlayerController()->SetInputMode(InputMode);
	GetOwningPlayerController()->SetShowMouseCursor(false);
}

UMw_UserWidget_Base* AMw_HUD::GetOverlayWidget()
{
	if (!Cast<APlayerController>(GetOwner())->IsLocalController()) return nullptr;	
	
	return OverlayWidget;
}

UMw_UserWidget_Base* AMw_HUD::ToggleInventory()
{
	return nullptr;
}

void AMw_HUD::ToggleInventoryMenu()
{
	if (IsShowingInventory)
	{
		CloseInventoryMenu();
	}
	else
	{
		OpenInventoryMenu();
	}
}

UMw_UserWidget_Base* AMw_HUD::GetInventoryWidget()
{
	checkf(HUDOwingController.IsValid(),TEXT("Inventory Component should have a Player Controller as Owner."));
	if (!HUDOwingController->IsLocalController()) return nullptr;	
	
	return InventoryWidget;
}
