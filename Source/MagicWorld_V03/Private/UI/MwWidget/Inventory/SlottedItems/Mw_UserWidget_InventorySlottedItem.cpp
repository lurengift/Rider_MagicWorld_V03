// Copyright JNJ,  All Rights Reserved.


#include "UI/MwWidget/Inventory/SlottedItems/Mw_UserWidget_InventorySlottedItem.h"

#include "Items/Instances/Mw_ItemInstance.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UMw_UserWidget_InventorySlottedItem::SetImageIconBrush(const FSlateBrush& InBrush) const
{
	Image_Icon->SetBrush(InBrush);
}

void UMw_UserWidget_InventorySlottedItem::SetInventoryItemInstance(UMw_ItemInstance* InItemInstance)
{
	InventoryItemInstance = InItemInstance;
}

void UMw_UserWidget_InventorySlottedItem::UpdateStackCount(int32 StackCount)
{
	if (StackCount > 0)
	{
		Text_SelectCount->SetVisibility(ESlateVisibility::Visible);
		// AsNumber 数字转文本
		Text_SelectCount->SetText(FText::AsNumber(StackCount));
	}
	else
	{
		Text_SelectCount->SetVisibility(ESlateVisibility::Collapsed);
	}
}
