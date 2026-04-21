// Copyright JNJ,  All Rights Reserved.


#include "Items/Mw_ItemTags.h"


namespace Mw_ItemTags
{
	UE_DEFINE_GAMEPLAY_TAG(Item, "Item");
	
	UE_DEFINE_GAMEPLAY_TAG(Item_Type, "Item.Type");
	UE_DEFINE_GAMEPLAY_TAG(Item_Type_Basic, "Item.Type.Basic");
	UE_DEFINE_GAMEPLAY_TAG(Item_Type_Equippable, "Item.Type.Equippable");
	UE_DEFINE_GAMEPLAY_TAG(Item_Type_Consumable, "Item.Type.Consumable");
	UE_DEFINE_GAMEPLAY_TAG(Item_Type_Craftable, "Item.Type.Craftable");
	
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Item_Rarity, "Item.Rarity", "Item 稀有度");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Item_Rarity_Common, "Item.Rarity.Common", "Item 普通的");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Item_Rarity_UnCommon, "Item.Rarity.UnCommon", "Item 奇特的");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Item_Rarity_Rare, "Item.Rarity.Rare", "Item 稀有的");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Item_Rarity_Epic, "Item.Rarity.Epic", "Item 史诗的");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Item_Rarity_Legendary, "Item.Rarity.Legendary", "Item 传说的");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Item_Category, "Item.Category", "Item 物品分类");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Item_Category_Equippable, "Item.Category.Equippable", "Item 物品分类 可装备");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Item_Category_Equippable_Weapon, "Item.Category.Equippable.Weapon", "Item 物品分类 可装备");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Item_Category_Equippable_Weapon_OneHandedSword, "Item.Category.Equippable.Weapon.OneHandedSword", "Item 物品分类 可装备 单手剑");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Item_Category_Equippable_Weapon_OneHandedSword_L, "Item.Category.Equippable.Weapon.OneHandedSword.L", "Item 物品分类 可装备 单手剑 左手");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Item_Category_Equippable_Weapon_OneHandedSword_R, "Item.Category.Equippable.Weapon.OneHandedSword.R", "Item 物品分类 可装备 单手剑 右手");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Item_Category_Equippable_Weapon_DoubleHandedSword, "Item.Category.Equippable.Weapon.DoubleHandedSword", "Item 物品分类 可装备 双手剑");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Item_Category_Consumable, "Item.Category.Consumable", "Item 物品分类 可消耗");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Item_Category_Craftable, "Item.Category.Craftable", "Item 物品分类 可制作");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Item_Category_None, "Item.Category.None", "Item 物品分类 没有分类");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Item_EquipmentSlot, "Item.EquipmentSlot", "Item 装备插槽");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Item_EquipmentSlot_Head, "Item.EquipmentSlot.Head", "Item 装备插槽 头部");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Item_EquipmentSlot_Hand_LeftAndRight, "Item.EquipmentSlot.Hand.LeftAndRight", "Item 装备插槽 手部 双手");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Item_EquipmentSlot_Hand_Left, "Item.EquipmentSlot.Hand.Left", "Item 装备插槽 手部 左手");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Item_EquipmentSlot_Hand_Right, "Item.EquipmentSlot.Hand.Right", "Item 装备插槽 手部 右手");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Item_EquipmentSlot_Chest, "Item.EquipmentSlot.Chest", "Item 装备插槽 胸部");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Item_EquipmentSlot_Feet, "Item.EquipmentSlot.Feet", "Item 装备插槽 脚部");

	

}
