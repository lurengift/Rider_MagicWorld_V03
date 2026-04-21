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
	
	UFUNCTION(BlueprintCallable,Category ="MagicWorld|ItemComponent")
	bool CreateItem(UStaticMeshComponent* InStaticMeshComponent);
	
	UFUNCTION(BlueprintCallable,Category ="MagicWorld|ItemComponent")
	void InitializeSpawn(UMw_ItemInstance* InItemInstance);
	/**
	 * 是否允许堆叠
	 * @return 
	 */
	bool IsStackable() const;
	// BlueprintImplementable 蓝图可以覆盖C++中的实现
	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent,Category ="MagicWorld|ItemComponent")
	void OnInitialized();
	void OnInitializedModule(UStaticMeshComponent* InStaticMeshComponent);
	FString GetPickUpMessage() const {return PickUpMessage;}
	
	int32 GetQuantity() const {return Quantity;}
	void SetQuantity(int32 InQuantity) {Quantity = InQuantity;}
	
	UMw_ItemInstance* GetItemInstance() const {return ItemInstance;}
	
	void InteractPickedUp(AActor* PickedUpActor,UMw_ItemComponent* InItemComponent);
	
	void PickedUp();
	
	
protected:
	
	UFUNCTION(BlueprintImplementableEvent,Category ="MagicWorld|ItemComponent")
	void OnPickedUp();
	
private:
	
	UPROPERTY(VisibleAnywhere,Category ="MagicWorld|ItemComponent")
	TObjectPtr<UMw_ItemInstance> ItemInstance;

	// 数量
	UPROPERTY(EditAnywhere,Category ="MagicWorld|ItemComponent")
	float Quantity = 1.f;
	
	UPROPERTY(EditAnywhere,Category ="MagicWorld|ItemComponent")
	FString PickUpMessage;

};
