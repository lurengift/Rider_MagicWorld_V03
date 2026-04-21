// Copyright JNJ,  All Rights Reserved.


#include "UI/WidgetController/Mw_WidgetController_Overlay.h"

#include "AbilitySystem/Mw_AbilitySystemComponent.h"
#include "AbilitySystem/Mw_AttributeSet_Base.h"


void UMw_WidgetController_Overlay::BindCallbacksToDependencies()
{
	const UMw_AttributeSet_Base* MwAttributeSet = CastChecked<UMw_AttributeSet_Base>(Mw_AttributeSet);
	// 每当Health发生变化时就会被调用 ，MwAttributeSet->GetHealthAttribute()这里指定了要监听的属性
	// 对于简单的回调函数我们可以直接使用Lambda表达式 这里保留Stamina的回调函数是为了暂时不同的使用方法
	Mw_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		MwAttributeSet->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				// 将最新值广播
				OnHealthChanged.Broadcast(Data.NewValue);
			}
			);
	
	Mw_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		MwAttributeSet->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
			);
	
	Mw_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		MwAttributeSet->GetManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				// 将最新值广播
				OnManaChanged.Broadcast(Data.NewValue);
			}
			);
	
	Mw_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		MwAttributeSet->GetMaxManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxManaChanged.Broadcast(Data.NewValue);
			}
			);
	
	Mw_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
MwAttributeSet->GetStaminaAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
	{
		OnStaminaChanged.Broadcast(Data.NewValue);
	});
	
	Mw_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
MwAttributeSet->GetMaxStaminaAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
	{
		OnMaxStaminaChanged.Broadcast(Data.NewValue);
	});
	
	// GE效果AssetTag广播 04 绑定广播
	// 绑定委托需要用回调函数，但是用AddLambda 匿名函数也是可以的
	// 我们想将任何东西绑定到一个委托上，它需要匹配这个前面，例如下面需要一个const FGameplayTagContainer&的签名。
	// () 圆括号是输入参数输入的地方, 因此我们可以放置一个常量FGameplayTagContainer的引用，并将其称为AssetTags
	// 当此委托发生广播时，该lambda将发生调用
	// 如果我们想要从某个对象访问其成员变量，那么该对象，即拥有该成员变量的类，必须在lambda表达式中被捕获
	// 可以通过引用捕获对象也可以用指针捕获对象，如果我们希望能够访问GetDataTableRowByTag，那我们必须捕获this，即
	// 我们当前所在的对象。因此，指向当前对象的指针就是关键字this
	Mw_AbilitySystemComponent->EffectAssetTagsDelegate.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			// 这里通过引用来避免复制标签，如果使用引用方式必须将其声明为常量引用
			for (const FGameplayTag& Tag : AssetTags)
			{
				// 如果某个标签存在于我们项目中，即存在于我们配置文件中，那么我可以通过静态函数FGameplayTag::RequestGameplayTag来获取该标签，
				// 此时需要一个FName作为参数
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				// "Message.HealthPotion".MatchesTag("Message") will return true, "Message".MatchesTag（“Message.HealthPotion")  will return false
				if (Tag.MatchesTag(MessageTag))
				{
					/*
					const FString Msg = FString::Printf(TEXT("GE AssetTag is %s"),*Tag.ToString());
					GEngine->AddOnScreenDebugMessage(-1,8.f,FColor::Blue,Msg);
					*/
					
					const FMw_UiWidgetRow* Row = GetDataTableRowByTag<FMw_UiWidgetRow>(MessageWidgetDataTable,Tag);
					// 小部件消息FMw_UiWidgetRow广播 03 广播 (在WBP_Overlay中进行绑定）
					MessageWidgetRowDelegate.Broadcast(*Row);
				}
	
			}
		}
		);
}

void UMw_WidgetController_Overlay::BroadcastInitialValues()
{
	const UMw_AttributeSet_Base* MwAttributeSet = CastChecked<UMw_AttributeSet_Base>(Mw_AttributeSet);
	// 广播初始值 04 
	OnHealthChanged.Broadcast(MwAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(MwAttributeSet->GetMaxHealth());

	OnManaChanged.Broadcast(MwAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(MwAttributeSet->GetMaxMana());
	
	OnStaminaChanged.Broadcast(MwAttributeSet->GetStamina());
	OnMaxStaminaChanged.Broadcast(MwAttributeSet->GetMaxStamina());
}
