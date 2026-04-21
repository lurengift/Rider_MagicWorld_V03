// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Mw_Anim_Base.h"
#include "GameplayEffectTypes.h"

#include "Mw_Anim_Character.generated.h"

class UAbilitySystemComponent;

/**
 * 该项目所使用的基础游戏动画实例类。
 */
UCLASS()
class MAGICWORLD_V03_API UMw_Anim_Character : public UMw_Anim_Base
{
	GENERATED_BODY()
	
public:
	UMw_Anim_Character();
	
	virtual void InitializeWithAbilitySystem(UAbilitySystemComponent* ASC);

protected:

	virtual void NativeInitializeAnimation() override;
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


	// 可用于映射到蓝图变量的游戏玩法标签。当添加或移除这些标签时，变量将自动更新。应使用这些标签而非手动查询游戏玩法标签。
	UPROPERTY(EditDefaultsOnly, Category = "MagicWorld|MwAnimInstance_CharacterBase|GameplayTags")
	FGameplayTagBlueprintPropertyMap GameplayTagPropertyMap;

	UPROPERTY(BlueprintReadOnly, Category = "MagicWorld|MwAnimInstance_CharacterBase|Character State Data")
	float GroundDistance = -1.0f;
};
