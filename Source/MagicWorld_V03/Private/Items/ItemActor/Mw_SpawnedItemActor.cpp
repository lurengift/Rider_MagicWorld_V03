// Copyright JNJ,  All Rights Reserved.


#include "Items/ItemActor/Mw_SpawnedItemActor.h"

#include "Component/Inventory/Mw_InventoryComponent.h"
#include "Items/Component/Mw_ItemComponent.h"
#include "Items/Factory/Mw_ItemFactory.h"
#include "Items/Instances/Mw_ItemInstance.h"
#include "Items/Interfaces/Mw_PickupInterface.h"
#include "Items/Structures/Mw_ItemDisplayInfo.h"
#include "Utils/Mw_AsyncLoadingHelper.h"



// Sets default values
AMw_SpawnedItemActor::AMw_SpawnedItemActor()
{

	PrimaryActorTick.bCanEverTick = false;
	
	ItemStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("ItemStaticMeshComponent");

}


void AMw_SpawnedItemActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (UMw_ItemComponent* ItemComponent =  FindComponentByClass<UMw_ItemComponent>())
	{
		ItemComponent->CreateItem(ItemStaticMeshComponent);
		ItemComponent->OnInitializedModule(ItemStaticMeshComponent);
	}
	
}


/*void AMw_SpawnedItemActor::OnPickedUp(AActor* PickupUser)
{
	/*if (!PickupUser) return;
	// 1. 调用物品实例的拾取接口（执行额外效果，如音效、成就等）
	bool bContinue = true;
	if (ItemInstance && ItemInstance->Implements<UMw_PickupInterface>())
	{
		bContinue = IMw_PickupInterface::Execute_OnPickup(ItemInstance, PickupUser, Quantity);
	}
	// 如果接口返回 false，表示物品自己处理了所有拾取逻辑，不再执行默认库存添加
	if (!bContinue)
	{
		Destroy();
		return;
	}
	
	//2. 唯一一次添加到库存
	if (UMw_InventoryComponent* Inv = PickupUser->FindComponentByClass<UMw_InventoryComponent>())
	{
		bool InvValid =Inv->TryAddItem(ItemInstance, Quantity);
		if (!InvValid)
		{
			//Inv->NoRoomInInventory.Broadcast();
		}
		else
		{// 3. 销毁自身
			//Destroy();
			
		}
	
		
	}
	#1#


}*/


void AMw_SpawnedItemActor::HighlightItem_Implementation()
{
	ItemStaticMeshComponent->SetOverlayMaterial(HighlightMaterial);
}

void AMw_SpawnedItemActor::UnHighlightItem_Implementation()
{
	ItemStaticMeshComponent->SetOverlayMaterial(nullptr);
}
