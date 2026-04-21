// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/MwWidget/Mw_UserWidget_Base.h"
#include "UI/MwWidget/Inventory/Types/Mw_InventoryGridTypes.h"
#include "Mw_UserWidget_InventoryBase.generated.h"

class UMw_ItemComponent;

/**
 * 库存控件基类
 */
UCLASS()
class MAGICWORLD_V03_API UMw_UserWidget_InventoryBase : public UMw_UserWidget_Base
{
	GENERATED_BODY()
	
public:
	/**
	 * (空间/容器)有容纳某物的空间/余地
	 * @param InItemComponent UMw_ItemComponent
	 * @return FInv_SlotAvailabilityResult
	 */
	virtual FInv_SlotAvailabilityResult HasRoomForItem(UMw_ItemComponent* InItemComponent) const { return FInv_SlotAvailabilityResult(); };
	
};
