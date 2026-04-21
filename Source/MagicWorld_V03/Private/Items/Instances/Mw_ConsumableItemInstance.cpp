// Copyright JNJ,  All Rights Reserved.


#include "Items/Instances/Mw_ConsumableItemInstance.h"

#include "Items/Assets/Mw_ConsumableItemDefinition.h"
#include "Items/Assets/Effects/Mw_ConsumableItemEffect.h"
#include "Kismet/GameplayStatics.h"

bool UMw_ConsumableItemInstance::UseConsumeItem_Implementation(AActor* TargetActor)
{
	if (StackCount <=0) return false;
	
	if (!TargetActor) return false;
	
	// TODO:: 对ASC的检查
	
	UMw_ConsumableItemDefinition* ConsumableItemDefinition = Cast<UMw_ConsumableItemDefinition>(ItemDefinition);
	if (!ConsumableItemDefinition) return false;

	for (auto ConsumableItemEffect : ConsumableItemDefinition->OnConsumeEffects)
	{
		if (!ConsumableItemEffect) continue;
		
		ConsumableItemEffect->ApplyConsumeEffect(TargetActor,this);
		
		if (ConsumableItemEffect->OnConsumeSoundEffect)
		{
			UGameplayStatics::PlaySound2D(TargetActor,ConsumableItemEffect->OnConsumeSoundEffect);
		}
	}
	
	return true;
}

bool UMw_ConsumableItemInstance::OnPickup_Implementation(AActor* PickupUser, int32 Quantity)
{
	return true;
}
