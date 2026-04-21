// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Mw_WidgetController_Base.h"
#include "Mw_WidgetController_Inventory.generated.h"

class UMw_ItemInstance;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnInventoryControllerChangeSignature,UMw_ItemInstance*);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNoRoomInInventoryController);

/**
 * 
 */
UCLASS(Blueprinttype,Blueprintable)
class MAGICWORLD_V03_API UMw_WidgetController_Inventory : public UMw_WidgetController_Base
{
	GENERATED_BODY()
	
public:
	/**
	 * 将回调绑定到依赖项
	 */
	virtual void BindCallbacksToDependencies() override;
	
	
	/**
	 * 广播初始值
	 */
	virtual void BroadcastInitialValues() override;
	
	//UPROPERTY( BlueprintAssignable ,Category = "MagicWorld|InventoryControllerChange")
	FOnInventoryControllerChangeSignature OnInventoryControllerChange;
	
	// 没有空间的广播
	FNoRoomInInventoryController OnNoRoomInInventoryController;
	
private:
	/**
	 * 没有控件的回调函数
	 */
	UFUNCTION()
	void NoRoomInInventoryController();
};
