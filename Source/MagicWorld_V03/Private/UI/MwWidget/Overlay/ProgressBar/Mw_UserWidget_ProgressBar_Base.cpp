// Copyright JNJ,  All Rights Reserved.


#include "UI/MwWidget/Overlay/ProgressBar/Mw_UserWidget_ProgressBar_Base.h"

#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/SizeBox.h"

void UMw_UserWidget_ProgressBar_Base::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	UpdateBoxSize(BoxWidth,BoxHeight);
	UpdateBackgroundBrush(BackgroundBrush);
	UpdateGlobeImage(ProgressBarBackImage,ProgressBarFillImage);
}

void UMw_UserWidget_ProgressBar_Base::UpdateBoxSize(float InBoxWidth, float InBoxHeight)
{
	if (SizeBox_Root)
	{
		SizeBox_Root->SetWidthOverride(InBoxWidth);
		SizeBox_Root->SetHeightOverride(InBoxHeight);
	}
	
}

void UMw_UserWidget_ProgressBar_Base::UpdateBackgroundBrush(const FSlateBrush& InBackgroundBrush)
{
	if (Image_Background)
	{
		Image_Background->SetBrush(InBackgroundBrush);
	}
	
}

void UMw_UserWidget_ProgressBar_Base::UpdateGlobeImage(const FSlateBrush& InProgressBarBackImage,
	const FSlateBrush& InProgressBarFillImage)
{
	if (ProgressBar_Globe)
	{
		
		// 1. 获取当前样式副本
		FProgressBarStyle CurrentStyle =	ProgressBar_Globe->GetWidgetStyle();

		// 3. 修改样式副本的背景图片
		CurrentStyle.SetBackgroundImage(InProgressBarBackImage);

		CurrentStyle.SetFillImage(InProgressBarFillImage);
		
		// 4. 将修改后的样式应用到进度条
		ProgressBar_Globe->SetWidgetStyle(CurrentStyle);
	}


}
