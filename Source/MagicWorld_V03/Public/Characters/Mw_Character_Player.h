// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Mw_Character_Base.h"
#include "Mw_Character_Player.generated.h"

class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class MAGICWORLD_V03_API AMw_Character_Player : public AMw_Character_Base
{
	GENERATED_BODY()
	
public:
	
	AMw_Character_Player();
	
	/**
	 * 接下来是玩家控制角色的ASC初始化，玩家控制角色按照文档说法，我们需要在AvatarActor里面进行初始化。
	 *如果ASC存在于PlayerState中，我需要在AvatarActor覆盖PossessedBy和OnRep_PlayerState两个函数，然后添加私有初始化函数InitAbilityActorInfo（初始化的内容相同
	 */
	virtual void PossessedBy(AController* NewController) override; // 服务器初始化ASC
	
	
protected:
	
	/**
	 * 继承Mw_BaseCharacger
	 * 玩家的playerState和character里面存储的ASC和AS需要相同，我们可以在初始化玩家Character的时候，从PlayerState里获取ASC和AS
	 */
	virtual void InitAbilityActorInfo() override;
	
private:
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Camera",meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Camera",meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
};
