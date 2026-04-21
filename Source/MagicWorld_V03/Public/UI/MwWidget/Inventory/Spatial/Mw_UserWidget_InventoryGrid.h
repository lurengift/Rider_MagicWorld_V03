// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UI/MwWidget/Mw_UserWidget_Base.h"
//#include "UI/MwWidget/Inventory/Types/Mw_InventoryGridTypes.h"
#include "Mw_UserWidget_InventoryGrid.generated.h"

class UMw_UserWidget_InventorySlottedItem;
class UMw_ItemInstance;
class UCanvasPanel;
class UMw_UserWidget_InventoryGridSlot;
struct FInv_SlotAvailabilityResult ;
/**
 * 库存网格界面
 */
UCLASS()
class MAGICWORLD_V03_API UMw_UserWidget_InventoryGrid : public UMw_UserWidget_Base
{
	GENERATED_BODY()
	
public:
	
	virtual void NativeOnInitialized() override;
	
	FGameplayTag GetItemCategory() const {return GridItemType;}
	
	FInv_SlotAvailabilityResult HasRoomForItem(const UMw_ItemInstance* InItemInstance) ;

	/**
	 *  暂时作废
	 * @param InItemInstance 
	 * @param InItemTypeTag 
	 */
	void AddItemInstance(UMw_ItemInstance* InItemInstance, FGameplayTag InItemTypeTag);
	
private:
	
	void ConstructGrid();
	UFUNCTION()
	void AddedItem(UMw_ItemInstance* InItemInStance);

	/**
	 * 将项目添加到索引
	 * @param InResult 
	 * @param InNewItemInstance 
	 */
	void AddItemToIndices(const FInv_SlotAvailabilityResult& InResult, UMw_ItemInstance* InItemInstance);
	/**
	 * 检测物品的类别是否匹配
	 * @param Item UMw_ItemInstance
	 * @return bool
	 */
	bool MatchesCategory(const UMw_ItemInstance* Item) const;

	/**
	 * 获取图标绘制尺寸
	 * @param InItemInstance 物品实例
	 * @return 
	 */
	FVector2D GetDrawSize(const UMw_ItemInstance* InItemInstance) const;

	/**
	 * 设置插槽物品图像
	 * @param InItemInstance 物品实例
	 * @param InSlottedItem 插槽控件
	 */
	void SetSlottedItemImage(const UMw_ItemInstance* InItemInstance,const UMw_UserWidget_InventorySlottedItem* InSlottedItem) const;

	/**
	 * 在索引处添加项目
	 * @param InItemInstance 物品实例
	 * @param InIndex 索引
	 * @param bStackable 是否可以堆叠
	 * @param StackAmount 堆叠数量
	 */
	void AddItemAtIndex(UMw_ItemInstance* InItemInstance, const int32 InIndex,const bool bStackable,const int32 StackAmount);
	/**
	 * 创建带槽物品
	 * @param InItemInstance 物品实例
	 * @param bStackable 是否可以堆叠
	 * @param StackAmount 堆叠数量
	 * @param InIndex 索引
	 * @return 
	 */
	UMw_UserWidget_InventorySlottedItem* CreateSlottedItem(UMw_ItemInstance* InItemInstance,const bool bStackable,const int32 StackAmount,int32 InIndex);

	/**
	 * 将带槽物品添加到画布
	 * @param InItemInstance 物品实例
	 * * @param InSlottedItem 插槽控件
	 * @param InIndex 索引
	 */
	void AddSlottedItemToCanvas(UMw_ItemInstance* InItemInstance,UMw_UserWidget_InventorySlottedItem* InSlottedItem,const int32 InIndex);
	/**
	 * 更新网格插槽
	 * @param InItemInstance 物品实例
	 * @param InIndex 索引
	 * @param bStackableItem 是否允许堆叠
	 * @param InStackAmount 堆叠数量
	 */
	void UpdateGridSlots(UMw_ItemInstance* InItemInstance,const int32 InIndex,bool bStackableItem, const int32 InStackAmount);

	/**
	 * 是否已检查索引
	 * @param CheckedIndices 检查的索引
	 * @param InIndex 需要检查的索引
	 * @return 
	 */
	bool IsIndexClaimed(const TSet<int32>& CheckedIndices,const int32 InIndex) const;
	/**
	 * 指定的索引是否可用
	 * @param GridSlot
	 * @param Dimensions
	 * @param InCheckedIndices
	 * @param OutTentativelyClaimed
	 * @param ItemTypeTag
	 * @param InMaxStackSize
	 * @return 
	 */
	bool HasRoomAtIndex(const UMw_UserWidget_InventoryGridSlot* GridSlot,const FIntPoint& Dimensions,
		const TSet<int32>& InCheckedIndices,TSet<int32>& OutTentativelyClaimed,const FGameplayTag& ItemTypeTag,
		const int32 InMaxStackSize);

	/**
	 * 检查槽位约束
	 * @param GridSlot 
	 * @param SubGridSlot 
	 * @param InCheckedIndices 
	 * @param OutTentativelyClaimed 
	 * @param ItemTypeTag 
	 * @param InMaxStackSize 
	 * @return 
	 */
	bool CheckSlotConstraints(const UMw_UserWidget_InventoryGridSlot* GridSlot,const UMw_UserWidget_InventoryGridSlot* SubGridSlot,
		const TSet<int32>& InCheckedIndices,TSet<int32>& OutTentativelyClaimed,const FGameplayTag& ItemTypeTag,
		const int32 InMaxStackSize) const;
	/**
	 * 是否上左插槽
	 * @param GridSlot 
	 * @param SubGridSlot 
	 * @return 
	 */
	bool IsUpperLeftSlot(const UMw_UserWidget_InventoryGridSlot* GridSlot,const UMw_UserWidget_InventoryGridSlot* SubGridSlot) const;
	/**
	 * 是否有效物品
	 * @param GridSlot UMw_UserWidget_InventoryGridSlot
	 * @return 
	 */
	bool HasValidItem(const UMw_UserWidget_InventoryGridSlot* GridSlot) const;
	/**
	 * 物品类型是否匹配
	 * @param InSubItemInstance 
	 * @param ItemTypeTag 
	 * @return 
	 */
	bool DoesItemTypeMatch(const UMw_ItemInstance* InSubItemInstance,const FGameplayTag& ItemTypeTag) const;
	/**
	 * 是否在网格边界内
	 * @param StartIndex 
	 * @param ItemDimensions 
	 * @return 
	 */
	bool IsInGridBounds(const int32 StartIndex,const FIntPoint& ItemDimensions)const;
	/**
	 * 确定插槽的填充量
	 * @param bStackable 是否可以堆叠
	 * @param MaxStackSize 最大堆叠数量
	 * @param AmountToFill 需要填充的数量
	 * @param GridSlot 网格插槽
	 * @return 
	 */
	int32 DetermineFillAmountForSlot(const bool bStackable,const int32 MaxStackSize,const int32 AmountToFill,const UMw_UserWidget_InventoryGridSlot* GridSlot)const;
	/**
	 * 获取槽位现填充数量
	 * @param GridSlot 
	 * @return 
	 */
	int32 GetStackAmount(const UMw_UserWidget_InventoryGridSlot* GridSlot) const;
	// 物品分类 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MagicWorld|UI|Inventory",meta = (AllowPrivateAccess = "true",GameplayTagFilter="Item.Type"))
	FGameplayTag GridItemType;
	
	UPROPERTY()
	TArray<TObjectPtr<UMw_UserWidget_InventoryGridSlot>> GridSlots;
	
	UPROPERTY(EditAnywhere,Category="MagicWorld|UI|Inventory")
	TSubclassOf<UMw_UserWidget_InventoryGridSlot> GridSlotClass;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel;
	
	UPROPERTY(EditAnywhere,Category="MagicWorld|UI|Inventory")
	TSubclassOf<UMw_UserWidget_InventorySlottedItem> SlottedItemClass;
	
	// int32 网格索引， 对应的网格槽
	UPROPERTY()
	TMap<int32,TObjectPtr<UMw_UserWidget_InventorySlottedItem>> SlottedItemMap;
	
	// 行数
	//UPROPERTY(EditAnywhere,  meta = (AllowPrivateAccess = "true"),Category = "MagicWorld|UI|Inventory" )
	UPROPERTY(EditAnywhere, Category = "MagicWorld|UI|Inventory" )
	int32 Rows;
	// 列数
	//UPROPERTY(EditAnywhere,  meta = (AllowPrivateAccess = "true"),Category = "MagicWorld|UI|Inventory")
	UPROPERTY(EditAnywhere, Category = "MagicWorld|UI|Inventory" )
	int32 Columns;
	// 格子大小
	//UPROPERTY(EditAnywhere,  meta = (AllowPrivateAccess = "true"),Category = "MagicWorld|UI|Inventory")
	UPROPERTY(EditAnywhere, Category = "MagicWorld|UI|Inventory" )
	float TileSize;


};
