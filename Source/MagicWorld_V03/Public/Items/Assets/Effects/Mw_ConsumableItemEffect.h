// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Mw_ConsumableItemEffect.generated.h"

class UMw_ConsumableItemInstance;
/**
 * 创建消耗效果，我们可以创建一个UObject，它本质是一个数据和逻辑的容器。它可被称为可消耗物品效果。
 */
// Abstract 标记后，指这个类是抽象类，不能直接创建
// EditInlineNew 表示将允许我们在定义中，当我们的UMw_ConsumableItemDefinition的数组有属性的时候，
// 将允许我们创建一个非常具体的可消耗物品效果实例，并在定义内部编辑属性
UCLASS(Abstract,Blueprintable,BlueprintType,EditInlineNew)
class MAGICWORLD_V03_API UMw_ConsumableItemEffect : public UObject
{
	GENERATED_BODY()
	
public:
	
	// 效果名称
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;
	// 效果描述
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine))  //meta = (MultiLine) 单行改为多行
	FText Description;
	// 消耗时声音效果
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USoundBase> OnConsumeSoundEffect;
	
	// BlueprintNativeEvent 蓝图原生事件,允许将函数暴露给蓝图，可以在蓝图中实际编写需要发生的事情，并且可以在蓝图中完成
	/**
	 * 应用消耗品效果
	 * @param TagetActor AActor
	 * @param InConsumableItemInstance 可消耗物品实例
	 * @return bool
	 */
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category = "ConsumableItemDefinition")
	bool ApplyConsumeEffect(AActor* TagetActor,UMw_ConsumableItemInstance* InConsumableItemInstance);


};
