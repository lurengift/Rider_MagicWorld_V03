// Copyright JNJ,  All Rights Reserved.


#include "UI/MwWidget/Inventory/GridSlot/Mw_UserWidget_InventoryGridSlot.h"

#include "Items/Instances/Mw_ItemInstance.h"
#include "Components/Image.h"

// 弱指针直接用指针赋值要引用头文件
void UMw_UserWidget_InventoryGridSlot::SetInventoryItem(UMw_ItemInstance* InItemInstance)
{
	InventoryItem = InItemInstance;
}

void UMw_UserWidget_InventoryGridSlot::SetUnoccupiedTexture()
{
	GridSlotState = EMw_Inv_GridSlotState::Unoccupied;
	Image_GridSlot->SetBrush(Brush_Unoccupied);
}

void UMw_UserWidget_InventoryGridSlot::SetOccupiedTexture()
{
	GridSlotState = EMw_Inv_GridSlotState::Occupied;
	Image_GridSlot->SetBrush(Brush_Occupied);
}

void UMw_UserWidget_InventoryGridSlot::SetSelectedTexture()
{
	GridSlotState = EMw_Inv_GridSlotState::Selected;
	Image_GridSlot->SetBrush(Brush_Selected);
}

void UMw_UserWidget_InventoryGridSlot::SetGrayedOutTexture()
{
	GridSlotState = EMw_Inv_GridSlotState::GrayedOut;
	Image_GridSlot->SetBrush(Brush_GrayedOut);
}
