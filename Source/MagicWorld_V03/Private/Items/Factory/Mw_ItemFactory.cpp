// Copyright JNJ,  All Rights Reserved.


#include "Items/Factory/Mw_ItemFactory.h"

#include "Mw_LogChannels.h"
#include "Items/Mw_ItemTags.h"
#include "Items/Assets/Mw_ItemDefinition.h"
#include "Items/Assets/Mw_EquippableItemDefinition.h"
#include "Items/Assets/Mw_ConsumableItemDefinition.h"
#include "Items/Instances/Mw_ConsumableItemInstance.h"
#include "Items/Instances/Mw_EquippableItemInstance.h"
#include "Items/Instances/Mw_ItemInstance.h"
#include "Items/ItemActor/Mw_SpawnedItemActor.h"

UMw_ItemInstance* UMw_ItemFactory::CreateItemFromDefinition(UObject* WorldConTextObject, UMw_ItemDefinition* InItemDefinition,
                                                            int32 Quantity)
{
	if (!WorldConTextObject)
	{
		UE_LOG(LogMwTemp, Error, TEXT("WorldConTextObject is not valid, Cannot create item."));
		return nullptr;
	}
	
	if (!InItemDefinition)
	{
		UE_LOG(LogMwTemp, Error, TEXT("InItemDefinition is not valid, Cannot create item."));
		return nullptr;
	}
	
	const int32 FinalQuantity = FMath::Clamp(Quantity,1,InItemDefinition->GameplayInfo.MaxStackSize);
	
	UMw_ItemInstance* NewItem = nullptr;
	
	if (InItemDefinition->ItemTypeTag.MatchesTagExact(Mw_ItemTags::Item_Type_Equippable))
	{
		
		if (UMw_EquippableItemDefinition* EquippableItemDefinition =Cast<UMw_EquippableItemDefinition>(InItemDefinition))
		{
			NewItem = CreateEquippableItem(WorldConTextObject,EquippableItemDefinition,FinalQuantity);

		}
		
	}else if (InItemDefinition->ItemTypeTag.MatchesTagExact(Mw_ItemTags::Item_Type_Consumable))
	{
		NewItem = NewObject<UMw_ConsumableItemInstance>(WorldConTextObject);
		if (!NewItem->InitializedItem(InItemDefinition,FinalQuantity))
		{
			return nullptr;
		}
		
	}else if (InItemDefinition->ItemTypeTag.MatchesTagExact(Mw_ItemTags::Item_Type_Basic))
	{
		NewItem = NewObject<UMw_ItemInstance>(WorldConTextObject);
		if (!NewItem->InitializedItem(InItemDefinition,FinalQuantity))
		{
			return nullptr;
		}
	}
	else
	{
		UE_LOG(LogMwTemp, Error, TEXT("ItemTypeTag is valid,NewItem Instance failed to create."));
		return nullptr;
	}
	
	
	if (!NewItem)
	{
		UE_LOG(LogMwTemp, Error, TEXT("NewItem Instance failed to create."));
		return nullptr;
	}
	
	
	
	return NewItem;
	
}

UMw_EquippableItemInstance* UMw_ItemFactory::CreateEquippableItem(UObject* WorldConTextObject,
	UMw_EquippableItemDefinition* InEquippableItemDefinition, int32 Quantity)
{
	if (!WorldConTextObject)
	{
		UE_LOG(LogMwTemp, Error, TEXT("WorldConTextObject is not valid, Cannot create EquippableItem."));
		return nullptr;
	}
	
	if (!InEquippableItemDefinition)
	{
		UE_LOG(LogMwTemp, Error, TEXT("InItemDefinition is not valid, Cannot create EquippableItem."));
		return nullptr;
	}
	// 因为UMw_EquippableItemInstance是UObject类型，想要使用和存储需要实例化
	UMw_EquippableItemInstance* NewItem = nullptr;
	NewItem = NewObject<UMw_EquippableItemInstance>(WorldConTextObject);
	
	if (!NewItem)
	{
		UE_LOG(LogMwTemp, Error, TEXT("NewEquippableItem Instance failed to create."));
		return nullptr;
	}
				
	if (!NewItem->InitializedItem(InEquippableItemDefinition,Quantity))
	{
		return nullptr;
	}
	// 通过循环获取物品定义中的所有需要定义的值
	for (auto BaseAttributePair : InEquippableItemDefinition->BaseAttributes)
	{
		float FinalAttributeValue =0.f;
		if (BaseAttributePair.Value.UseValueRange)
		{
			// 根据两个数的区间获取随机一个值赋值
			FinalAttributeValue = FMath::RandRange(BaseAttributePair.Value.MinValue,BaseAttributePair.Value.MaxValue);
			// 如果期望最终值是一个整数RoundToInt四舍五入
			FinalAttributeValue = FMath::RoundToInt(FinalAttributeValue);
		}
		else
		{
			FinalAttributeValue = BaseAttributePair.Value.MaxValue;
		}
		// 为武器实例中的属性值赋值
		NewItem->Attributes.Add(BaseAttributePair.Key,FinalAttributeValue);
	}
	
	return NewItem;
}

UMw_ConsumableItemInstance* UMw_ItemFactory::CreateConsumableItem(UObject* WorldConTextObject,
	UMw_ConsumableItemDefinition* InConsumableItemDefinition, int32 Quantity)
{
	if (!WorldConTextObject) return nullptr;
	
	if (!InConsumableItemDefinition) return nullptr;
	
	UMw_ConsumableItemInstance* NewItem = nullptr;
	
	NewItem = NewObject<UMw_ConsumableItemInstance>(WorldConTextObject);
	
	if (!NewItem)
	{
		UE_LOG(LogMwTemp, Error, TEXT("NewConsumableItem Instance failed to create."));
		return nullptr;
	}
				
	if (!NewItem->InitializedItem(InConsumableItemDefinition,Quantity))
	{
		return nullptr;
	}
	
	return NewItem;
	
}

AMw_SpawnedItemActor* UMw_ItemFactory::SpawnItemInWorld(UObject* WorldConTextObject, UMw_ItemInstance* InItemInstance,
                                                        FVector SpawnLocation, FRotator SpawnRotation)
{
	if (!WorldConTextObject)
	{
		UE_LOG(LogMwTemp, Error, TEXT("WorldConTextObject is not valid, Cannot create item."));
		return nullptr;
	}
	
	if (!InItemInstance)
	{
		UE_LOG(LogMwTemp, Error, TEXT("InItemInstance is not valid, Cannot create item."));
		return nullptr;
	}
	
	UWorld* World = WorldConTextObject->GetWorld();
	if (!World)
	{
		UE_LOG(LogMwTemp, Error, TEXT("World is not valid, Cannot create item."));
		return nullptr;
	}
	
	if (!InItemInstance->ItemDefinition->DisplayInfo.OverrideWorldDropClass)
	{
		UE_LOG(LogMwTemp, Error, TEXT("OverrideWorldDropClass is not valid, Cannot create item."));
		return nullptr;
	}
	
	FActorSpawnParameters SpawnParameters;
	AMw_SpawnedItemActor* SpawnedItemActor = World->SpawnActor<AMw_SpawnedItemActor>(InItemInstance->ItemDefinition->DisplayInfo.OverrideWorldDropClass,SpawnLocation, SpawnRotation,SpawnParameters);
	
	if (!SpawnedItemActor)
	{
		UE_LOG(LogMwTemp, Error, TEXT("SpawnedItemActor is not valid, Cannot create item."));
		return nullptr;
	}
	
	//SpawnedItemActor->InitializeSpawn(InItemInstance);
	return SpawnedItemActor;
}
