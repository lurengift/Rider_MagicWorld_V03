// Copyright JNJ,  All Rights Reserved.


#include "Items/Instances/Mw_ItemInstance.h"

#include "Mw_LogChannels.h"
#include "Items/Assets/Mw_ItemDefinition.h"


int32 UMw_ItemInstance::GetStackCount() const
{
	return StackCount;
}

bool UMw_ItemInstance::InitializedItem(UMw_ItemDefinition* InItemDefinition, int32 InStackCount)
{
	if (!InItemDefinition)
	{
		UE_LOG(LogMwTemp, Error, TEXT("InItemDefinition is NULL"));
		return false;
	}
	if (InStackCount <= 0)
	{
		return false;
	}
	
	ItemDefinition = InItemDefinition;
	
	StackCount = FMath::Clamp(InStackCount,1,ItemDefinition->GameplayInfo.MaxStackSize);
	
	return true;
}

bool UMw_ItemInstance::AddToStackCount(int32 AmountToAdd)
{
	if (!ItemDefinition)
	{
		UE_LOG(LogMwTemp, Error, TEXT("ItemDefinition is Valid"));
		return false;
	}
	
	if (AmountToAdd <= 0)
	{
		return false;
	}
	if (AmountToAdd + StackCount > ItemDefinition->GameplayInfo.MaxStackSize)
	{
		
		return false;
	}
	
	const int32 OldStackCount = StackCount;
	StackCount += AmountToAdd;
	
	OnItemStackCountChange.Broadcast(this,OldStackCount,StackCount);
	return true;
}

bool UMw_ItemInstance::RemoveFromStackCount(int32 AmountToRemove)
{
	if (!ItemDefinition)
	{
		UE_LOG(LogMwTemp, Error, TEXT("ItemDefinition is Valid"));
		return false;
	}
	if (AmountToRemove <= 0 ||
		AmountToRemove > ItemDefinition->GameplayInfo.MaxStackSize ||
		AmountToRemove > StackCount)
	{
		return false;
	}
	
	const int32 OldStackCount = StackCount;
	StackCount -= AmountToRemove;
	
	OnItemStackCountChange.Broadcast(this,OldStackCount,StackCount);
	
	if (StackCount <= 0)
	{
		OnItemStackDepleted.Broadcast(this);
	}
	
	return true;
}

FMw_ItemDisplayInfo UMw_ItemInstance::GetItemDisplayInfo() const
{
	if (!ItemDefinition)
	{
		UE_LOG(LogMwTemp, Error, TEXT("InItemDefinition is NULL"));
		return FMw_ItemDisplayInfo();
	}
	return ItemDefinition->DisplayInfo;
}

FText UMw_ItemInstance::GetItemName() const
{
	if (!ItemDefinition)
	{
		return FText();
	}
	return ItemDefinition->DisplayInfo.Name;
}

FText UMw_ItemInstance::GetItemDescription() const
{
	if (!ItemDefinition)
	{
		return FText();
	}
	return ItemDefinition->DisplayInfo.Description;
}

FText UMw_ItemInstance::GetItemUseActionText() const
{
	if (!ItemDefinition)
	{
		return FText();
	}
	return ItemDefinition->DisplayInfo.UseActionText;
}

FGameplayTag UMw_ItemInstance::GetItemTypeTag() const
{
	if (!ItemDefinition)
	{
		UE_LOG(LogMwTemp, Error, TEXT("InItemDefinition is NULL"));
		return FGameplayTag();
	}
	return ItemDefinition->ItemTypeTag;
}


FGameplayTag UMw_ItemInstance::GetItemCategoryTag() const
{
	if (!ItemDefinition)
	{
		UE_LOG(LogMwTemp, Error, TEXT("InItemDefinition is NULL"));
		return FGameplayTag();
	}
	return ItemDefinition->ItemCategoryTag;
}

FGameplayTag UMw_ItemInstance::GetItemRarityTag() const
{
	if (!ItemDefinition)
	{
		UE_LOG(LogMwTemp, Error, TEXT("InItemDefinition is NULL"));
		return FGameplayTag();
	}
	return ItemDefinition->ItemRarityTag;
}

FMw_ItemGameplayInfo UMw_ItemInstance::GetItemGameplayInfo() const
{
	if (!ItemDefinition)
	{
		UE_LOG(LogMwTemp, Error, TEXT("InItemDefinition is NULL"));
		return FMw_ItemGameplayInfo();
	}
	return ItemDefinition->GameplayInfo;
}


TSoftObjectPtr<UTexture2D>  UMw_ItemInstance::GetItemIconSoft() const
{
	if (!ItemDefinition)
	{
		return nullptr;
	}
	return ItemDefinition->DisplayInfo.IconSoftPtr;
}

FIntPoint UMw_ItemInstance::GetItemIconDimensions() const
{
	if (!ItemDefinition)
	{
		return FIntPoint();
	}
	return ItemDefinition->DisplayInfo.IconDimensions;
}

float UMw_ItemInstance::GetItemIconGridPadding() const
{
	if (!ItemDefinition)
	{
		return 0.f;
	}
	return ItemDefinition->DisplayInfo.IconGridPadding;
}

FIntPoint UMw_ItemInstance::GetItemIconGridDimensions() const
{
	if (!ItemDefinition)
	{
		return FIntPoint();
	}
	return ItemDefinition->DisplayInfo.IconGridDimensions;
}

bool UMw_ItemInstance::GetItemIsStackable() const
{
	if (!ItemDefinition)
	{
		return false;
	}
	return ItemDefinition->GameplayInfo.IsStackable;
}

float UMw_ItemInstance::GetItemWeight() const
{
	if (!ItemDefinition)
	{
		return 0.f;
	}
	return ItemDefinition->GameplayInfo.Weight;
}

float UMw_ItemInstance::GetItemMaxStackSize() const
{
	if (!ItemDefinition)
	{
		return 0.f;
	}
	return ItemDefinition->GameplayInfo.MaxStackSize;
}
