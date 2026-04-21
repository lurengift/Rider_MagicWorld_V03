// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Mw_UserWidget_Base.generated.h"

/**
 * 
 */
UCLASS()
class MAGICWORLD_V03_API UMw_UserWidget_Base : public UUserWidget
{
	GENERATED_BODY()
		
public:
	/**
	 * 设置小部件控制器
	 * @param InWidgetController 小部件控制器
	 */
	UFUNCTION(BlueprintCallable, Category = "MagicWorld|UI")
	void SetWidgetController(UObject* InWidgetController);
	
	// 小部件控制器
	UPROPERTY(BlueprintReadWrite, Category = "MagicWorld|UI")
	TObjectPtr<UObject> WidgetController;
	
protected:
	
	UFUNCTION(BlueprintImplementableEvent, Category = "MagicWorld|UI") //函数能在蓝图中实现
	void OnWidgetControllerSetEnd();//设置控制层完成之后触发
};
