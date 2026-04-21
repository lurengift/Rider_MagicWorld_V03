// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CrossCompilerCommon.h"
#include "UI/MwWidget/Mw_UserWidget_Base.h"
#include "Mw_UserWidget_InventorySlottedItem.generated.h"

class UTextBlock;
class UMw_ItemInstance;
class UImage;
/**
 * 物品网格槽
 */
UCLASS()
class MAGICWORLD_V03_API UMw_UserWidget_InventorySlottedItem : public UMw_UserWidget_Base
{
	GENERATED_BODY()
	
public:
	
	void SetIsStackable(bool bStackable){bIsStackable=bStackable;}
	bool GetIsStackable() const{return bIsStackable;}
	
	void SetImageIconBrush(const FSlateBrush& InBrush) const;
	UImage* GetImageIcon()const{return Image_Icon;}
	
	void SetGridIndex(int32 Index){GridIndex=Index;}
	int32 GetGridIndex()const{return GridIndex;}
	
	void SetGridDimensions(const FIntPoint& Dimensions){GridDimensions = Dimensions;}
	FIntPoint GetGridDimensions()const{return GridDimensions;}
	
	void  SetInventoryItemInstance(UMw_ItemInstance* InItemInstance);
	UMw_ItemInstance* GetInventoryItemInstance() const{return InventoryItemInstance.Get();}
	void UpdateStackCount(int32 StackCount); 
	
private:
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Icon;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_SelectCount;
	// 该网格的索引
	int32 GridIndex;
	// 网格大小
	FIntPoint GridDimensions;
	// 存储物品实例
	TWeakObjectPtr<UMw_ItemInstance> InventoryItemInstance;
	// 是否堆叠
	bool bIsStackable = false;
};
