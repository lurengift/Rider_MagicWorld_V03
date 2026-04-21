// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mw_ItemComponent.generated.h"


class UMw_ItemDefinition;
class UMw_ItemInstance;


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class MAGICWORLD_V03_API UMw_ItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMw_ItemComponent();

		
	// 存储的物品定义
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category ="MagicWorld|ItemInstance")
	TObjectPtr<UMw_ItemDefinition> ItemDefinition;
	
	// 数量
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category ="MagicWorld|ItemComponent")
	float Quantity = 1.f;
	
	UFUNCTION(BlueprintCallable,Category ="MagicWorld|ItemComponent")
	bool CreateItem(UStaticMeshComponent* InStaticMeshComponent);
	
	UFUNCTION(BlueprintCallable,Category ="MagicWorld|ItemComponent")
	void InitializeSpawn(UMw_ItemInstance* InItemInstance);
	
	// BlueprintImplementable 蓝图可以覆盖C++中的实现
	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent,Category ="MagicWorld|ItemComponent")
	void OnInitialized();
	void OnInitializedModule(UStaticMeshComponent* InStaticMeshComponent);
	FString GetPickUpMessage() const {return PickUpMessage;}
	
	UMw_ItemInstance* GetItemInstance() const {return ItemInstance;}
	
	void PickedUp(AActor* PickupUser);
	
protected:
	
	UFUNCTION(BlueprintImplementableEvent,Category ="MagicWorld|ItemComponent")
	void OnPickedUp();
	
private:
	
	UPROPERTY(VisibleAnywhere,Category ="MagicWorld|ItemComponent")
	TObjectPtr<UMw_ItemInstance> ItemInstance;

	UPROPERTY(EditAnywhere,Category ="MagicWorld|ItemComponent")
	FString PickUpMessage;

};
