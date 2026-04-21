// Copyright JNJ,  All Rights Reserved.


#include "UI/MwWidget/Message/Mw_UserWidget_InventoryInfoMessage.h"

#include "Components/TextBlock.h"

void UMw_UserWidget_InventoryInfoMessage::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	TextBlock->SetText(FText::GetEmpty());
	MessageHide();
}

void UMw_UserWidget_InventoryInfoMessage::SetMessage(const FText& Message)
{
	TextBlock -> SetText(Message);
	
	if (!bIsMessageActive)
	{
		MessageShow();
	}
	bIsMessageActive = true;
	GetWorld()->GetTimerManager().SetTimer(MessageTimer,[this]()
	{
		MessageHide();
		bIsMessageActive = false;
		
	},MessageLifeTime,false);
}
