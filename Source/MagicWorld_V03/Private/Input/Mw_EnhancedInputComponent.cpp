// Copyright JNJ,  All Rights Reserved.


#include "Input/Mw_EnhancedInputComponent.h"

UMw_EnhancedInputComponent::UMw_EnhancedInputComponent()
{
}

void UMw_EnhancedInputComponent::RemoveBinds(TArray<uint32>& BindHandles)
{
	for (uint32 Handle : BindHandles)
	{
		RemoveBindingByHandle(Handle);
	}
	BindHandles.Reset();
}
