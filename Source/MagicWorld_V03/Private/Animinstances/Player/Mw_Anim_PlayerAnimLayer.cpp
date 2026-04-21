// Copyright JNJ,  All Rights Reserved.


#include "Animinstances/Player/Mw_Anim_PlayerAnimLayer.h"

#include "Animinstances/Player/Mw_Anim_Player.h"

UMw_Anim_Player* UMw_Anim_PlayerAnimLayer::GetAnimPlayer() const
{
	return Cast<UMw_Anim_Player>(GetOwningComponent()->GetAnimInstance());
}
