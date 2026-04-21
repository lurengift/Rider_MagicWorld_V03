// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Mw_WidgetController_Base.generated.h"

class UMw_AttributeSet_Base;
class UMw_AbilitySystemComponent;
class AMw_PlayerState_Base;
class AMw_PlayerController_Base;
/**
 * 这意味着我们的能力系统组件、属性、角色，以及任何真正与数据相关的重要内容，
 * widgetcontroller控件控制器将负责获取其数据并将它们进行广播给任何将其控制器设置为它的控件。
 * 因此我希望我的控制器拥有一组变量，出于本项目，暂时对AbilitySystemCompont、AttributeSet、
 * PlayerState、PlayerController感兴趣。在游戏过程中控件可能需要访问这4个元素。因此这就是我们为
 * 控制器设置依赖关系的方式。
 */
USTRUCT( BlueprintType )
struct FWidgetControllerParams
{
	GENERATED_BODY()
	
	FWidgetControllerParams(){};
	FWidgetControllerParams(AMw_PlayerController_Base* MwPC,AMw_PlayerState_Base* MwPS, UMw_AbilitySystemComponent* MwASC, UMw_AttributeSet_Base* MwAS)
	:MwPlayerController(MwPC),MwPlayerState(MwPS),MwAbilitySystemComponent(MwASC),MwAttributeSet(MwAS){};

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<AMw_PlayerController_Base> MwPlayerController = nullptr;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<AMw_PlayerState_Base> MwPlayerState = nullptr;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UMw_AbilitySystemComponent> MwAbilitySystemComponent = nullptr;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UMw_AttributeSet_Base> MwAttributeSet = nullptr;

};

UCLASS()
class MAGICWORLD_V03_API UMw_WidgetController_Base : public UObject
{
	GENERATED_BODY()
	
public:
	
	/**
	 * 初始化 设置依赖项（PC、PS、ASC、AS）
	 * @param Params FWidgetControllerParams&
	 */
	UFUNCTION( BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& Params);
	
	/**
	 * 广播初始值 01 
	 * 主动推送一次当前值，让Widget在刚创建时能显示正确的初始数据（比如血条一开始就是满的）。
	 */
	UFUNCTION( BlueprintCallable)
	virtual void BroadcastInitialValues();

	/**
	 * 建立监听，当底层数据变化时，控制器能收到通知，然后转发给Widget。
	 */
	virtual void BindCallbacksToDependencies();
	
protected:

	
#pragma region	// 这4个变量是获取数据以广播到我们控件的基础
	
	
	UPROPERTY( BlueprintReadOnly, Category ="MagicWorld|WidgetController")
	TObjectPtr<AMw_PlayerController_Base> Mw_PlayerController;
	
	UPROPERTY( BlueprintReadOnly, Category ="MagicWorld|WidgetController")
	TObjectPtr<AMw_PlayerState_Base> Mw_PlayerState;
	
	UPROPERTY( BlueprintReadOnly, Category ="MagicWorld|WidgetController")
	TObjectPtr<UMw_AbilitySystemComponent> Mw_AbilitySystemComponent;
	
	UPROPERTY( BlueprintReadOnly, Category ="MagicWorld|WidgetController")
	TObjectPtr<UMw_AttributeSet_Base> Mw_AttributeSet;
	
#pragma endregion
};
