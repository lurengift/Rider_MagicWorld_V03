// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Mw_WidgetController_Base.h"
#include "GameplayTagContainer.h"

#include "Mw_WidgetController_Overlay.generated.h"


class UMw_UserWidget_Base;
struct FOnAttributeChangeData;

// 存储标签对应的UI信息，任何想显示的信息都可以放在这里，例如物品的图像
USTRUCT( BlueprintType)
struct FMw_UiWidgetRow : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();
	
	// 在Ui部件的领域中，当我们以部件的形式向用户展示文本时，使用FText
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();
	
	// 显示信息的小部件
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UMw_UserWidget_Base> MessageWidget;
	
	// 物品的图片
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;
};

// 广播初始值 02
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangeSignature,float,NewValue);
/* // 我们可以值声明一个广播FOnAttributeChangeSignature 不需要为每一个属性都单独声明， 因为这些都是浮点数
 *DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature,float,NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature,float,NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature,float,NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature,float,NewMaxMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStaminaChangedSignature,float,NewStamina);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxStaminaChangedSignature,float,NewMaxStamina);*/

// 我们将使用一个委托来处理所有消息，因为只需广播一行数据即可满足需求。该行包含用于识别特定数据包的所有信息。
// 它有一个游戏标签和消息，所有的这些内容都包含在数据行本身中，因此我们可以仅用一行来统御全局。
// 小部件消息FMw_UiWidgetRow广播 01 定义
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature,FMw_UiWidgetRow,Row);

/**
 * 覆盖层小部件控制器
 */
UCLASS(Blueprinttype,Blueprintable)
class MAGICWORLD_V03_API UMw_WidgetController_Overlay : public UMw_WidgetController_Base
{
	GENERATED_BODY()
	
public:
	
	/**
	 * 将回调绑定到依赖项
	 */
	virtual void BindCallbacksToDependencies() override;
	
	
	/**
	 * 广播初始值
	 */
	virtual void BroadcastInitialValues() override;

	// 广播初始值 03
	UPROPERTY( BlueprintAssignable ,Category = "MagicWorld|Attributes")
	FOnAttributeChangeSignature OnHealthChanged;
	
	UPROPERTY( BlueprintAssignable ,Category = "MagicWorld|Attributes")
	FOnAttributeChangeSignature OnMaxHealthChanged;

	UPROPERTY( BlueprintAssignable ,Category = "MagicWorld|Attributes")
	FOnAttributeChangeSignature OnManaChanged;
	
	UPROPERTY( BlueprintAssignable ,Category = "MagicWorld|Attributes")
	FOnAttributeChangeSignature OnMaxManaChanged;
	
	UPROPERTY( BlueprintAssignable ,Category = "MagicWorld|Attributes")
	FOnAttributeChangeSignature OnStaminaChanged;
	
	UPROPERTY( BlueprintAssignable ,Category = "MagicWorld|Attributes")
	FOnAttributeChangeSignature OnMaxStaminaChanged;
	
	// 小部件消息FMw_UiWidgetRow广播 02 声明变量
	UPROPERTY( BlueprintAssignable ,Category = "MagicWorld|Messages")
	FMessageWidgetRowSignature MessageWidgetRowDelegate;
protected:
	
	UPROPERTY( EditDefaultsOnly,BlueprintReadOnly ,Category = "MagicWorld|WidgetData")
	TObjectPtr<UDataTable> MessageWidgetDataTable;
	
	/**
		 * // 我们想有一个函数可以传入数据表和标签，返回任何的数据表行 ，所以用模版函数
		 * @tparam T typename T
		 * @param DataTable UDataTable*
		 * @param Tag FGameplayTag&
		 * @return 
		 */
	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag) const;
};
template <typename T>
T* UMw_WidgetController_Overlay::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag) const
{
	// 这里传入空文本是因为这里的暂时上下文没有其他用途
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}