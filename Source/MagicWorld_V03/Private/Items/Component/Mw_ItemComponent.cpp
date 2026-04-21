// Copyright JNJ,  All Rights Reserved.


#include "Items/Component/Mw_ItemComponent.h"

#include "Component/Inventory/Mw_InventoryComponent.h"
#include "Items/Factory/Mw_ItemFactory.h"
#include "Items/Instances/Mw_ItemInstance.h"
#include "Items/Interfaces/Mw_PickupInterface.h"
#include "Items/Structures/Mw_ItemDisplayInfo.h"
#include "Utils/Mw_AsyncLoadingHelper.h"


UMw_ItemComponent::UMw_ItemComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

	PickUpMessage = FString("E - Pick Up");
	
	
}

bool UMw_ItemComponent::CreateItem(UStaticMeshComponent* InStaticMeshComponent)
{
	if (!InStaticMeshComponent) return false;
	
	if (!ItemDefinition)
	{
		UE_LOG(LogTemp, Error, TEXT("ItemDefinition is not valid. Cannot spawn item into world."));
		return false;
	}
	UMw_ItemInstance* L_ItemInstance = UMw_ItemFactory::CreateItemFromDefinition(GetWorld(),ItemDefinition,Quantity);
	if (!L_ItemInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("Item Instance is not valid. Cannot spawn item into world."));
		// 0.2秒后 会被垃圾回收
		GetOwner()->SetLifeSpan(0.2f);
		return false;
	}
	ItemInstance = L_ItemInstance;
	return true;
}

void UMw_ItemComponent::InitializeSpawn(UMw_ItemInstance* InItemInstance)
{
	if (!InItemInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("Item Instance is not valid. Cannot spawn item into world."));
		// 0.2秒后 会被垃圾回收
		GetOwner()->SetLifeSpan(0.2f);
		return;
	}
	
	ItemInstance = InItemInstance;
	
	// 在这里调用这个那么在蓝图中我们可以进行一些其他的操作
	OnInitialized();
}

void UMw_ItemComponent::OnInitializedModule(UStaticMeshComponent* InStaticMeshComponent)
{
	if (!ItemInstance)
	{
		return;
	}
	
	// 获取软引用
	/*TSoftObjectPtr<UStaticMesh> WorldMeshSoftPtr = ItemInstance->GetDisplayInfo().WordStaticMeshSoftPtr;
	if (WorldMeshSoftPtr.IsNull())
	{
		UE_LOG(LogTemp, Warning, TEXT("OnInitializedModule: WordStaticMeshSoftPtr is null, cannot load"));
		return;
	}*/

	/*// 使用 FStreamableManager 异步加载
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
	StreamableHandle = StreamableManager.RequestAsyncLoad(
		WorldMeshSoftPtr.ToSoftObjectPath(),
		[this, WorldMeshSoftPtr]()
		{
			// 加载完成后回调（在游戏线程执行）
			if (this && ItemStaticMeshComponent)
			{
				UStaticMesh* LoadedMesh = WorldMeshSoftPtr.Get();
				if (LoadedMesh)
				{
					ItemStaticMeshComponent->SetStaticMesh(LoadedMesh);
					UE_LOG(LogTemp, Log, TEXT("Successfully loaded static mesh for item: %s"), *LoadedMesh->GetName());
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Failed to load static mesh for item"));
				}
			}
		},
		FStreamableManager::DefaultAsyncLoadPriority,
		false, // bManageActiveHandle
		false  // bStartStalled
	);*/
	const FMw_ItemDisplayInfo& DisplayInfo = ItemInstance->GetItemDisplayInfo();

	// 异步加载静态网格
	AsyncLoadSoftPtr<UStaticMesh>(
		DisplayInfo.WordStaticMeshSoftPtr,
		[InStaticMeshComponent](UStaticMesh* LoadedMesh)
		{
			if (LoadedMesh && InStaticMeshComponent)
				InStaticMeshComponent->SetStaticMesh(LoadedMesh);
		},
		this
	);
}

void UMw_ItemComponent::PickedUp(AActor* PickupUser)
{
	OnPickedUp();
	
	if (!PickupUser) return;
	// 1. 调用物品实例的拾取接口（执行额外效果，如音效、成就等）
	bool bContinue = true;
	if (ItemInstance && ItemInstance->Implements<UMw_PickupInterface>())
	{
		bContinue = IMw_PickupInterface::Execute_OnPickup(ItemInstance, PickupUser, Quantity);
	}
	// 如果接口返回 false，表示物品自己处理了所有拾取逻辑，不再执行默认库存添加
	if (!bContinue)
	{
		GetOwner()->Destroy();
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
	GetOwner()->Destroy();
}

