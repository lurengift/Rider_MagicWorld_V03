// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/MwWidget/Mw_UserWidget_Base.h"
#include "Mw_UserWidget_InventoryInfoMessage.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class MAGICWORLD_V03_API UMw_UserWidget_InventoryInfoMessage : public UMw_UserWidget_Base
{
	GENERATED_BODY()
public:
	
	virtual void NativeOnInitialized() override;

	/**
	 * 显示消息
	 */
	UFUNCTION(BlueprintImplementableEvent,Category = "MagicWorld|Inventory")
	void MessageShow();

	/**
	 * 隐藏消息
	 */
	UFUNCTION(BlueprintImplementableEvent,Category = "MagicWorld|Inventory")
	void MessageHide();

	/**
	 * 设置消息文本
	 * @param Message 文本
	 */
	void SetMessage(const FText& Message);
private:
	// 库存增加失败时，提示文本
	UPROPERTY(VisibleAnywhere,meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock;
	// 文本显示时间
	UPROPERTY(EditAnywhere,Category="MagicWorld|Inventory")
	float MessageLifeTime = 3.f;
	// 计时器
	FTimerHandle MessageTimer;
	// 计时器是否启用
	bool bIsMessageActive = false;
};
