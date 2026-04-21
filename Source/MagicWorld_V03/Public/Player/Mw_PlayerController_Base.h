// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"

#include "Mw_PlayerController_Base.generated.h"


class AMw_HUD;
class UMw_UserWidget_Overlay;
class UMw_InputConfig;
class UMw_EnhancedInputComponent;
/**
 * 
 */
UCLASS()
class MAGICWORLD_V03_API AMw_PlayerController_Base : public APlayerController
{
	GENERATED_BODY()
	
public:
	
	AMw_PlayerController_Base();
	
	
	
protected:
	
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
	virtual void Tick(float DeltaTime) override;
	
private:
	
	// 用于检测物品的射线检测长度
	UPROPERTY(EditDefaultsOnly, Category = "MagicWorld|TraceItem")
	double TraceLength ;
	
	// 用于检测物品的射线通道
	UPROPERTY(EditDefaultsOnly, Category = "MagicWorld|TraceItem")
	TEnumAsByte<ECollisionChannel> ItemTraceChannel;
	
	TWeakObjectPtr<AActor> ThisActor;
	TWeakObjectPtr<AActor> LastActor;
	// 缓存MwHUD
	TWeakObjectPtr<AMw_HUD> Mw_HUD;
	// 缓存Overlay引用
	TWeakObjectPtr<UMw_UserWidget_Overlay> CachedOverlayWidget; 
	
	// 需要在虚幻编辑器上选择对应的输入数据资产
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "MagicWorld|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMw_InputConfig> InputConfig;
	
	
	// 初始化玩家输入
	void InitPlayerInput(UMw_EnhancedInputComponent* Mw_EnhancedInputComponent);
	
	
	/**
	* 移动输入的回调函数
	* @param InputActionValue 
	*/
	UFUNCTION()
	void Input_Move(const FInputActionValue& InputActionValue) ;
	/**
	 * 镜头旋转
	 * @param InputActionValue 
	 */	
	void Input_Look(const FInputActionValue& InputActionValue) ;

	/**
	 * 物品追踪
	 */
	void TraceForItem();

	/**
	 * 切货物品栏
	 */
	void Input_ToggleInventory();
	/**
	 * 交互
	 * @param Value 
	 */
	void Input_Interact(const FInputActionValue& Value);
};
