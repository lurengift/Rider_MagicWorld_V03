// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Mw_ItemInstance.h"
#include "Items/Interfaces/Mw_PickupInterface.h"
#include "Mw_EquippableItemInstance.generated.h"

/**
 * 可装备物品实例类
 */
UCLASS()
class MAGICWORLD_V03_API UMw_EquippableItemInstance : public UMw_ItemInstance,public IMw_PickupInterface
{
	GENERATED_BODY()
	
public:
	// 根据工厂创建的确定的属性变量，例如附魔 属性health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisplayInfo",meta = (GameplayTagFilter = "Attributes"))
	TMap<FGameplayTag,float> Attributes;

	/**
	 * 获取属性值
	 * @param InAttributeTag 
	 * @return float
	 */
	UFUNCTION(BlueprintCallable)
	float GetAttributeValue(const FGameplayTag& InAttributeTag) const;
	
	virtual bool OnPickup_Implementation(AActor* PickupActor, int32 Quantity) override;
};
