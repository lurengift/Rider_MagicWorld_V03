// Copyright JNJ,  All Rights Reserved.


#include "FunctionLibrary/Mw_BFL_Widget.h"

#include "Kismet/GameplayStatics.h"
#include "Player/Mw_PlayerController_Base.h"
#include "Player/Mw_PlayerState_Base.h"
#include "UI/HUD/Mw_HUD.h"
#include "UI/WidgetController/Mw_WidgetController_Base.h"
#include "UI/MwWidget/Overlay/Mw_UserWidget_Overlay.h"


int32 UMw_BFL_Widget::GetIndexFromPosition(const FIntPoint& Position, const int32 Columns)
{
	return Position.X + Position.Y * Columns;
}

FIntPoint UMw_BFL_Widget::GetPositionFromIndex(const int32 Index, const int32 Columns)
{
	return FIntPoint(Index % Columns, Index / Columns);
}

AMw_HUD* UMw_BFL_Widget::GetMwHUD(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		return  Cast<AMw_HUD>(PC->GetHUD());

	}
	return nullptr;
}

UMw_UserWidget_Overlay* UMw_BFL_Widget::GetUserWidgetOverlay(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AMw_HUD* MwHUD = Cast<AMw_HUD>(PC->GetHUD()))
		{
			return Cast<UMw_UserWidget_Overlay>(MwHUD->GetOverlayWidget());
		}
	}
	return nullptr;
}

UMw_UserWidget_Base* UMw_BFL_Widget::ToggleInventory(const UObject* WorldContextObject)
{
	// 一个小部件只会存在客户端中，那么第一个
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AMw_HUD* MwHUD = Cast<AMw_HUD>(PC->GetHUD()))
		{
			MwHUD->ToggleInventoryMenu();
			return 	MwHUD->ToggleInventory();
		}
		
	}
	return nullptr;
}

UMw_WidgetController_Inventory* UMw_BFL_Widget::GetWidgetController_InventoryMenu(const UObject* WorldContextObject)
{
	// 一个小部件只会存在客户端中，那么第一个
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		
		if (AMw_HUD* MwHUD = Cast<AMw_HUD>(PC->GetHUD()))
		{
			AMw_PlayerController_Base* MwPC = Cast<AMw_PlayerController_Base>(PC);
			AMw_PlayerState_Base* MwPS = MwPC->GetPlayerState<AMw_PlayerState_Base>();
			UMw_AbilitySystemComponent* MwASC = MwPS->GetMwAbilitySystemComponent();
			UMw_AttributeSet_Base* MwAS = MwPS->GetMwAttributeSet();
			
			const FWidgetControllerParams WcParam(MwPC,MwPS,MwASC,MwAS);
			
			return  MwHUD->GetWidgetController_InventoryMenu(WcParam);
		}
	}
	
	return nullptr;
}
