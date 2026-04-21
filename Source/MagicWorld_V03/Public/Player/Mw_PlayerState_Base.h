// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"


#include "Mw_PlayerState_Base.generated.h"

class UMw_AttributeSet_Base;
class UMw_AbilitySystemComponent;
class AMw_PlayerController_Base;
/**
 * 
 */
UCLASS()
class MAGICWORLD_V03_API AMw_PlayerState_Base : public APlayerState,public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	
	AMw_PlayerState_Base();
	
	UFUNCTION(BlueprintCallable, Category = "Lyra|PlayerState")
	AMw_PlayerController_Base* GetMwPlayerControllerBase() const;
	
	UFUNCTION(BlueprintCallable, Category = "Lyra|PlayerState")
	UMw_AbilitySystemComponent* GetMwAbilitySystemComponent() const { return MwAbilitySystemComponent; }
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	/**
	 * 获取AC
	 * @return UMw_AttributeSet_Base*
	 */
	UMw_AttributeSet_Base* GetMwAttributeSet() const { return MwAttributeSet; } //获取as
	
private:
	
	UPROPERTY(VisibleAnywhere, Category = "MagicWorld|PlayerState")
	TObjectPtr<UMw_AbilitySystemComponent> MwAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, Category = "MagicWorld|MwPlayerState")
	TObjectPtr<UMw_AttributeSet_Base> MwAttributeSet;
};
