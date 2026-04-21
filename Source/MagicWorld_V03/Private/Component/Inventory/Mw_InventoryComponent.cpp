// Copyright JNJ,  All Rights Reserved.


#include "Component/Inventory/Mw_InventoryComponent.h"

#include "Mw_DebugHelper.h"
#include "FunctionLibrary/Mw_BFL_Widget.h"
#include "Items/Mw_ItemTags.h"
#include "Items/Assets/Mw_ItemDefinition.h"
#include "Items/Component/Mw_ItemComponent.h"
#include "Items/Instances/Mw_ConsumableItemInstance.h"
#include "Items/Instances/Mw_EquippableItemInstance.h"
#include "Items/Instances/Mw_ItemInstance.h"
#include "UI/HUD/Mw_HUD.h"
#include "UI/MwWidget/Inventory/Mw_UserWidget_InventoryBase.h"
#include "UI/MwWidget/Inventory/Types/Mw_InventoryGridTypes.h"


UMw_InventoryComponent::UMw_InventoryComponent()
{

	PrimaryComponentTick.bCanEverTick = false;
	
}

bool UMw_InventoryComponent::TryAddItem(UMw_ItemComponent* InItemComponent)
{
	if (!InItemComponent)
	{
		Debug::Print(TEXT("InItemComponent is not valid. "),EMwLogType::LogMwTemp,ELogVerbosity::Error,true);
		return false;
	}
	if (!InventoryWidget.IsValid())
	{
		InventoryWidget = Cast<UMw_UserWidget_InventoryBase>(UMw_BFL_Widget::GetMwHUD(GetWorld())->GetInventoryWidget());
	}
	
	FInv_SlotAvailabilityResult Result = InventoryWidget->HasRoomForItem(InItemComponent);
	
	UMw_ItemInstance* FoundItemInstance = FindFirstItemByType(InItemComponent->GetItemInstance()->GetItemTypeTag());
	
	Result.Item = FoundItemInstance;
	
	if (Result.TotalRoomToFill == 0)
	{
		// 总的空间已经满了
		NoRoomInInventory.Broadcast();
		return false;
	}
	
	if (Result.Item.IsValid() && Result.bStackable)
	{
		// 向库存中已存在的物品添加堆叠。我们只需更新堆叠数量，而不是创建此类型的全新物品
		AddStacksToItem(InItemComponent,Result.TotalRoomToFill,Result.Remainder);
		//return true;
	}
	else if (Result.TotalRoomToFill > 0)
	{
		// 该物品类型在库存中并不存在，创建新物品并更新所有槽位
		AddNewItem(InItemComponent, Result.bStackable ? Result.TotalRoomToFill : 0,Result.Remainder);//Result.bStackable ? Result.TotalRoomToFill : 0);
		//return true;
	}
	else
	{
		return false;
	}
	
	return true;
	
}

/*
bool UMw_InventoryComponent::TryAddItem(UMw_ItemInstance* InItemInstance, int32 InStackCount)
{
	/#1#/ 如果物品可堆叠，先尝试合并
	if (InItemInstance->GetGameplayInfo().IsStackable)
	{
		// 查找可合并的现有实例（相同定义且动态属性一致）
		if (UMw_ItemInstance* ExistingStack = FindStackableInstance(InItemInstance))
		{
			return MergeToExistingStack(ExistingStack, InItemInstance, InStackCount);
		}
		
	}
	
	// 无法合并，需要添加新实例（此时需检查槽位）
	if (ItemInventorys.Num() >= MaxItemSlots)
	{
		Debug::Print(TEXT("Inventory full, cannot add new item"), EMwLogType::LogMwTemp, ELogVerbosity::Warning, true);
		return false;
	}

	return AddNewItemInstance(InItemInstance, InStackCount);#1#
}
*/

void UMw_InventoryComponent::AddNewItem(UMw_ItemComponent* InItemComponent, int32 InStackCount,int32 Remainder)
{
	if (!InItemComponent) return;
	//if (InStackCount <= 0) return;
	UMw_ItemInstance* NewInstance = DuplicateItemInstance(InItemComponent->GetItemInstance(), InStackCount); // 需要实现深拷贝

	ItemInventorys.Add(NewInstance);
	
	// 物品广播
	OnInventoryItemAdded.Broadcast(NewInstance);
	
	// 是否有剩余
	if (Remainder == 0)
	{
		// 全部拾取
		InItemComponent->PickedUp();
	}
	else if (InItemComponent && InItemComponent->GetItemInstance())
	{
		// 物品组件是直接设置
		InItemComponent->SetQuantity(Remainder);
		// 物品实例通过减少来变动
		InItemComponent->GetItemInstance()->RemoveFromStackCount(InStackCount);
	}
	
}

void UMw_InventoryComponent::AddStacksToItem(UMw_ItemComponent* InItemComponent, int32 InStackCount, int32 Remainder)
{
	// TODO:: 这个不一定适合我，我应该要更加完善的判断
	const FGameplayTag& ItemTypeTag = IsValid(InItemComponent) ? InItemComponent->GetItemInstance()->GetItemTypeTag() : FGameplayTag::EmptyTag;
	
	UMw_ItemInstance* SlotItemInstance = FindFirstItemByType(ItemTypeTag);
	
	if (!IsValid(SlotItemInstance)) return;
	
	SlotItemInstance->AddToStackCount(InStackCount);
	
	if (Remainder == 0)
	{
		InItemComponent->PickedUp();
	}
	else if (InItemComponent && InItemComponent->GetItemInstance())
	{
		// 物品组件是直接设置
		InItemComponent->SetQuantity(Remainder);
		// 物品实例通过减少来变动
		InItemComponent->GetItemInstance()->RemoveFromStackCount(InStackCount);
	}
}

bool UMw_InventoryComponent::RemoveItemInventory(UMw_ItemInstance* InItemInstance, int32 InStackCount)
{
	if (!InItemInstance)
	{
		UE_LOG(LogMwTemp, Error, TEXT("InItemInstance is not valid, Cannot Remove Item Inventory."));
		return false;
	}
	if (InStackCount <= 0 ) return false;
	
	ItemInventorys.Remove(InItemInstance);
	
	return true;
}

UMw_ItemInstance* UMw_InventoryComponent::FindFirstItemByType(const FGameplayTag& ItemType) const
{
	for (UMw_ItemInstance* Existing : ItemInventorys)
	{
		if (Existing && Existing->GetItemTypeTag().MatchesTagExact(ItemType))
		{
			return Existing;
		}
	}
	return nullptr;
}

TArray<UMw_ItemInstance*> UMw_InventoryComponent::GetItemInstances() const
{
	if (ItemInventorys.IsEmpty())
	{
		return TArray<UMw_ItemInstance*>();
	}
	
	return ItemInventorys;
}

UMw_ItemInstance* UMw_InventoryComponent::FindStackableInstance(const UMw_ItemInstance* InItem) const
{
	// Existing 现有
	for (UMw_ItemInstance* Existing : ItemInventorys)
	{
		if (!Existing || Existing->ItemDefinition != InItem->ItemDefinition)
			continue;

		// 如果是可装备物品，需要比较动态属性（如 Attributes）
		if (Existing->ItemDefinition->ItemTypeTag == Mw_ItemTags::Item_Type_Equippable)
		{
			const UMw_EquippableItemInstance* ExistingEquip = Cast<UMw_EquippableItemInstance>(Existing);
			const UMw_EquippableItemInstance* InEquip = Cast<UMw_EquippableItemInstance>(InItem);
			if (!ExistingEquip || !InEquip)
				continue;
			if (!AreAttributesEqual(ExistingEquip->Attributes, InEquip->Attributes))
				continue;
		}
		else if (Existing->ItemDefinition->ItemTypeTag == Mw_ItemTags::Item_Type_Consumable)
		{
			const UMw_ConsumableItemInstance* ExistingEquip = Cast<UMw_ConsumableItemInstance>(Existing);
			const UMw_ConsumableItemInstance* InEquip = Cast<UMw_ConsumableItemInstance>(InItem);
			if (!ExistingEquip || !InEquip)
				continue;
			
		}else if (Existing->ItemDefinition->ItemTypeTag == Mw_ItemTags::Item_Type_Craftable)
		{
			return nullptr;
		}
		else
		{
			return nullptr;
		}

		// 检查是否还有空间可堆叠
		if (Existing->GetStackCount() < Existing->GetItemMaxStackSize())
			return Existing;
	}
	return nullptr;
}

bool UMw_InventoryComponent::MergeToExistingStack(UMw_ItemInstance* Existing, UMw_ItemInstance* InItem,
	int32 InStackCount)
{
	int32 MaxStack = Existing->GetItemMaxStackSize();
	int32 CurrentCount = Existing->GetStackCount();
	int32 Total = CurrentCount + InStackCount;

	if (Total <= MaxStack)
	{
		// 完全合并
		Existing->AddToStackCount(InStackCount);
		// 库存变化进行广播
		OnInventoryItemAdded.Broadcast(Existing);
		
		return true;
	}
	else
	{
		// 先填满现有堆叠
		int32 FillAmount = MaxStack - CurrentCount;
		Existing->AddToStackCount(FillAmount);
		
		OnInventoryItemAdded.Broadcast(Existing);
		
		int32 Remaining = InStackCount - FillAmount;

		// 剩余部分需要创建新实例（可能还要拆分多个堆叠）
		return AddNewItemInstance(InItem, Remaining);
	}
}

bool UMw_InventoryComponent::AddNewItemInstance(UMw_ItemInstance* InItem, int32 InStackCount)
{
	if (InStackCount <= 0) return false;

	// 槽位上限检查
	if (ItemInventorys.Num() >= MaxItemSlots)
	{
		Debug::Print(TEXT("Inventory full while adding new item"), EMwLogType::LogMwTemp, ELogVerbosity::Warning, true);
		/*// 物品添加失败广播
		NoRoomInInventory.Broadcast();*/
		return false;
	}
	
	int32 MaxStack = InItem->GetItemMaxStackSize();
	int32 Remaining = InStackCount;
	// 如果需要拆分（剩余数量超过最大堆叠）
	while (Remaining > 0)
	{
		if (ItemInventorys.Num() >= MaxItemSlots)
		{
			Debug::Print(TEXT("Inventory full while adding new item"), EMwLogType::LogMwTemp, ELogVerbosity::Warning, true);
			
			return false;
		}

		int32 NewStackCount = FMath::Min(Remaining, MaxStack);
		UMw_ItemInstance* NewInstance = DuplicateItemInstance(InItem, NewStackCount); // 需要实现深拷贝
		ItemInventorys.Add(NewInstance);
		
		OnInventoryItemAdded.Broadcast(NewInstance);
		
		Remaining -= NewStackCount;
	}
	
	return true;
}

bool UMw_InventoryComponent::AreAttributesEqual(const TMap<FGameplayTag, float>& A, const TMap<FGameplayTag, float>& B,
	float Tolerance)
{
	if (A.Num() != B.Num()) return false;
	for (const auto& Pair : A)
	{
		const float* ValueInB = B.Find(Pair.Key);
		if (!ValueInB || !FMath::IsNearlyEqual(Pair.Value, *ValueInB, Tolerance))
			return false;
	}
	return true;
}

UMw_ItemInstance* UMw_InventoryComponent::DuplicateItemInstance(UMw_ItemInstance* Original, int32 NewStackCount)
{
	
	// 使用 NewObject 创建新实例，然后复制必要属性
	UMw_ItemInstance* NewInstance = NewObject<UMw_ItemInstance>(this, Original->GetClass());
	NewInstance->ItemDefinition = Original->ItemDefinition;
	NewInstance->AddToStackCount(NewStackCount) ;
	// 复制动态属性（如 Attributes）
	if (UMw_EquippableItemInstance* OriginalEquip = Cast<UMw_EquippableItemInstance>(Original))
	{
		UMw_EquippableItemInstance* NewEquip = Cast<UMw_EquippableItemInstance>(NewInstance);
		if (NewEquip)
		{
			NewEquip->Attributes = OriginalEquip->Attributes; // 浅拷贝 TMap，值类型是 float 没问题
			// 若有其他动态属性，一并复制
		}

	}
	else if (UMw_ConsumableItemInstance* OriginalConsume = Cast<UMw_ConsumableItemInstance>(Original))
	{
		UMw_ConsumableItemInstance* NewConsume = Cast<UMw_ConsumableItemInstance>(NewInstance);
		if (NewConsume)
		{
			// 浅拷贝 TMap，值类型是 float 没问题
			// 若有其他动态属性，一并复制
		}

	}
	else
	{
		
	}
	return NewInstance;
}



