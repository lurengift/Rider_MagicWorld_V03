// Copyright JNJ,  All Rights Reserved.


#include "AbilitySystem/Mw_AttributeSet_Base.h"

#include "GameplayEffectExtension.h"

UMw_AttributeSet_Base::UMw_AttributeSet_Base()
{
}

void UMw_AttributeSet_Base::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	

	// 这个地方才是实际修改属性值的地方
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(),0.f,GetMaxHealth()));
	}
	
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(),0.f,GetMaxMana()));
	}
	if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(),0.f,GetMaxStamina()));
	}
	
}

void UMw_AttributeSet_Base::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	/*
	 * 这里的NewValue 是怎么来的，这源自于当特定属性发生变化时，由GameplayEffect中的修饰器所执行的计算。
	 * 当然，这个函数在属性被直接设置时也会被调用。但是如果这是来自一个GE效果，该修饰符（modifier）返回的是计算的结果，
	 * 而这里正是接收该结果的地方。当然，我们正在检查其值，进行限制，确保它不会低于零或者超过最大值。
	 * 这里的限制并不会永久性修改修饰符（modifier），这仅仅改变了从查询该修饰符时返回的值。
	 * 如果我们有其他游戏效果需要查询其自身的修改器，它将基于当前值重新计算该值。这就像是数值从未真正被限制过。
	 * 我们对属性在变化之前进行限制，但修饰符会重新计算。GE效果修改值发生在游戏效果已经引用后，我们应该再到PostGameplayEffectExecute
	 * 进行限制，并且无需担心由于我们再次更改它，可能会导致它再次复制到客户端。这样只会因属性值的更改而产生一次复制。
	 * 这里只是限制了查询修改器的值
	 * 
	 */
	Super::PreAttributeChange(Attribute, NewValue);
	// 注意：float& NewValue 通过引用传递的，并不是常理引用。这提示我们可以改变NewValue，而某些的某些东西可以进行改变
	
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue,0.f,GetMaxHealth());
	}
	
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue,0.f,GetMaxMana());
	}
	
	if (Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp(NewValue,0.f,GetMaxStamina());
	}
}
