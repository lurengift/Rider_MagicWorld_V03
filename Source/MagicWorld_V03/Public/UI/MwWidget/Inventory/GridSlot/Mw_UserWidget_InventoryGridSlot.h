// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VisualizeTexture.h"
#include "UI/MwWidget/Mw_UserWidget_Base.h"
#include "Mw_UserWidget_InventoryGridSlot.generated.h"

class UMw_ItemInstance;
class UImage;

// 网格槽状态
UENUM(BlueprintType)
enum class EMw_Inv_GridSlotState : uint8
{
	//未被占用的
	Unoccupied,
	// 占用
	Occupied,
	// 被选中的
	Selected,
	// 不可用的
	GrayedOut
};

/**
 * 
 */
UCLASS()
class MAGICWORLD_V03_API UMw_UserWidget_InventoryGridSlot : public UMw_UserWidget_Base
{
	GENERATED_BODY()
	
public:

	/**
	 * 获取网格索引
	 * @return 
	 */
	void SetTileIndex(int32 Index) {TileIndex = Index;}
	/**
	 * 设置网格索引
	 * @param InIndex 
	 */
	int32 GetTileIndex() const {return TileIndex;}
	/**
	 * 获取网格槽状态
	 * @return EMw_Inv_GridSlotState
	 */
	EMw_Inv_GridSlotState GetGridSlotState() const {return GridSlotState;}
	TWeakObjectPtr<UMw_ItemInstance> GetInventoryItemInstance() const {return InventoryItem;}
	void SetInventoryItem(UMw_ItemInstance* InItemInstance);
	int32 GetStackCount() const {return StackCount;}
	void SetStackCount(int32 InStackCount){StackCount = InStackCount;}
	/**
	 * 获取左上角索引
	 * @return 
	 */
	int32 GetUpperLeftIndex() const {return UpperLeftIndex;}
	/**
	 * 设置左上角索引
	 * @param InIndex 
	 */
	void SetUpperLeftIndex(int32 InIndex){UpperLeftIndex=InIndex;}
	/**
	 * 获取网格是否可用
	 * @return 
	 */
	bool GetAvailable() const {return bAvailable;}
	/**
	 * 设置网格是否可用
	 * @param InIsAvailable 
	 */
	void SetAvailable(bool InIsAvailable){bAvailable=InIsAvailable;}
	
	void SetUnoccupiedTexture();
	void SetOccupiedTexture();
	void SetSelectedTexture();
	void SetGrayedOutTexture();
	

private:
	
	UPROPERTY(VisibleAnywhere,  Category = "MagicWorld|ItemGridSlot")
	int32 TileIndex;
	int32 StackCount;
	// 左上角索引
	int32 UpperLeftIndex = INDEX_NONE;
	TWeakObjectPtr<UMw_ItemInstance> InventoryItem;
	// 可用的
	bool bAvailable;
	
	UPROPERTY(EditAnywhere,meta = (BindWidget))
	TObjectPtr<UImage>  Image_GridSlot;
	//未被占用的刷子
	UPROPERTY(EditAnywhere,Category = "MagicWorld|ItemGridSlot")
	FSlateBrush Brush_Unoccupied;
	//被占用的刷子
	UPROPERTY(EditAnywhere,Category = "MagicWorld|ItemGridSlot")
	FSlateBrush Brush_Occupied;
	//被选中的刷子
	UPROPERTY(EditAnywhere,Category = "MagicWorld|ItemGridSlot")
	FSlateBrush Brush_Selected;
	//不可用的刷子
	UPROPERTY(EditAnywhere,Category = "MagicWorld|ItemGridSlot")
	FSlateBrush Brush_GrayedOut;
	
	EMw_Inv_GridSlotState GridSlotState;
	
};
