// Copyright JNJ,  All Rights Reserved.


#include "Mw_GameplayTags.h"

/**
 * UE_DEFINE_GAMEPLAY_TAG_COMMENT 可以在后面编写备注
 * UE_DEFINE_GAMEPLAY_TAG 不编写备注
 */
namespace Mw_GameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(MwAbilities_Strategy_OnlyGiven, "MwAbilities.Strategy.OnlyGiven", "Abilities Activate Strategy: Only Give");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(MwAbilities_Strategy_GiveAndActivate, "MwAbilities.Strategy.GiveAndActivate", "Abilities Activate Strategy: Give And Activate");
	
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Crouch, "InputTag.Crouch");
	UE_DEFINE_GAMEPLAY_TAG(Input_ToggleInventory, "InputTag.ToggleInventory");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Interact, "InputTag.Interact");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Equip, "InputTag.Equip");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_UnEquip, "InputTag.UnEquip");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable, "InputTag.Toggleable");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable_TargetLock, "InputTag.Toggleable.TargetLock");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_LMB, "InputTag.LMB");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_RMB, "InputTag.RMB");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Shift, "InputTag.Shift");
	
	UE_DEFINE_GAMEPLAY_TAG(InputState_Trigger, "InputState.Trigger");
	UE_DEFINE_GAMEPLAY_TAG(InputState_Complete, "InputState.Complete");
	
	UE_DEFINE_GAMEPLAY_TAG(Ability_Interact, "Ability.Interact");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Equip, "Ability.Equip");
	UE_DEFINE_GAMEPLAY_TAG(Ability_UnEquip, "Ability.UnEquip");
	UE_DEFINE_GAMEPLAY_TAG(Ability_ComboX, "Ability.ComboX");
	UE_DEFINE_GAMEPLAY_TAG(Ability_ComboXX, "Ability.ComboXX");
	UE_DEFINE_GAMEPLAY_TAG(Ability_ComboXXX, "Ability.ComboXXX");
	UE_DEFINE_GAMEPLAY_TAG(Ability_ComboXY, "Ability.ComboXY");
	UE_DEFINE_GAMEPLAY_TAG(Ability_ComboY, "Ability.ComboY");
	
	UE_DEFINE_GAMEPLAY_TAG(Ability_Action_Roll, "Ability.Action.Roll");
	
	UE_DEFINE_GAMEPLAY_TAG(Status_Equip_Weapon_Left, "Status.Equip.Weapon.Left");
	UE_DEFINE_GAMEPLAY_TAG(Status_Equip_Weapon_Right, "Status.Equip.Weapon.Right");
	UE_DEFINE_GAMEPLAY_TAG(Status_Equip_Weapon_Double, "Status.Equip.Weapon.Double");
	
	UE_DEFINE_GAMEPLAY_TAG(Status_UnEquip_Weapon_Left, "Status.UnEquip.Weapon.Left");
	UE_DEFINE_GAMEPLAY_TAG(Status_UnEquip_Weapon_Right, "Status.UnEquip.Weapon.Right");
	UE_DEFINE_GAMEPLAY_TAG(Status_UnEquip_Weapon_Double, "Status.UnEquip.Weapon.Double");
	
	UE_DEFINE_GAMEPLAY_TAG(ANS_Window_Combo, "ANS.Window.Combo");
	
	UE_DEFINE_GAMEPLAY_TAG(AN_Event_Interact, "AN.Event.Interact");
	UE_DEFINE_GAMEPLAY_TAG(ANS_Window_CantRoll, "ANS.Window.CantRoll");
	
	UE_DEFINE_GAMEPLAY_TAG(ActionState_Equip, "ActionState.Equip");
	UE_DEFINE_GAMEPLAY_TAG(ActionState_UnEquip, "ActionState.UnEquip");
	
	UE_DEFINE_GAMEPLAY_TAG(ActionState_Start, "ActionState.Start");
	UE_DEFINE_GAMEPLAY_TAG(ActionState_Comboing, "ActionState.Comboing");
	
	
	UE_DEFINE_GAMEPLAY_TAG(Event_Movement_TargetLock, "Event.Movement.TargetLock");
	UE_DEFINE_GAMEPLAY_TAG(Event_Movement_ADS, "Event.Movement.ADS");
	UE_DEFINE_GAMEPLAY_TAG(Event_Movement_WeaponFire, "Event.Movement.WeaponFire");
	UE_DEFINE_GAMEPLAY_TAG(Event_Movement_Reload, "Event.Movement.Reload");
	UE_DEFINE_GAMEPLAY_TAG(Event_Movement_Dash, "Event.Movement.Dash");
	UE_DEFINE_GAMEPLAY_TAG(Event_Movement_Melee, "Event.Movement.Melee");
	
	UE_DEFINE_GAMEPLAY_TAG(State_Movement_Walking, "State.Movement.Walking");
	UE_DEFINE_GAMEPLAY_TAG(State_Movement_Jogging, "State.Movement.Jogging");
	UE_DEFINE_GAMEPLAY_TAG(State_Movement_Running, "State.Movement.Running");
	
	UE_DEFINE_GAMEPLAY_TAG(Message_HealthCrystal, "Message.HealthCrystal");
	UE_DEFINE_GAMEPLAY_TAG(Message_HealthPotion, "Message.HealthPotion");
	UE_DEFINE_GAMEPLAY_TAG(Message_ManaPotion, "Message.ManaPotion");
	UE_DEFINE_GAMEPLAY_TAG(Message_StaminaPotion, "Message.StaminaPotion");

	UE_DEFINE_GAMEPLAY_TAG(Attributes_Primary_Vitality, "Attributes.Primary.Vitality");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Primary_Concentration, "Attributes.Primary.Concentration");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Primary_Endurance, "Attributes.Primary.Endurance");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Primary_Strength, "Attributes.Primary.Strength");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Primary_Dexterity, "Attributes.Primary.Dexterity");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Primary_Intelligence, "Attributes.Primary.Intelligence");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Primary_Faith, "Attributes.Primary.Faith");
	
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Vital_Health, "Attributes.Vital.Health");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Vital_MaxHealth, "Attributes.Vital.MaxHealth");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Vital_Mana, "Attributes.Vital.Mana");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Vital_MaxMana, "Attributes.Vital.MaxMana");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Vital_Stamina, "Attributes.Vital.Stamina");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Vital_MaxStamina, "Attributes.Vital.MaxStamina");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Vital_Weight, "Attributes.Vital.Weight");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Vital_MaxWeight, "Attributes.Vital.MaxWeight");
	
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Combat_Attack, "Attributes.Combat.Attack");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Combat_Defense, "Attributes.Combat.Defense");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Combat_MagicAttack, "Attributes.Combat.MagicAttack");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Combat_MagicDefense, "Attributes.Combat.MagicDefense");
}