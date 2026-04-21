// Copyright JNJ,  All Rights Reserved.


#include "Animinstances/Mw_Anim_Character.h"

#include "AbilitySystemGlobals.h"
#include "Mw_LogChannels.h"
//#include "AbilitySystem/Mw_AbilitySystemComponent.h"
#include "Characters/Mw_CharacterMovementComponent.h"
#include "Characters/Mw_Character_Base.h"

UMw_Anim_Character::UMw_Anim_Character()
{
}

void UMw_Anim_Character::InitializeWithAbilitySystem(UAbilitySystemComponent* ASC)
{
	check(ASC);
	GameplayTagPropertyMap.Initialize(this, ASC);
}

void UMw_Anim_Character::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	if (AActor* OwningActor = GetOwningActor())
	{
		if (UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OwningActor))
		{
			InitializeWithAbilitySystem(ASC);
			UE_LOG(LogMwAbilitySystem, Log, TEXT("ASC initialized successfully"));
		}
		else
		{
			UE_LOG(LogMwAbilitySystem, Warning, TEXT("Failed to get ASC from owning actor"));
		}
	}
}

void UMw_Anim_Character::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	const AMw_Character_Base* Character = Cast<AMw_Character_Base>(GetOwningActor());
	if (!Character)
	{
		return;
	}
	UMw_CharacterMovementComponent* CharMoveComp = CastChecked<UMw_CharacterMovementComponent>(Character->GetCharacterMovement());
	const FMw_CharacterGroundInfo& GroundInfo = CharMoveComp->GetGroundInfo();
	GroundDistance = GroundInfo.GroundDistance;
}
