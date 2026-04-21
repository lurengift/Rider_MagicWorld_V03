// Copyright JNJ,  All Rights Reserved.


#include "Player/Mw_PlayerState_Base.h"

#include "AbilitySystem/Mw_AbilitySystemComponent.h"
#include "AbilitySystem/Mw_AttributeSet_Base.h"
#include "Player/Mw_PlayerController_Base.h"

AMw_PlayerState_Base::AMw_PlayerState_Base()
{
	MwAbilitySystemComponent = CreateDefaultSubobject<UMw_AbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	
	MwAttributeSet = CreateDefaultSubobject<UMw_AttributeSet_Base>("MwAttributeSet");
}

AMw_PlayerController_Base* AMw_PlayerState_Base::GetMwPlayerControllerBase() const
{
	return Cast<AMw_PlayerController_Base>(GetOwner());
}

UAbilitySystemComponent* AMw_PlayerState_Base::GetAbilitySystemComponent() const
{
	return GetMwAbilitySystemComponent();
}
