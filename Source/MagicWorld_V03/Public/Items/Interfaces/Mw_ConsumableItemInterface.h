// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Mw_ConsumableItemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UMw_ConsumableItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MAGICWORLD_V03_API IMw_ConsumableItemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	/**
	 * 使用消耗物品
	 * @param TargetActor 实际使用消耗物品的Actor
	 * @return bool
	 */
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category = Mw_ConsumableItemInterface)
	bool UseConsumeItem(AActor* TargetActor);
	
};
/*BlueprintNativeEvent 
	 * 通过 Execute_ 静态函数调用时，是指在C++中通过 IMw_ConsumableItemInterface::Execute_OnPickup(ItemInstance, PickupUser, Quantity)只会执行最终被覆盖的版本，不会同时执行 C++ 默认实现和蓝图覆写。
	 * 具体行为：
	 *	如果蓝图中覆写了该事件，则执行蓝图中的实现，C++ 的 _Implementation 不会执行。
	 *	如果蓝图中没有覆写，则执行 C++ 中提供的 _Implementation 默认实现。
	*	如果接口函数被标记为 BlueprintNativeEvent，您仍然可以直接调用虚函数 OnPickup，但这样只会执行 C++ 中的默认实现，无法触发蓝图中可能存在的覆写。
	*   而 Execute_OnPickup 会通过虚幻的反射系统，正确地找到并调用最终的实现（无论是 C++ 还是蓝图），保证了多态性。
	 */
/**
 * 只会调用 C++ 默认实现，忽略蓝图覆写
 * ItemInstance->OnPickup(PickupUser, Quantity);
 * 会调用最终实现（C++ 或蓝图）
 * IMw_PickupInterface::Execute_OnPickup(ItemInstance, PickupUser, Quantity);
 */