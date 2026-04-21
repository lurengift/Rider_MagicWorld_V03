// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Mw_ItemDefinition.h"
#include "Mw_ConsumableItemDefinition.generated.h"


class UMw_ConsumableItemEffect;
/**
 * 消耗品定义
 * 具有一次性效果，并将应用一系列效果
 */
UCLASS()
class MAGICWORLD_V03_API UMw_ConsumableItemDefinition : public UMw_ItemDefinition
{
	GENERATED_BODY()
	
public:
	UMw_ConsumableItemDefinition();
	
	// 创建消耗效果，我们可以创建一个UObject，它本质是一个数据和逻辑的容器。它可被称为可消耗物品效果。
	// Instanced 表示当我们创建一个新的实例时的这个UMw_ConsumableItemEffect
	// 并且它存储在这个OnConsumeEffects数组中，它将是一个有效对象，会被存储在这里
	
	// 一个消耗品效果的数组
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Instanced)    
	TArray<TObjectPtr<UMw_ConsumableItemEffect>> OnConsumeEffects;
	
};

/**
 * 消耗品效果是你定义的任务在使用此物品时应该发生的事情。
 * 可以是播放音效、可以播放视觉效果、可以是施加增益效果、可以将你的角色传输到随机位置。
 * 如果使用GAS，可以将GAS作为一个消耗品效果添加、并实际添加到你的物品定义中。
 *
 */