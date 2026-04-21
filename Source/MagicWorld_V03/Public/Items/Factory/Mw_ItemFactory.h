// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Mw_ItemFactory.generated.h"

class UMw_ConsumableItemDefinition;
class UMw_ConsumableItemInstance;
class UMw_EquippableItemDefinition;
class UMw_EquippableItemInstance;
class AMw_SpawnedItemActor;
class UMw_ItemInstance;
class UMw_ItemDefinition;
/**
 * 物品工厂
 */
UCLASS()
class MAGICWORLD_V03_API UMw_ItemFactory : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	//meta = (WorldContext = "WorldContextObject") 不这样写那么每次使用都要指定 WorldContext 
	/**
	 * 创建所有物品实例
	 * @param WorldConTextObject 世界上下文
	 * @param InItemDefinition 物品定义
	 * @param Quantity 总量
	 * @return 物品实例UMw_ItemInstance
	 */
	UFUNCTION(BlueprintCallable, Category = "Item Create" , meta = (WorldContext = "WorldContextObject"))
	static UMw_ItemInstance* CreateItemFromDefinition(UObject* WorldConTextObject, UMw_ItemDefinition* InItemDefinition, int32 Quantity = 1);

	/**
	 * 创建可装备物品实例
	 * @param WorldConTextObject 世界上下文
	 * @param InEquippableItemDefinition 可装备物品定义
	 * @param Quantity 总量
	 * @return UMw_EquippableItemInstance
	 */
	static UMw_EquippableItemInstance* CreateEquippableItem(UObject* WorldConTextObject,UMw_EquippableItemDefinition* InEquippableItemDefinition,int32 Quantity = 1);

	/**
	 * 创建可消耗物品实例
	 * @param WorldConTextObject 世界上下文
	 * @param InConsumableItemDefinition 可消耗物品定义
	 * @param Quantity 总量
	 * @return UMw_ConsumableItemInstance
	 */
	static UMw_ConsumableItemInstance* CreateConsumableItem(UObject* WorldConTextObject,UMw_ConsumableItemDefinition* InConsumableItemDefinition,int32 Quantity = 1);
	
	UFUNCTION(BlueprintCallable, Category = "Item Create" , meta = (WorldContext = "WorldContextObject"))
	static AMw_SpawnedItemActor* SpawnItemInWorld(UObject* WorldConTextObject, UMw_ItemInstance* InItemInstance,FVector SpawnLocation, FRotator SpawnRotation);
	
};


