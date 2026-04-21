// Copyright JNJ,  All Rights Reserved.


#include "MagicWorld_V03/Public/Items/Assets/Mw_ItemDefinition.h"

#include "Items/Mw_ItemTags.h"


UMw_ItemDefinition::UMw_ItemDefinition()
{
	ItemTypeTag = Mw_ItemTags::Item_Type_Basic;
	ItemRarityTag = Mw_ItemTags::Item_Rarity_Common;
}

FPrimaryAssetId UMw_ItemDefinition::GetPrimaryAssetId() const
{
	
	// 将数据资产的主要ID定义 ， 例子  Item.Category.Equippable.Weapon.OneHandedSword:DA_TestItem  DA_TestItem在虚幻编辑器中的文件名
	return FPrimaryAssetId(ItemCategoryTag.GetTagName(),GetFName());
}
