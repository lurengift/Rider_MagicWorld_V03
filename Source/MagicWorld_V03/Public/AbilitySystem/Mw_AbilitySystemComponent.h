// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Mw_AbilitySystemComponent.generated.h"


// GE效果AssetTag广播 01 定义广播
DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer&  /*AssetTags*/);

/**
 * 
 */
UCLASS()
class MAGICWORLD_V03_API UMw_AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	UMw_AbilitySystemComponent();
	
	// GE效果AssetTag广播 02 声明广播变量
	FEffectAssetTags EffectAssetTagsDelegate;
};
