// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Mw_BFL_Widget.generated.h"

class UMw_WidgetController_Inventory;
class UMw_UserWidget_Base;
class UMw_UserWidget_Overlay;
class AMw_HUD;
/**
 * UI 辅助
 */
UCLASS()
class MAGICWORLD_V03_API UMw_BFL_Widget : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/**
	 * 计算
	 * @param Position 
	 * @param Columns 
	 * @return 
	 */
	static int32 GetIndexFromPosition(const FIntPoint& Position, const int32 Columns);
	
	static FIntPoint GetPositionFromIndex(const int32 Index, const int32 Columns);
	
	UFUNCTION(BlueprintCallable, Category = "MagicWorld|Mw_BFL_Widget")
	static AMw_HUD* GetMwHUD(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, Category = "MagicWorld|Mw_BFL_Widget")
	static UMw_UserWidget_Overlay* GetUserWidgetOverlay(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category="MagicWorld|Mw_BFL_Widget")
	static UMw_UserWidget_Base* ToggleInventory(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category="MagicWorld|Mw_BFL_Widget|WidgetController")
	static UMw_WidgetController_Inventory* GetWidgetController_InventoryMenu(
	const UObject* WorldContextObject);

	/**
	 * 二维数组或二维集合的“对每个元素”循环结构，用于遍历二维数据中的每个元素
	 * @tparam T 
	 * @tparam FuncT 
	 * @param Array 
	 * @param Index 
	 * @param Range2D 
	 * @param GridColumns 
	 * @param Function 
	 */
	template<typename T, typename FuncT>
	static void ForEach2D(TArray<T>& Array,int32 Index,const FIntPoint& Range2D,int32 GridColumns,const FuncT& Function);
};

template<typename T, typename FuncT>
void UMw_BFL_Widget::ForEach2D(TArray<T>& Array,int32 Index,const FIntPoint& Range2D,int32 GridColumns,const FuncT& Function)
{
	for (int32 j = 0 ; j < Range2D.Y ; ++j)
	{
		for (int32 i = 0 ; i < Range2D.X ; ++i)
		{
			const FIntPoint Coordinates = GetPositionFromIndex(Index,GridColumns) + FIntPoint(i,j);
			const int32 TileIndex = GetIndexFromPosition(Coordinates,GridColumns);
			if (Array.IsValidIndex(TileIndex))
			{
				Function(Array[TileIndex]);
			}
		}
	}
}
