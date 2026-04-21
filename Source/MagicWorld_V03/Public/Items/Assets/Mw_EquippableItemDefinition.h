// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Mw_ItemDefinition.h"
#include "Mw_EquippableItemDefinition.generated.h"

USTRUCT(BlueprintType)
struct FMw_EquipmentSlotAttributeRange
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta =(ClampMin=0))
	float MaxValue = 1.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta = (EditCondition= "UseValueRange" ,EditConitionHides, ClampMin = 0.0))
	float MinValue;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool UseValueRange = false;
	
};

/**
 * 
 */
UCLASS()
class MAGICWORLD_V03_API UMw_EquippableItemDefinition : public UMw_ItemDefinition
{
	GENERATED_BODY()
	
public:
	
	UMw_EquippableItemDefinition();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Slot", meta = (GameplayTagFilter = "Item.EquipmentSlot"))
	FGameplayTag EquipmentSlotTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Attribute", meta = (GameplayTagFilter = "Attributes"))
	TMap<FGameplayTag, FMw_EquipmentSlotAttributeRange> BaseAttributes;
	
};
