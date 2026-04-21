// Copyright JNJ, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "Templates/Function.h"

/**
 * 异步加载软指针资源，并在加载完成后执行回调。
 * 使用 Context 对象来确保回调只在上下文有效时执行，避免悬空引用。
 */
template<typename T>
void AsyncLoadSoftPtr(TSoftObjectPtr<T> SoftPtr, TFunction<void(T*)> OnLoaded, UObject* Context)
{
	if (SoftPtr.IsNull())
	{
		return;
	}

	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
	StreamableManager.RequestAsyncLoad(
		SoftPtr.ToSoftObjectPath(),
		[OnLoaded, SoftPtr, Context]()
		{
			if (Context && IsValid(Context))
			{
				T* LoadedAsset = SoftPtr.Get();
				if (LoadedAsset)
				{
					OnLoaded(LoadedAsset);
				}
			}
		}
	);
}