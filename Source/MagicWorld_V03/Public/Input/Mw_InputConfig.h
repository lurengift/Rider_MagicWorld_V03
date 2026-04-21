// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"

#include "Mw_InputConfig.generated.h"

class UInputMappingContext;
class UInputAction;




/**
 *
 * 用于将输入操作映射到游戏玩法输入标签的结构
 */
USTRUCT(BlueprintType)
struct FMw_InputAction
{
	GENERATED_BODY()

public:
	FMw_InputAction()
	{
		InputAction = nullptr;
		InputTag = FGameplayTag::EmptyTag;
	}
	/**
	 * 游戏标签
	 * meta = (Categories = "InputTag") 限定只能选择以InputTag开头的标签
	 **/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	// 输入操作，存储输入操作文件
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	UInputAction* InputAction;

	bool IsValid() const
	{
		return InputTag.IsValid() && InputAction;
	}
};


USTRUCT(BlueprintType)
struct FMw_InputMapping
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputMappingContext> InputMappingContexts;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Priority = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool RegisterWithSettings = true;
};

/**
 * 不可变的数据资产，包含输入配置属性。
 */
UCLASS()
class MAGICWORLD_V03_API UMw_InputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	
	UMw_InputConfig();
	
		
	UFUNCTION(BlueprintCallable, Category = "MagicWorld|Pawn")
	const UInputAction* FindNativeInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = true) const;

	UFUNCTION(BlueprintCallable, Category = "MagicWorld|Pawn")
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = true) const;

	// 增强输入映射
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MagicWorld|InputMappings")
	TArray<FMw_InputMapping> InputMappings;
	
	
	// 所有者使用的输入操作列表。这些输入操作会映射到一个游戏玩法标签，并且必须手动绑定。
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
	TArray<FMw_InputAction> NativeInputActions;

	// 所有者使用的输入操作列表。这些输入操作会映射到游戏玩法标签，并自动与具有匹配输入标签的能力绑定。
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
	TArray<FMw_InputAction> AbilityInputActions;
};
