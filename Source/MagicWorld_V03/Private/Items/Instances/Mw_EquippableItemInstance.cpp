// Copyright JNJ,  All Rights Reserved.


#include "Items/Instances/Mw_EquippableItemInstance.h"

float UMw_EquippableItemInstance::GetAttributeValue(const FGameplayTag& InAttributeTag) const
{
	if (Attributes.Contains(InAttributeTag))
	{
		return Attributes[InAttributeTag];
	}
	return 0.0f;
}

bool UMw_EquippableItemInstance::OnPickup_Implementation(AActor* PickupActor, int32 Quantity)
{
	// 播放音效
	// UGameplayStatics::PlaySound2D(this, PickupSound);
	// 增加成就
	// ...
	// 返回 true，让默认库存添加继续执行
	return true;
	
	// 也可以 如果某个物品希望完全接管拾取（例如拾取后直接传送到其他位置，不加入背包），可以返回 false 并自行处理
	// 自定义传送逻辑
	// ...
	// 返回 false 告诉掉落物 Actor 不要执行默认库存添加
	//return false;
}
