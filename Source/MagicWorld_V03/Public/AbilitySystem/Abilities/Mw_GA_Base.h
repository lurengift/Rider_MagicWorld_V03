// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Mw_GA_Base.generated.h"

class UMw_AbilitySystemComponent;
/**
 * 定义了一项能力的激活方式。
 */
UENUM(BlueprintType)
enum class EMw_AbilityActivationPolicy : uint8
{
	// 已经分配能力，但通过通过事件（按键等）激活
	OnInputTriggered,
	// 已经分配能力，通过事件（按键等）持续尝试激活该能力
	WhileInputActive,
	// 通过其他事件分配该能力时尝试激活
	OnSpawn
};

/**
 * 该项目所使用的基础游戏玩法能力类别
 */
UCLASS(Abstract)
class MAGICWORLD_V03_API UMw_GA_Base : public UGameplayAbility
{
	GENERATED_BODY()
	friend class UMw_AbilitySystemComponent;   // UMw_AbilitySystemComponent 可以访问UMw_GA_Base私有成员

public:
	UMw_GA_Base();
	/**
	 * 获取激活策略
	 * @return EMw_AbilityActivationPolicy
	 */
	EMw_AbilityActivationPolicy GetActivationPolicy() const { return ActivationPolicy; }

protected:
	// 激活GA的方式
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MagicWorld|Ability Activation")
	EMw_AbilityActivationPolicy ActivationPolicy;

};
