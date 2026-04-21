// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Mw_HighlightItemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UMw_HighlightItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MAGICWORLD_V03_API IMw_HighlightItemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MagicWorld|Mw_HighlightItemInterface")
	void HighlightItem();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MagicWorld|Mw_HighlightItemInterface")
	void UnHighlightItem();
};
