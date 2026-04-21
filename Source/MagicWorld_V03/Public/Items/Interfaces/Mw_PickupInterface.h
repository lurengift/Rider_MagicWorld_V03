// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Mw_PickupInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UMw_PickupInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MAGICWORLD_V03_API IMw_PickupInterface
{
	GENERATED_BODY()

public:
	
	/**
	 * 拾取时调用，用于执行额外效果（如播放声音、触发任务等）。
	 * 注意：不要在此函数内添加物品到库存，库存添加由调用者统一处理。
	 * @param PickupUser 拾取者
	 * @param Quantity   拾取数量
	 * @return 返回 true 表示正常处理，false 表示阻止后续默认拾取逻辑（谨慎使用）
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Pickup")
	bool OnPickup(AActor* PickupUser, int32 Quantity);
};
