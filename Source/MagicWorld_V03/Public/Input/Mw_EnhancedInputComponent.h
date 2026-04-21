// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Mw_InputConfig.h"
#include "Mw_EnhancedInputComponent.generated.h"

class UInputAction;
class UEnhancedInputLocalPlayerSubsystem;

/**
 * 
 */
UCLASS()
class MAGICWORLD_V03_API UMw_EnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	
	UMw_EnhancedInputComponent();
	
	/**
	 * 模版函数：本地输入
	 * @tparam UserClass 
	 * @tparam FuncType 
	 * @param InputConfig 输入操作数据资产
	 * @param InputTag 游戏标签
	 * @param TriggerEvent 触发事件
	 * @param Object 输入映射场景对接
	 * @param Func 回调函数
	 * @param bLogIfNotFound 
	 */
	template<class UserClass, typename FuncType>
	void BindNativeAction(const UMw_InputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func , bool bLogIfNotFound);
	
	/**
	 * 这个输入函数与本地输入动作不同
	 * Ability按键触发
	 * @tparam UserObject 
	 * @tparam CallbackFunc 
	 * @param InInputConfig 输入操作数据资产
	 * @param ContextObject 输入映射场景
	 * @param InputPressedFunc 输入按下的回调函数
	 * @param InputReleasedFunc 输入释放的回调函数
	 * @param BindHandles 计数
	 */
	template<class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(const UMw_InputConfig* InInputConfig, UserObject* ContextObject,
								CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc, TArray<uint32>& BindHandles);

	void RemoveBinds(TArray<uint32>& BindHandles);
	
};

template <class UserClass, typename FuncType>
void UMw_EnhancedInputComponent::BindNativeAction(const UMw_InputConfig* InputConfig, const FGameplayTag& InputTag,
	ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func, bool bLogIfNotFound)
{
	check(InputConfig);
	if (const UInputAction* IA = InputConfig->FindNativeInputActionForTag(InputTag, bLogIfNotFound))
	{
		BindAction(IA, TriggerEvent, Object, Func);
	}
}

template <class UserObject, typename CallbackFunc>
void UMw_EnhancedInputComponent::BindAbilityInputAction(const UMw_InputConfig* InInputConfig, UserObject* ContextObject,
	CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc, TArray<uint32>& BindHandles)
{
	checkf(InInputConfig,TEXT("DataAsset_InputConfig is null,can not proceed with binding"));

	for (const FMw_InputAction& AbilityInputActionConfig : InInputConfig->AbilityInputActions)
	{
		if (AbilityInputActionConfig.InputAction && AbilityInputActionConfig.InputTag.IsValid())
		{
			//if (!AbilityInputActionConfig.IsValid()) continue;
			if (InputPressedFunc)
			{
				// 按下
				BindHandles.Add(BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Triggered, ContextObject, InputPressedFunc, AbilityInputActionConfig.InputTag).GetHandle());
		
			}
			if (InputReleasedFunc)
			{
				// 释放
				BindHandles.Add(BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Completed, ContextObject, InputReleasedFunc, AbilityInputActionConfig.InputTag).GetHandle());
	
			}
		}
		
	}
}