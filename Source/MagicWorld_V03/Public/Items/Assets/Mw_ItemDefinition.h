// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "MagicWorld_V03/Public/Items/Structures/Mw_ItemDisplayInfo.h"
#include "Mw_ItemDefinition.generated.h"

/**
 * 定义基础物品
 */
UCLASS(BlueprintType,Blueprintable)
class MAGICWORLD_V03_API UMw_ItemDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	
	UMw_ItemDefinition();
	// 基础物品信息
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisplayInfo")
	FMw_ItemDisplayInfo DisplayInfo;
	// 物品类型标签
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classification",meta = (GameplayTagFilter="Item.Type"))
	FGameplayTag ItemTypeTag;
	// 物品分类
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classification",meta = (GameplayTagFilter="Item.Category"))
	FGameplayTag ItemCategoryTag;
	// 物品稀有度标签
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classification",meta = (GameplayTagFilter="Item.Rarity"))
	FGameplayTag ItemRarityTag;
	// 物品游玩信息
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayInfo")
	FMw_ItemGameplayInfo GameplayInfo;
	// 一些额外的标签集合
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta")
	FGameplayTagContainer MetaTags;
	
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
	
	
};
