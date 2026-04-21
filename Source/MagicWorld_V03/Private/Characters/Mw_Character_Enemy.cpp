// Copyright JNJ,  All Rights Reserved.


#include "Characters/Mw_Character_Enemy.h"

#include "AbilitySystem/Mw_AbilitySystemComponent.h"
#include "AbilitySystem/Mw_AttributeSet_Base.h"

AMw_Character_Enemy::AMw_Character_Enemy()
{
	// 敌人的OwnerActor和AvatarActor是相同的，我们直接在敌人的基类的构造函数里面对ASC和AS实例化
	MwAbilitySystemComponent = CreateDefaultSubobject<UMw_AbilitySystemComponent>("MwAbilitySystemComponent");

	MwAttributeSet = CreateDefaultSubobject<UMw_AttributeSet_Base>("MwAttributeSet");
}

void AMw_Character_Enemy::BeginPlay()
{
	Super::BeginPlay();
	
	InitAbilityActorInfo();
}

void AMw_Character_Enemy::InitAbilityActorInfo()
{
	/**
	*对于AI控制的角色，ASC存在于Pawn中，通常在Pawn的 BeginPlay()方法中完成ASC在服务器端和客户端的初始化。
	*既然根据文档知道了如何初始化，那么，我们按照相应的方式初始化。首先初始化敌人身上的ASC，敌人作为ai怪物，只需要在BeginPlay里面初始化即可
	*/
	MwAbilitySystemComponent->InitAbilityActorInfo(this,this);
}
