// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "Mw_ItemDisplayInfo.generated.h"

class AMw_SpawnedItemActor;

// 物品显示信息
USTRUCT(BlueprintType)
struct FMw_ItemDisplayInfo
{
	GENERATED_BODY()
	// 物品名称
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisplayInfo")
	FText Name;
	// 物品描述
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisplayInfo")
	FText Description;
	// 使用动作文本，比如食物，按某键进行食用
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayInfo")
	FText UseActionText;
	
	// 物品图标
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisplayInfo")
	TSoftObjectPtr<UTexture2D> IconSoftPtr = nullptr;
	// 物品图标 图标占用多少个网格
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisplayInfo")
	FIntPoint IconDimensions = FIntPoint{1,1};
	// 物品图标 间距
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisplayInfo")
	float IconGridPadding = 0.f;
	// 图标网格尺寸
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisplayInfo")
	FIntPoint IconGridDimensions = FIntPoint{50,50};
	
	// 用于在游戏内显示我们物品的3D模型
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisplayInfo")
	TSoftObjectPtr<UStaticMesh> WordStaticMeshSoftPtr = nullptr;
	// 例如用于角色的武器
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisplayInfo")
	TSoftObjectPtr<USkeletalMesh> SkeletalMeshSoftPtr = nullptr;
	// 覆盖世界掉落类
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisplayInfo")
	TSubclassOf<AMw_SpawnedItemActor> OverrideWorldDropClass = nullptr;
};

// 物品游戏玩法信息
USTRUCT(BlueprintType)
struct FMw_ItemGameplayInfo
{
	GENERATED_BODY()
	// 最大堆叠数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayInfo",meta = (ClampMin = 1))
	int32 MaxStackSize = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayInfo")
	bool IsStackable = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayInfo",meta = (ClampMin = 0.0))
	float Weight = 1.0f;
	// 购买价格
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayInfo",meta = (ClampMin = 0.0))
	float Cost = 10.0f;
	// 出售价格
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayInfo",meta = (ClampMin = 0.0))
	float SellCost = 2.0f;
	// 是否商店物品
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayInfo")
	bool IsShopItem = false;
	
	// 是否可消耗 比如药水 使用后要从背包移除
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayInfo")
	bool IsConsumable = false;
	// 能否堆叠

	// 是否绑定角色
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayInfo")
	bool IsBound = false;*/
	// 是否有冷却时间
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayInfo")
	bool HasCoolDown = false;
	// 冷却时间
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayInfo",meta = (ClampMin = 0.0))
	float CoolDown = 0.0f;
	
};

