// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "Logging/LogMacros.h"

class UObject;

MAGICWORLD_V03_API DECLARE_LOG_CATEGORY_EXTERN(LogMw, Log, All);
MAGICWORLD_V03_API DECLARE_LOG_CATEGORY_EXTERN(LogMwTemp, Log, All);
MAGICWORLD_V03_API DECLARE_LOG_CATEGORY_EXTERN(LogMwExperience, Log, All);
MAGICWORLD_V03_API DECLARE_LOG_CATEGORY_EXTERN(LogMwAbilitySystem, Log, All);
MAGICWORLD_V03_API DECLARE_LOG_CATEGORY_EXTERN(LogMwTeams, Log, All);

MAGICWORLD_V03_API FString GetClientServerContextString(UObject* ContextObject = nullptr);