// Copyright JNJ,  All Rights Reserved.


#include "UI/MwWidget/Inventory/Spatial/Mw_UserWidget_InventoryGrid.h"

#include "Mw_DebugHelper.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "FunctionLibrary/Mw_BFL_Widget.h"
#include "Items/Instances/Mw_ItemInstance.h"
#include "UI/MwWidget/Inventory/GridSlot/Mw_UserWidget_InventoryGridSlot.h"
#include "UI/MwWidget/Inventory/SlottedItems/Mw_UserWidget_InventorySlottedItem.h"
#include "UI/MwWidget/Inventory/Types/Mw_InventoryGridTypes.h"
#include "UI/WidgetController/Mw_WidgetController_Inventory.h"
#include "Components/Image.h"



void UMw_UserWidget_InventoryGrid::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	ConstructGrid();
	// 绑定库存控制器委托
	if (UMw_WidgetController_Inventory* InvController = UMw_BFL_Widget::GetWidgetController_InventoryMenu(GetWorld()))
	{
		InvController->OnInventoryControllerChange.AddUObject(this, &ThisClass::AddedItem);
	}
}

void UMw_UserWidget_InventoryGrid::ConstructGrid()
{
	GridSlots.Reserve(Rows * Columns);
	
	for (int32 j = 0; j < Columns; j++)
	{
		for (int32 i = 0; i < Rows; i++)
		{
			UMw_UserWidget_InventoryGridSlot* GridSlot = CreateWidget<UMw_UserWidget_InventoryGridSlot>(this,GridSlotClass);
			
			CanvasPanel->AddChild(GridSlot);
			
			const FIntPoint TilePosition(i,j);
			GridSlot->SetTileIndex(UMw_BFL_Widget::GetIndexFromPosition(TilePosition,Columns)) ;
			
			UCanvasPanelSlot* GridCPS = UWidgetLayoutLibrary::SlotAsCanvasSlot(GridSlot);
			// 设置网格大小
			GridCPS->SetSize(FVector2D(TileSize));
			GridCPS->SetPosition(TilePosition* TileSize);
			GridSlots.Add(GridSlot);
		}
	}
	
}




FInv_SlotAvailabilityResult UMw_UserWidget_InventoryGrid::HasRoomForItem(const UMw_ItemInstance* InItemInstance)
{
	//if (!InItemInstance) return FInv_SlotAvailabilityResult();
	
	FInv_SlotAvailabilityResult Result;
	// 物品是否可以堆叠
	Result.bStackable = InItemInstance->GetItemIsStackable();
	// 需要填充的数量
	int32 AmountToFill = Result.bStackable ? InItemInstance->StackCount : 1;
	// 最大允许填充的数量
	const int32 MaxStackSize = Result.bStackable ? InItemInstance->GetItemMaxStackSize() : 1;
	
	// 已检查的索引
	TSet<int32> CheckedIndices;  // 这里不用数组是因为数组可以存储相同的数组，而TSet只能存储不同的。
	
	for (const auto& GridSlot : GridSlots)
	{
		
		if (AmountToFill == 0) break;
		// 当前网格槽的索引是否存在已检查的索引集合中
		if (IsIndexClaimed(CheckedIndices,GridSlot->GetTileIndex())) continue;
		// 是否超出库存网格边界
		const FIntPoint Dimensions =  InItemInstance->GetItemIconDimensions();
		
		if (!IsInGridBounds(GridSlot->GetTileIndex(),Dimensions)) continue;
			
		// 存储临时指定的已检查索引
		TSet<int32> TentativelyClaimed;
		// 该物品能放在这里吗？（即是否超出网格边界？）
		if (!HasRoomAtIndex(GridSlot,Dimensions,CheckedIndices,TentativelyClaimed,InItemInstance->GetItemTypeTag(),MaxStackSize)) continue;
		
		// 物品占用多少空间
		const int32 AmountToFillInSlot = DetermineFillAmountForSlot(Result.bStackable,MaxStackSize,AmountToFill,GridSlot);
		if (AmountToFillInSlot == 0 ) continue;
		CheckedIndices.Append(TentativelyClaimed);
		//更新剩余需填充的数量
		Result.TotalRoomToFill += AmountToFillInSlot;
		Result.SlotAvailabilities.Emplace(
			FInv_SlotAvailability{
				HasValidItem(GridSlot) ? GridSlot->GetUpperLeftIndex() : GridSlot->GetTileIndex(),
				Result.bStackable ? AmountToFillInSlot : 0,
				HasValidItem(GridSlot)
			}
		);
		
		AmountToFill -= AmountToFillInSlot;
		// 剩下多少数量
		Result.Remainder = AmountToFill;
		
		if (AmountToFill == 0) return Result;
	}
	
	return Result;
}

void UMw_UserWidget_InventoryGrid::AddedItem(UMw_ItemInstance* InItemInStance)
{
	// 在添加物品的回调中，当物品被加入时，应该查找该物品是否与当前库存网格中的物品类别匹配，我们有一个用于存储物品类别的变量。
	if (!MatchesCategory(InItemInStance)) return;
	
	FInv_SlotAvailabilityResult Result = HasRoomForItem(InItemInStance);
	
	// 创建一个控件来显示物品图标，并将其添加到网格的正确位置。
	AddItemToIndices(Result, InItemInStance);
}

void UMw_UserWidget_InventoryGrid::AddItemToIndices(const FInv_SlotAvailabilityResult& InResult,
	UMw_ItemInstance* InItemInstance)
{
	for (const auto& Availability : InResult.SlotAvailabilities)
	{
		AddItemAtIndex(InItemInstance,Availability.Index,InResult.bStackable,Availability.AmountToFill);
		UpdateGridSlots(InItemInstance,Availability.Index,InResult.bStackable,Availability.AmountToFill);
	}
	
	
	
	// 我们将创建一个用于添加到网格的组件，并且我们将会加入到其中。
	// 我们需要创建新的组件存储在数组或其他容器中，以便后续可以移除。当物品被掉落时，消耗该物品、消耗该物品或其中任何一种操作。
}
void UMw_UserWidget_InventoryGrid::AddItemAtIndex(UMw_ItemInstance* InItemInstance, const int32 InIndex,
	const bool bStackable, const int32 StackAmount)
{

	UMw_UserWidget_InventorySlottedItem* SlottedItem = CreateSlottedItem(InItemInstance,bStackable,StackAmount,InIndex);
	// 将小部件存储到自己的容器之前，将其槽位项添加到画布面板中。
	AddSlottedItemToCanvas(InItemInstance,SlottedItem,InIndex);
	
	SlottedItemMap.Add(InIndex,SlottedItem);
	
}

UMw_UserWidget_InventorySlottedItem* UMw_UserWidget_InventoryGrid::CreateSlottedItem(UMw_ItemInstance* InItemInstance,
	const bool bStackable, const int32 StackAmount, int32 InIndex)
{
	if (!SlottedItemClass) return nullptr;
	UMw_UserWidget_InventorySlottedItem* SlottedItem = CreateWidget<UMw_UserWidget_InventorySlottedItem>(GetOwningPlayer(),SlottedItemClass);
	SlottedItem->SetInventoryItemInstance(InItemInstance);
	SetSlottedItemImage(InItemInstance,SlottedItem);
	SlottedItem->SetGridIndex(InIndex);
	SlottedItem->SetIsStackable(bStackable);
	const int32 StackUpdateAmount = bStackable ? StackAmount : 1;
	SlottedItem->UpdateStackCount(StackUpdateAmount);
	return SlottedItem;
}

void UMw_UserWidget_InventoryGrid::AddSlottedItemToCanvas(UMw_ItemInstance* InItemInstance,UMw_UserWidget_InventorySlottedItem* InSlottedItem, const int32 InIndex)
{
	CanvasPanel->AddChild(InSlottedItem);
	UCanvasPanelSlot* CanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(InSlottedItem);
	CanvasSlot->SetSize(GetDrawSize(InItemInstance));
	const FVector2D DrawPos = UMw_BFL_Widget::GetPositionFromIndex(InIndex,Columns) * TileSize;
	const FVector2D DrawPosWithPadding = DrawPos + FVector2D(InItemInstance->GetItemIconGridPadding());
	CanvasSlot->SetPosition(DrawPosWithPadding);
}

void UMw_UserWidget_InventoryGrid::UpdateGridSlots(UMw_ItemInstance* InItemInstance, const int32 InIndex,bool bStackableItem, const int32 InStackAmount)
{
	check(GridSlots.IsValidIndex(InIndex));
	
	if (!InItemInstance) return;
	
	if (bStackableItem)
	{
		GridSlots[InIndex]->SetStackCount(InStackAmount);
	}
	// 维度 
	const FIntPoint Dimensions = InItemInstance ? InItemInstance->GetItemIconDimensions() : FIntPoint(1,1);
	
	UMw_BFL_Widget::ForEach2D(GridSlots,InIndex,Dimensions,Columns,
		[&](UMw_UserWidget_InventoryGridSlot* GridSlot)
	{
			GridSlot->SetInventoryItem(InItemInstance);
			GridSlot->SetUpperLeftIndex(InIndex);
			GridSlot->SetOccupiedTexture();
			GridSlot->SetAvailable(false);
	});
	
	/*UMw_UserWidget_InventoryGridSlot* GridSlot = GridSlots[InIndex];
	GridSlot->SetOccupiedTexture();*/
}

bool UMw_UserWidget_InventoryGrid::IsIndexClaimed(const TSet<int32>& CheckedIndices, const int32 InIndex) const
{
	return CheckedIndices.Contains(InIndex);
}

bool UMw_UserWidget_InventoryGrid::HasRoomAtIndex(const UMw_UserWidget_InventoryGridSlot* GridSlot,
	const FIntPoint& Dimensions,const TSet<int32>& InCheckedIndices,TSet<int32>& OutTentativelyClaimed,
	const FGameplayTag& ItemTypeTag,const int32 InMaxStackSize)
{
	bool bHasRoomAtIndex = true;
	
	UMw_BFL_Widget::ForEach2D(GridSlots,GridSlot->GetTileIndex(),Dimensions,Columns,
		[&](const UMw_UserWidget_InventoryGridSlot* SubGridSlot)
		{
			
			if (CheckSlotConstraints(GridSlot,SubGridSlot,InCheckedIndices,OutTentativelyClaimed,ItemTypeTag,InMaxStackSize))
			{
				OutTentativelyClaimed.Add(SubGridSlot->GetTileIndex());
			}
			else
			{
				bHasRoomAtIndex = false;
			}
			
		});
	
	return bHasRoomAtIndex;
}

bool UMw_UserWidget_InventoryGrid::CheckSlotConstraints(const UMw_UserWidget_InventoryGridSlot* GridSlot,const UMw_UserWidget_InventoryGridSlot* SubGridSlot
	,const TSet<int32>& InCheckedIndices,TSet<int32>& OutTentativelyClaimed,const FGameplayTag& ItemTypeTag,
	const int32 InMaxStackSize) const
{
	// 索引声称
	if (IsIndexClaimed(InCheckedIndices,SubGridSlot->GetTileIndex())) return false;
	// 是否有效物品
	if (!HasValidItem(SubGridSlot))
	{
		OutTentativelyClaimed.Add(SubGridSlot->GetTileIndex());
		return true;
	}
	// 这个网格槽是在左上位置吗
	if (!IsUpperLeftSlot(GridSlot,SubGridSlot)) return false;
	
	// 是否可堆叠
	const UMw_ItemInstance* SubItemInstance = SubGridSlot->GetInventoryItemInstance().Get();
	if (!SubItemInstance->GetItemIsStackable()) return false;
	// 是否同一个类型
	if (!DoesItemTypeMatch(SubItemInstance,ItemTypeTag)) return false;
	// 如果这个槽位中已有物品，该槽位是否还有空间或已满
	if (GridSlot->GetStackCount() >= InMaxStackSize) return false;
	
	return true;
}

bool UMw_UserWidget_InventoryGrid::IsUpperLeftSlot(const UMw_UserWidget_InventoryGridSlot* GridSlot,
	const UMw_UserWidget_InventoryGridSlot* SubGridSlot) const
{
	return  SubGridSlot->GetUpperLeftIndex() == GridSlot->GetTileIndex();
}

bool UMw_UserWidget_InventoryGrid::HasValidItem(const UMw_UserWidget_InventoryGridSlot* GridSlot) const
{
	return GridSlot->GetInventoryItemInstance().IsValid();
}

bool UMw_UserWidget_InventoryGrid::DoesItemTypeMatch(const UMw_ItemInstance* InSubItemInstance,
	const FGameplayTag& ItemTypeTag) const
{
	return InSubItemInstance->GetItemTypeTag().MatchesTagExact(ItemTypeTag);
}

bool UMw_UserWidget_InventoryGrid::IsInGridBounds(const int32 StartIndex, const FIntPoint& ItemDimensions) const
{
	if (StartIndex <0 || StartIndex >= GridSlots.Num()) return false;
	const int32 EndColumn = (StartIndex % Columns)+ItemDimensions.X;
	const int32 EndRow = (StartIndex / Columns)+ItemDimensions.Y;
	return EndColumn <= Columns && EndRow <= Rows;
}

int32 UMw_UserWidget_InventoryGrid::DetermineFillAmountForSlot(const bool bStackable, const int32 MaxStackSize,
	const int32 AmountToFill, const UMw_UserWidget_InventoryGridSlot* GridSlot) const
{
	const int32 RoomInSlot = MaxStackSize - GetStackAmount(GridSlot);
	return bStackable ? FMath::Min(AmountToFill,RoomInSlot) : 1;
}

int32 UMw_UserWidget_InventoryGrid::GetStackAmount(const UMw_UserWidget_InventoryGridSlot* GridSlot) const
{
	int32 CurrentSlotStackCount = GridSlot->GetStackCount();
	// 如果当前处于不包含堆栈计数的槽位，我们必须获取实际的堆栈计数。
	if (const int32 UpperLeftIndex = GridSlot->GetUpperLeftIndex(); UpperLeftIndex != INDEX_NONE)
	{
		UMw_UserWidget_InventoryGridSlot* UpperLeftGridSlot = GridSlots[UpperLeftIndex];
		CurrentSlotStackCount = UpperLeftGridSlot->GetStackCount();
	}
	return CurrentSlotStackCount;
}

bool UMw_UserWidget_InventoryGrid::MatchesCategory(const UMw_ItemInstance* Item) const
{
	return Item->GetItemTypeTag() == GridItemType;
}

FVector2D UMw_UserWidget_InventoryGrid::GetDrawSize(const UMw_ItemInstance* InItemInstance) const
{
	const float IconTleWidth = TileSize - InItemInstance->GetItemIconGridPadding() *2;
	return  InItemInstance->GetItemIconDimensions() * IconTleWidth;
}

void UMw_UserWidget_InventoryGrid::SetSlottedItemImage(const UMw_ItemInstance* InItemInstance,const UMw_UserWidget_InventorySlottedItem* InSlottedItem) const
{
	if (!InSlottedItem) return;
	UImage* IconImage = InSlottedItem->GetImageIcon();
	if (!IconImage) return;

	// 直接使用 UImage 的成员函数设置软引用纹理（自动异步加载）
	IconImage->SetBrushFromSoftTexture(InItemInstance->GetItemIconSoft());

	// 如果你需要自定义绘制大小，可以获取当前笔刷并修改
	FSlateBrush CurrentBrush = IconImage->GetBrush();
	CurrentBrush.ImageSize = GetDrawSize(InItemInstance);
	IconImage->SetBrush(CurrentBrush);
	
	/* // 这里因为图标是软引用，这样使用会出现空指针。
	 *FSlateBrush Brush;
	
	Brush.SetResourceObject(InItemInstance->GetDisplayInfo().IconSoftPtr.Get());
	Brush.DrawAs = ESlateBrushDrawType::Image;
	Brush.ImageSize = GetDrawSize(InItemInstance);
	InSlottedItem->SetImageIconBrush(Brush);*/
}


void UMw_UserWidget_InventoryGrid::AddItemInstance(UMw_ItemInstance* InItemInstance, FGameplayTag InItemTypeTag)
{
	if (!InItemInstance) return;
	// 关键：只处理匹配当前网格分类的物品
	if (InItemTypeTag != GridItemType) return;
	
	// 1. 检查物品是否已经在网格中的某个槽位
	for (UMw_UserWidget_InventoryGridSlot* GridSlot : GridSlots)
	{
		
		UE_LOG(LogTemp, Warning, TEXT("Item already in grid, skipping."));
		return;
	
	}
	
	// 2. 查找第一个空槽位
	for (UMw_UserWidget_InventoryGridSlot* GridSlot : GridSlots)
	{
	}

	// 网格已满
	UE_LOG(LogTemp, Warning, TEXT("Inventory grid is full, cannot add item."));
}
