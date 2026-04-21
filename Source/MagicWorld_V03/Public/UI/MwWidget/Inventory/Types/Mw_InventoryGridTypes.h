// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "Mw_InventoryGridTypes.generated.h"

class UMw_ItemInstance;
/**
 * 单一库存槽位
 */
USTRUCT()
struct FInv_SlotAvailability
{
	GENERATED_BODY()
	
	FInv_SlotAvailability(){}
	
	FInv_SlotAvailability(int32 ItemIndex,int32 Room, bool bHasItem): Index(ItemIndex), AmountToFill(Room), bItemAtIndex(bHasItem){}
	
	// 物品存入的索引
	int32 Index = INDEX_NONE;  //默认值为-1
	// 填充多少
	int32 AmountToFill = 0;
	// 索引处的项是否已经有其他物品
	bool bItemAtIndex = false;
};

/**
 * 库存槽位可用性结果
 */
USTRUCT()
struct FInv_SlotAvailabilityResult
{
	GENERATED_BODY()
	
	FInv_SlotAvailabilityResult(){}
	
	TWeakObjectPtr<UMw_ItemInstance> Item;
	
	// 可容纳多少 总待填充房间数
	int32 TotalRoomToFill = 0;
	// 剩余容纳多少
	int32 Remainder = 0;
	// 可堆叠的
	bool bStackable = false;
	
	TArray<FInv_SlotAvailability> SlotAvailabilities;
};
