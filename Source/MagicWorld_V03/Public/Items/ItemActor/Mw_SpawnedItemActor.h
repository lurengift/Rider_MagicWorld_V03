// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Items/Interfaces/Mw_HighlightItemInterface.h"
#include "Mw_SpawnedItemActor.generated.h"



UCLASS()
class MAGICWORLD_V03_API AMw_SpawnedItemActor : public AActor,public IMw_HighlightItemInterface
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> ItemStaticMeshComponent;
	

	
	// 高光材质
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category ="MagicWorld|ItemInstance")
	TObjectPtr<UMaterialInterface> HighlightMaterial;

	/**
	 * 物品轮廓高光
	 */
	virtual void HighlightItem_Implementation() override;
	/**
	 * 取消物品轮廓高光
	 */
	virtual void UnHighlightItem_Implementation() override;
	
public:

	AMw_SpawnedItemActor();
	
	virtual void BeginPlay() override;
	
	
	

};
