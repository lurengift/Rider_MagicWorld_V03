// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Mw_Character_Base.h"
#include "Mw_Character_Enemy.generated.h"

/**
 * 
 */
UCLASS()
class MAGICWORLD_V03_API AMw_Character_Enemy : public AMw_Character_Base
{
	GENERATED_BODY()
	
public:
	
	AMw_Character_Enemy();
	
protected:
	
	virtual void BeginPlay() override;
	
	virtual void InitAbilityActorInfo() override;	
};
