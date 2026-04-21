// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Mw_CharacterMovementComponent.generated.h"


/**
 * 关于字符下方地面的信息。它仅在需要时进行更新。
 */
USTRUCT(BlueprintType)
struct FMw_CharacterGroundInfo
{
	GENERATED_BODY()

	FMw_CharacterGroundInfo()
		: LastUpdateFrame(0)
		, GroundDistance(0.0f)
	{}

	uint64 LastUpdateFrame;

	UPROPERTY(BlueprintReadOnly)
	FHitResult GroundHitResult;

	UPROPERTY(BlueprintReadOnly)
	float GroundDistance;
};

/**
 * 该项目所使用的基础字符移动组件类
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MAGICWORLD_V03_API UMw_CharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	
	UMw_CharacterMovementComponent();

	// 返回当前地面信息。调用此功能会更新过时的地面信息。
	UFUNCTION(BlueprintCallable, Category = "MagicWord|CharacterMovement")
	const FMw_CharacterGroundInfo& GetGroundInfo();
	
protected:
	
	// 角色的缓存地面信息。请勿直接访问！--仅在通过 GetGroundInfo() 访问时才会更新。
	FMw_CharacterGroundInfo CachedGroundInfo;
};
