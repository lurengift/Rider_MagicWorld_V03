// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"

#include "Mw_Character_Base.generated.h"

class UMw_InventoryComponent;
class UMw_AttributeSet_Base;
class UMw_AbilitySystemComponent;


UCLASS()
class MAGICWORLD_V03_API AMw_Character_Base : public ACharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AMw_Character_Base(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable,Category="MagicWorld|AbilitySystem")
	virtual  UMw_AbilitySystemComponent* GetMwAbilitySystemComponent() const;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	
	
protected:
	
	UPROPERTY(VisibleAnywhere, Category = "MagicWorld|MwComponent")
	TObjectPtr<UMw_AbilitySystemComponent> MwAbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "MagicWorld|MwComponent")
	TObjectPtr<UMw_AttributeSet_Base> MwAttributeSet;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "MagicWorld|MwComponent")
	TObjectPtr<UMw_InventoryComponent> MwInventoryComponent;
	/**
	 * 这个函数用于初始化ASC的委托注册
	 */
	virtual void InitAbilityActorInfo();
	
	
};
