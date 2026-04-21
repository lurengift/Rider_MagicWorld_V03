// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/MwWidget/Mw_UserWidget_Base.h"
#include "Mw_UserWidget_Overlay.generated.h"

class UMw_UserWidget_InventoryInfoMessage;
/**
 * 
 */
UCLASS()
class MAGICWORLD_V03_API UMw_UserWidget_Overlay : public UMw_UserWidget_Base
{
	GENERATED_BODY()
	
	
public:
	
	virtual void NativeOnInitialized() override;
	
	//BlueprintImplementableEvent 表示蓝图覆写，C++不能默认实现
	/**
	 * 显示拾取消息文本
	 * @param Message 消息文本
	 */
	UFUNCTION(BlueprintImplementableEvent,Category = "MagicWorld|MwUserWidget_HUDWidget")
	void ShowPickupMessage(const FString& Message);

	/**
	 * 隐藏拾取消息文本
	 */
	UFUNCTION(BlueprintImplementableEvent,Category = "MagicWorld|MwUserWidget_HUDWidget")
	void HidePickupMessage();
	
private:
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMw_UserWidget_InventoryInfoMessage> InventoryInfoMessage;
	
	UFUNCTION()
	void OnNoRoom();
};
