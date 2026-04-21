// Copyright JNJ,  All Rights Reserved.


#include "UI/WidgetController/Mw_WidgetController_Inventory.h"

#include "AbilitySystem/Mw_AbilitySystemComponent.h"
#include "Component/Inventory/Mw_InventoryComponent.h"

// 应该用于广播当前库存中的所有物品。
void UMw_WidgetController_Inventory::BindCallbacksToDependencies()
{
	AActor* AvatarActor = Mw_AbilitySystemComponent->GetAvatarActor();
	if (!AvatarActor) return;
	
	UMw_InventoryComponent* Inv_Component = AvatarActor->FindComponentByClass<UMw_InventoryComponent>();
	if (!Inv_Component) return;
	
	Inv_Component->NoRoomInInventory.AddDynamic(this,&ThisClass::NoRoomInInventoryController);
	
	Inv_Component->OnInventoryItemAdded.AddLambda(
		[this](UMw_ItemInstance* In_ItemInstance)
	{
		OnInventoryControllerChange.Broadcast(In_ItemInstance);
	});
}

//用于监听未来变化
void UMw_WidgetController_Inventory::BroadcastInitialValues()
{
	AActor* AvatarActor = Mw_AbilitySystemComponent->GetAvatarActor();
	if (!AvatarActor) return;
	
	UMw_InventoryComponent* Inv_Component = AvatarActor->FindComponentByClass<UMw_InventoryComponent>();
	if (!Inv_Component) return;
	
	// 只做初始广播：把当前库存里的所有物品挨个广播出去
	for (UMw_ItemInstance* Item : Inv_Component->GetItemInstances())
	{
		OnInventoryControllerChange.Broadcast(Item);
	}
}

void UMw_WidgetController_Inventory::NoRoomInInventoryController()
{
	OnNoRoomInInventoryController.Broadcast();
}
