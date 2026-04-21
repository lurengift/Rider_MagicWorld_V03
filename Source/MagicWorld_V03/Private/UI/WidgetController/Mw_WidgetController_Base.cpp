// Copyright JNJ,  All Rights Reserved.


#include "UI/WidgetController/Mw_WidgetController_Base.h"

void UMw_WidgetController_Base::SetWidgetControllerParams(const FWidgetControllerParams& Params)
{
	Mw_PlayerController = Params.MwPlayerController;
	Mw_PlayerState = Params.MwPlayerState;
	Mw_AbilitySystemComponent = Params.MwAbilitySystemComponent;
	Mw_AttributeSet = Params.MwAttributeSet;
}

void UMw_WidgetController_Base::BroadcastInitialValues()
{
}

void UMw_WidgetController_Base::BindCallbacksToDependencies()
{
}
