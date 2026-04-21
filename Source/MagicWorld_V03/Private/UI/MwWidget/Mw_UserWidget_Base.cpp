// Copyright JNJ,  All Rights Reserved.


#include "UI/MwWidget/Mw_UserWidget_Base.h"

void UMw_UserWidget_Base::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	OnWidgetControllerSetEnd(); // 通知蓝图事件
}
