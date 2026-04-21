// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/MwWidget/Mw_UserWidget_Base.h"
#include "Mw_UserWidget_ProgressBar_Base.generated.h"

class UProgressBar;
class UImage;
class UTextBlock;
class USizeBox;
struct FSlateBrush;
/**
 * 
 */
UCLASS()
class MAGICWORLD_V03_API UMw_UserWidget_ProgressBar_Base : public UMw_UserWidget_Base
{
	GENERATED_BODY()
	
public:
	
	virtual void NativePreConstruct() override;

	
protected:
	
	// 尺寸框
	UPROPERTY(VisibleAnywhere,meta = (BindWidget))
	TObjectPtr<USizeBox> SizeBox_Root;
	
	// 进度条
	UPROPERTY(VisibleAnywhere,meta = (BindWidget))
	TObjectPtr<UProgressBar> ProgressBar_Globe;

	// 玻璃效果（透明）图片
	UPROPERTY(VisibleAnywhere,meta = (BindWidget))
	TObjectPtr<UImage> Image_Glass;
	// 背景图片
	UPROPERTY(VisibleAnywhere,meta = (BindWidget))
	TObjectPtr<UImage> Image_Background;
	// 文本
	UPROPERTY(VisibleAnywhere,meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_TextValue;
	
	
private:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"),Category="MagicWorld|UI|ProgressBar")
	float BoxWidth = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"),Category="MagicWorld|UI|ProgressBar")
	float BoxHeight = 0.f;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta = (AllowPrivateAccess = "true"),Category="MagicWorld|UI|ProgressBar")
	FSlateBrush BackgroundBrush;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta = (AllowPrivateAccess = "true"),Category="MagicWorld|UI|ProgressBar")
	FSlateBrush ProgressBarBackImage;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta = (AllowPrivateAccess = "true"),Category="MagicWorld|UI|ProgressBar")
	FSlateBrush ProgressBarFillImage;
	
	UFUNCTION(BlueprintCallable,Category="MagicWorld|UI|ProgressBar")
	void UpdateBoxSize(float InBoxWidth,float InBoxHeight);

	UFUNCTION(BlueprintCallable,Category="MagicWorld|UI|ProgressBar")
	void UpdateBackgroundBrush(const FSlateBrush& InBackgroundBrush);
	
	UFUNCTION(BlueprintCallable,Category="MagicWorld|UI|ProgressBar")
	void UpdateGlobeImage(const FSlateBrush& InProgressBarBackImage,const FSlateBrush& InProgressBarFillImage);
};
