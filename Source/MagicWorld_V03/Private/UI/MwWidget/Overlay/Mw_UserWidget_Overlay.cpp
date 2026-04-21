// Copyright JNJ,  All Rights Reserved.


#include "UI/MwWidget/Overlay/Mw_UserWidget_Overlay.h"

#include "FunctionLibrary/Mw_BFL_Widget.h"
#include "UI/MwWidget/Message/Mw_UserWidget_InventoryInfoMessage.h"
#include "UI/WidgetController/Mw_WidgetController_Inventory.h"

void UMw_UserWidget_Overlay::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	if (UMw_WidgetController_Inventory* WidgetController_Inventory = UMw_BFL_Widget::GetWidgetController_InventoryMenu(GetWorld()))
	{
		WidgetController_Inventory->OnNoRoomInInventoryController.AddDynamic(this,&ThisClass::OnNoRoom);
	}
}

void UMw_UserWidget_Overlay::OnNoRoom()
{
	if (!IsValid(InventoryInfoMessage)) return;
	
	InventoryInfoMessage->SetMessage(FText::FromString("No Room In Inventory."));
	
}
