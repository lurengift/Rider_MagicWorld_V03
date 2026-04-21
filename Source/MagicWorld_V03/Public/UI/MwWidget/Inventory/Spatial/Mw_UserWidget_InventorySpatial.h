// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/MwWidget/Inventory/Mw_UserWidget_InventoryBase.h"
#include "Mw_UserWidget_InventorySpatial.generated.h"

class UWidgetSwitcher;
class UButton;
class UMw_UserWidget_InventoryGrid;
/**
 * 空间库存（管理），指在特定空间位置上存储的库存物品或资源的集合与管理
 */
UCLASS()
class MAGICWORLD_V03_API UMw_UserWidget_InventorySpatial : public UMw_UserWidget_InventoryBase
{
	GENERATED_BODY()
	
public:
	/**
	 * 原生初始化事件处理程序；在原生组件初始化时触发的事件
	 */
	virtual void NativeOnInitialized() override;
	
	virtual FInv_SlotAvailabilityResult HasRoomForItem(UMw_ItemComponent* InItemComponent) const override;
	
private:
	
	// 切换器
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher>	Switcher;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMw_UserWidget_InventoryGrid> Grid_Equippable;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMw_UserWidget_InventoryGrid> Grid_Consumable;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMw_UserWidget_InventoryGrid> Grid_Craftable;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Equippable;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Consumable;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Craftable;
	
	// 显示库存-可装备界面
	UFUNCTION()
	void ShowEquippable();
	// 显示库存-可消耗品界面
	UFUNCTION()
	void ShowConsumable();
	// 显示库存-可制造品界面
	UFUNCTION()
	void ShowCraftable();
	// 禁用按钮
	void DisableButton(UButton* Button);

	/**
	 * 设置活动网格
	 * @param Grid 网格
	 * @param Button 按钮
	 */
	void SetActiveGrid(UMw_UserWidget_InventoryGrid* Grid, UButton* Button);
	

};
