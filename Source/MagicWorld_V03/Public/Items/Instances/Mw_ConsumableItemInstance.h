// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Mw_ItemInstance.h"
#include "Items/Interfaces/Mw_ConsumableItemInterface.h"
#include "Items/Interfaces/Mw_PickupInterface.h"
#include "Mw_ConsumableItemInstance.generated.h"

/**
 * 消耗品实例
 */
UCLASS()
class MAGICWORLD_V03_API UMw_ConsumableItemInstance : public UMw_ItemInstance,public IMw_ConsumableItemInterface,public IMw_PickupInterface
{
	GENERATED_BODY()
	
public:
	// 因为我在接口上声明了蓝图可实现，那么在C++我想添加一个默认实现那么该接口的函数后面要加_Implementation
	// 也可以在蓝图上重写

	/**
	 * 使用消耗品
	 * @param TargetActor 应用的目标
	 * @return bool
	 */
	UFUNCTION()
	virtual  bool UseConsumeItem_Implementation(AActor* TargetActor) override;
	
	UFUNCTION()
	virtual bool OnPickup_Implementation(AActor* PickupUser, int32 Quantity) override; 
	
};
