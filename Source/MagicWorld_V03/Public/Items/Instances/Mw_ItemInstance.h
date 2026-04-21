// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "Mw_ItemInstance.generated.h"

struct FMw_ItemGameplayInfo;
struct FMw_ItemDisplayInfo;
class UMw_ItemDefinition;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnItemStackCountChangeDelegate, UMw_ItemInstance* , Item, int32 , OldStackSize, int32 , CurrentStackSize);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemStackDepleted,UMw_ItemInstance*, Item);
/**
 * 这是游戏中所有物品的基础实例
 */
UCLASS(BlueprintType,Blueprintable)
class MAGICWORLD_V03_API UMw_ItemInstance : public UObject
{
	GENERATED_BODY()
	
public:
	// 物品基础信息
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	TObjectPtr<UMw_ItemDefinition> ItemDefinition;
	
	// 堆叠大小（数量个数）
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	int32 StackCount;

public:
	
	UPROPERTY(BlueprintAssignable, Category = "Item|Events")
	FOnItemStackCountChangeDelegate OnItemStackCountChange;
	
	UPROPERTY(BlueprintAssignable, Category = "Item|Events")
	FOnItemStackDepleted OnItemStackDepleted;
	
	/**
	 * 初始化物品数据
	 * @param InItemDefinition 
	 * @param InStackCount 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category = "Item")
	virtual bool InitializedItem(UMw_ItemDefinition* InItemDefinition, int32 InStackCount = 1);

	/**
	 * 添加堆叠数量
	 * @param AmountToAdd 数量
	 * @return bool
	 */
	UFUNCTION(BlueprintCallable, Category = "Item")
	virtual bool AddToStackCount(int32 AmountToAdd);

	/**
	 * 减少堆叠数量
	 * @param AmountToRemove 数量
	 * @return bool
	 */
	UFUNCTION(BlueprintCallable, Category = "Item")
	virtual bool RemoveFromStackCount(int32 AmountToRemove);
	
	int32 GetTotalStackCount() const{return TotalStackCount;}
	void SetTotalStackCount(int32 InCount) {TotalStackCount = InCount;}
#pragma region	一些辅助类的函数，可以供外部使用

	/**
	 * 获取显示信息
	 * @return FMw_ItemDisplayInfo
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure,Category = "Item")
	FMw_ItemDisplayInfo GetItemDisplayInfo() const;
	/**
	 * 获取物品名称
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure,Category = "Item")
	FText GetItemName() const;
	/**
	 * 获取物品描述
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure,Category = "Item")
	FText GetItemDescription() const;
	/**
	 * 获取使用动作文本，比如食物，按某键进行食用
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure,Category = "Item")
	FText GetItemUseActionText() const;
	/**
	 * 获取图标软引用
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure,Category = "Item")
	TSoftObjectPtr<UTexture2D>  GetItemIconSoft() const;
	/**
	 * 获取图标占用多少个网格
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure,Category = "Item")
	FIntPoint GetItemIconDimensions() const;

	/**
	 * 获取图标网格内边距
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure,Category = "Item")
	float GetItemIconGridPadding() const;

	/**
	 * 获取图标网格尺寸
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure,Category = "Item")
	FIntPoint GetItemIconGridDimensions() const;
	
	
	
	/**
	 * 获取物品类型
	 * @return ItemTypeTag
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure,Category = "Item")
	FGameplayTag GetItemTypeTag() const;


	/**
	 * 获取物品分类
	 * @return ItemTypeTag
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure,Category = "Item")
	FGameplayTag GetItemCategoryTag() const;
	
	/**
	 * 获取物品稀有度
	 * @return ItemRarityTag
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure,Category = "Item")
	FGameplayTag GetItemRarityTag() const;

	
	/**
	 * 获取物品游戏玩法信息
	 * @return FMw_ItemGameplayInfo
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure,Category = "Item")
	FMw_ItemGameplayInfo GetItemGameplayInfo() const;
	
	/**
	 * 获取最大堆栈大小
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item")
	float GetItemMaxStackSize()const;
	
	
	/**
	 * 获取是否可堆叠
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure,Category = "Item")
	bool GetItemIsStackable()const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item")
	float GetItemWeight() const;
	
#pragma endregion

private:
	
	// 总堆叠数
	int32 TotalStackCount = 0;

};
