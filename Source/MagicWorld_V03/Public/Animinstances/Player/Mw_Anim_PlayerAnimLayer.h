// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animinstances/Mw_Anim_Base.h"
#include "Mw_Anim_PlayerAnimLayer.generated.h"

class UMw_Anim_Player;
/**
 * 
 */
UCLASS()
class MAGICWORLD_V03_API UMw_Anim_PlayerAnimLayer : public UMw_Anim_Base
{
	GENERATED_BODY()
	
public:
	
	// Meta = (NotBlueprintThreadSafe) 属性内部访问节点使用这个函数，为了使这个函数显示，需要同时是BlueprintPure和BlueprintThreadSafe

	/**
	 * 
	 * 通过GetOwningComponent()->GetAnimInstance() 来获取并且强制转换为UPlayerAnimInstances
	 * 这样可以获取到相关UPlayerAnimInstances的属性和方法
	 **/
	UFUNCTION(BlueprintPure, Meta = (NotBlueprintThreadSafe),Category = "MagicWorld|MwAnimInstance_PlayerAnimLayer")
	UMw_Anim_Player* GetAnimPlayer() const;
};
