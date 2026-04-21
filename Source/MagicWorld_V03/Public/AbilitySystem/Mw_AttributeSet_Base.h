// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"

#include "Mw_AttributeSet_Base.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class MAGICWORLD_V03_API UMw_AttributeSet_Base : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	
	UMw_AttributeSet_Base();
	
	
#pragma region // Primary Attributes 主要属性
	
	// 生命力 决定血量的高低，也会影响火属性防御力、免疫力
	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Vitality;
	ATTRIBUTE_ACCESSORS(ThisClass,Vitality);
	
	// 集中力 决定专注值的高低、也会影响理智值
	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Concentration;
	ATTRIBUTE_ACCESSORS(ThisClass,Concentration);
	
	// 耐力 决定精力高低，也会影响健壮值，以及可以承受的装备重量上限，重量分为轻中重，轻的时候翻滚的无敌帧相对来说是最长的，跑步的速度和跳跃的高度也是相对快和高，重的时候无法跑步
	UPROPERTY(BlueprintReadOnly,Category = "Primary Attributes")
	FGameplayAttributeData Endurance;
	ATTRIBUTE_ACCESSORS(ThisClass,Endurance);
	
	// 力量 使用重型武器必须的能力值，装备拥有力气加成的武器会提升攻击力，也会影响物理防御力
	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(ThisClass,Strength);
	
	// 敏捷 使用精密武器的必需能力值，装备拥有灵巧加成的武器会提升攻击力，也会影响落下损伤的减伤率，是否容易摔下马背，以及魔法、祷告的使用速度
	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Dexterity;
	ATTRIBUTE_ACCESSORS(ThisClass,Dexterity);
	
	
	// 智力 影响魔法攻击力和法力值
	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(ThisClass,Intelligence);
	
	// 信仰  执行祷告的必需能力值，执行拥有信仰加成的祷告会提升威力
	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Faith;
	ATTRIBUTE_ACCESSORS(ThisClass,Faith);
	
#pragma endregion
	
#pragma region  // Vital Attributes	关键属性

	#pragma region // 属性创建样板代码

	// 属性创建样板代码01
	// 我们希望变量可以复制到客户端，因此它在服务器上发生变化，客户端将获得更新后的值，如果我们通过游戏效果进行修改，我们知道这些效果是预测性的，这意味着他们会在客户端本地被改变，并且服务器会被告知这一变化。
	// 一旦在服务器上被更改，所有其他客户端都需要知道这一变化，所以生命值的复制是非常重要的。因此要使一个变量可复制，我们使用Replicated说明符将其标记为Replicated
	// 但对于属性而言，我们需要使用复制通知（RepNotify），当变量复制时，RepNotify（复制通知）会被自动调用，因此当服务器将该变量复制到客户端时，客户端的RepNotify函数将因此被触发。
	// 因此我们要为生命值设置ReplicatedUsing = OnRep_Health 网络复制 ，创建一个名为OnRep_后接变量名的函数。
	// 
	// 对于任何复制变量，我们必须重写GetLifetimeReplicatedProps()
	// 血量
	UPROPERTY(BlueprintReadOnly,Category = "Vital Attributes")
	FGameplayAttributeData Health;
	// 属性创建样板代码03 属性访问器
	ATTRIBUTE_ACCESSORS(ThisClass,Health);


	#pragma endregion
	


	// 最大血量
	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes") 
	FGameplayAttributeData MaxHealth;
	
	ATTRIBUTE_ACCESSORS(ThisClass,MaxHealth);

	// 魔法值
	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	
	ATTRIBUTE_ACCESSORS(ThisClass,Mana);

	// 最大魔法值
	UPROPERTY(BlueprintReadOnly,Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;
	
	ATTRIBUTE_ACCESSORS(ThisClass,MaxMana);

	// 体力
	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes")
	FGameplayAttributeData Stamina;
	
	ATTRIBUTE_ACCESSORS(ThisClass,Stamina);
	
	// 最大体力
	UPROPERTY(BlueprintReadOnly,Category = "Vital Attributes")
	FGameplayAttributeData MaxStamina;
	
	ATTRIBUTE_ACCESSORS(ThisClass,MaxStamina);
	
	// 装备重量
	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes")
	FGameplayAttributeData Weight;
	
	ATTRIBUTE_ACCESSORS(ThisClass,Weight);
	
	// 最大装备重量
	UPROPERTY(BlueprintReadOnly,Category = "Vital Attributes")
	FGameplayAttributeData MaxWeight;
	
	ATTRIBUTE_ACCESSORS(ThisClass,MaxWeight);

#pragma endregion
	
#pragma region // Combat Attributes 攻击属性
	
	// 攻击力 物理伤害
	UPROPERTY(BlueprintReadOnly, Category = "Combat Attributes")
	FGameplayAttributeData Attack;
	ATTRIBUTE_ACCESSORS(ThisClass,Attack);
	
	// 防御力 物理伤害减免
	UPROPERTY(BlueprintReadOnly,Category = "Combat Attributes")
	FGameplayAttributeData Defense;
	ATTRIBUTE_ACCESSORS(ThisClass,Defense);
	
	// 魔法攻击力 魔法攻击强度
	UPROPERTY(BlueprintReadOnly, Category = "Combat Attributes")
	FGameplayAttributeData MagicAttack;
	ATTRIBUTE_ACCESSORS(ThisClass,MagicAttack);
	
	// 魔法防御力 魔法伤害
	UPROPERTY(BlueprintReadOnly, Category = "Combat Attributes")
	FGameplayAttributeData MagicDefense;
	ATTRIBUTE_ACCESSORS(ThisClass,MagicDefense);
	
#pragma endregion

public:
	
	// 该函数是每当一个GE效果应用完成时都会被调用。
	/**
	 *    时机：在 GameplayEffect 完全执行完毕后调用
	 *	目的：用于处理副作用和高级逻辑
	 *	执行位置：只在服务器上执行（然后复制到客户端） 复杂游戏逻辑 - 只在服务器执行
	 *	主要用途：
	 *	处理死亡逻辑（当生命值<=0时）
	 *	触发事件/通知
	 *	复杂的状态更新
	 *	产生次级效果（如受伤时减少魔法值）
	 * @param Data FGameplayEffectModCallbackData&
	 */
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	/**
	 *   时机：在属性值即将被修改之前调用
	 *	目的：用于限制/修正新的属性值 ,并不是实现最终限制变化，后面还可以进一步计算
	 *	执行位置：在客户端和服务器上都会执行（客户端预测） 简单数值限制 - 客户端也能正确显示
	 *	主要用途：
	 *		数值限制（如确保生命值在0-100之间）
	 *		防止非法值（如负数）
	 *		基于当前状态调整值
	 * @param Attribute FGameplayAttribute& 
	 * @param NewValue 最新地修改后的值
	 */
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	
	
};
