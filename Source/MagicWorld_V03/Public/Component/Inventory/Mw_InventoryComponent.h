// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "Mw_InventoryComponent.generated.h"


class UMw_UserWidget_InventoryBase;
class UMw_ItemInstance;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnInventoryItemChangeSignature,UMw_ItemInstance*);
// 物品添加失败广播
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNoRoomInInventory);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MAGICWORLD_V03_API UMw_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMw_InventoryComponent();
	
	
	//
	void AddNewItem(UMw_ItemInstance* InItem, int32 InStackCount,int32 Remainder);
	
	void AddStacksToItem(UMw_ItemInstance* InItem, int32 InStackCount,int32 Remainder);

	/**
	 * 尝试添加物品
	 * @param InItemInstance 最开始的物品实例
	 * @param InStackCount 物品最开始的数量
	 * @return 
	 */
	UFUNCTION(BlueprintCallable,Category="MagicWorld|ItemInventory")
	bool TryAddItem(UMw_ItemInstance* InItemInstance, int32 InStackCount = 1);
	
	UFUNCTION(BlueprintCallable,Category="MagicWorld|ItemInventory")
	bool RemoveItemInventory(UMw_ItemInstance* InItemInstance, int32 InStackCount = 1);
	
	/**
	 * 按类型查找第一个项目
	 * @param ItemType FGameplayTag
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure,Category = "Item")
	UMw_ItemInstance* FindFirstItemByType(const FGameplayTag& ItemType) const;
	
	UFUNCTION(BlueprintCallable,Category="MagicWorld|ItemInventory")
	TArray<UMw_ItemInstance*> GetItemInstances() const;
	
	FOnInventoryItemChangeSignature OnInventoryItemAdded;
	FOnInventoryItemChangeSignature OnInventoryItemRemoved;
	
	FNoRoomInInventory NoRoomInInventory;
private:
	
	UPROPERTY(VisibleAnywhere,Category = "MagicWorld|ItemInventory")
	TArray<TObjectPtr<UMw_ItemInstance>> ItemInventorys ;
	
	UPROPERTY()
	TWeakObjectPtr<UMw_UserWidget_InventoryBase> InventoryWidget;
	
	// 最大插槽数量
	UPROPERTY(EditDefaultsOnly, Category="MagicWorld|ItemInventory")
	int32 MaxItemSlots = 10;
	
	/**
	 * 查找可堆叠实例 ,会判断物品的分类
	 * @param InItem UMw_ItemInstance
	 * @return UMw_ItemInstance
	 */
	UMw_ItemInstance* FindStackableInstance(const UMw_ItemInstance* InItem) const;

	/**
	 * 合并到现有堆叠（处理超出上限的情况）
	 * @param Existing 现有
	 * @param InItem 入库物品
	 * @param InStackCount 入库物品数量
	 * @return 
	 */
	bool MergeToExistingStack(UMw_ItemInstance* Existing, UMw_ItemInstance* InItem, int32 InStackCount);

	/**
	 * 添加新实例（支持拆分）
	 * @param InItem 入库物品
	 * @param InStackCount 入库物品数量
	 * @return 
	 */
	bool AddNewItemInstance(UMw_ItemInstance* InItem, int32 InStackCount);

	/**
	 * 属性比较辅助函数
	 * @param A 
	 * @param B 
	 * @param Tolerance 
	 * @return 
	 */
	static bool AreAttributesEqual(const TMap<FGameplayTag, float>& A, const TMap<FGameplayTag, float>& B, float Tolerance = 1e-4f);

	/**
	 *  物品实例复制（深拷贝） 由于 UMw_ItemInstance 是 UObject，不能直接拷贝，需要实现一个复制函数
	 * @param Original 来源
	 * @param NewStackCount 
	 * @return 
	 */
	UMw_ItemInstance* DuplicateItemInstance(UMw_ItemInstance* Original, int32 NewStackCount);
};
