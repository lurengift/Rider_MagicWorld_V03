// Copyright JNJ,  All Rights Reserved.


#include "UI/MwWidget/Inventory/Spatial/Mw_UserWidget_InventorySpatial.h"

#include "Mw_DebugHelper.h"
#include "Component/Inventory/Mw_InventoryComponent.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "FunctionLibrary/Mw_BFL_Widget.h"
#include "Items/Mw_ItemTags.h"
#include "Items/Instances/Mw_ItemInstance.h"
#include "UI/MwWidget/Inventory/Spatial/Mw_UserWidget_InventoryGrid.h"
#include "UI/WidgetController/Mw_WidgetController_Inventory.h"

void UMw_UserWidget_InventorySpatial::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	// 绑定按钮回调
	Button_Equippable->OnClicked.AddDynamic(this,&ThisClass::ShowEquippable);
	Button_Consumable->OnClicked.AddDynamic(this,&ThisClass::ShowConsumable);
	Button_Craftable->OnClicked.AddDynamic(this,&ThisClass::ShowCraftable);
	
	// 设置打开界面后的默认Grid
	ShowEquippable();
}

FInv_SlotAvailabilityResult UMw_UserWidget_InventorySpatial::HasRoomForItem(UMw_ItemInstance* Item) const
{
	if (!Item) return FInv_SlotAvailabilityResult();

	FGameplayTag ItemType = Item->GetItemTypeTag();
	// MatchesTag(Tag)：检查当前标签是否与指定标签相同或是其子标签（层级匹配）。
	// MatchesTagExact(Tag)：检查当前标签是否与指定标签完全相同（不考虑层级）。
	if (ItemType.MatchesTagExact(Mw_ItemTags::Item_Type_Equippable))
	{
		return Grid_Equippable->HasRoomForItem(Item);
	}
	else if (ItemType.MatchesTagExact(Mw_ItemTags::Item_Type_Consumable))
	{
		return Grid_Consumable->HasRoomForItem(Item);
	}
	else if (ItemType.MatchesTagExact(Mw_ItemTags::Item_Type_Craftable))
	{
		return Grid_Craftable->HasRoomForItem(Item);
	}
	else
	{
		Debug::Print(TEXT("Item does not have a valid Item type."), EMwLogType::LogMwTemp, ELogVerbosity::Error, true);
		return FInv_SlotAvailabilityResult();
	}
}

void UMw_UserWidget_InventorySpatial::ShowEquippable()
{
	SetActiveGrid(Grid_Equippable,Button_Equippable);
	
}

void UMw_UserWidget_InventorySpatial::ShowConsumable()
{
	SetActiveGrid(Grid_Consumable,Button_Consumable);
}

void UMw_UserWidget_InventorySpatial::ShowCraftable()
{
	SetActiveGrid(Grid_Craftable,Button_Craftable);
}

void UMw_UserWidget_InventorySpatial::DisableButton(UButton* Button)
{
	Button_Equippable->SetIsEnabled(true);
	Button_Consumable->SetIsEnabled(true);
	Button_Craftable->SetIsEnabled(true);
	Button->SetIsEnabled(false);
}

void UMw_UserWidget_InventorySpatial::SetActiveGrid(UMw_UserWidget_InventoryGrid* Grid, UButton* Button)
{
	DisableButton(Button);
	
	Switcher->SetActiveWidget(Grid);
}

