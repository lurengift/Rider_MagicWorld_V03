// Copyright JNJ,  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Logging/LogMacros.h"
#include "Mw_LogChannels.h"
#include "Mw_DebugHelper.generated.h"

UENUM(BlueprintType)
enum class EMwLogType : uint8
{
	LogMw,
	LogMwTemp,
	LogMwExperience,
	LogMwAbilitySystem,
	LogMwTeams
};
namespace  Debug
{
	// 使用ELogVerbosity::Type枚举的版本
	static void Print(const FString& Msg,EMwLogType Mw_LogType = EMwLogType::LogMwTemp, ELogVerbosity::Type LogVerbosity = ELogVerbosity::Display, 
					 bool ShowScreen = false,int32 InKey = -1, const FColor& InColor = FColor::MakeRandomColor())
	{
		if (GEngine)
		{
	
			if (Mw_LogType == EMwLogType::LogMw)
			{
				if (ShowScreen)
				{
					GEngine->AddOnScreenDebugMessage(InKey, 7.f, InColor, Msg);
				}
				
				// 根据LogVerbosity使用不同的UE_LOG宏
				switch (LogVerbosity)
				{
				case ELogVerbosity::Fatal:
					UE_LOG(LogMw, Fatal, TEXT("%s"), *Msg);
					break;
				case ELogVerbosity::Error:
					UE_LOG(LogMw, Error, TEXT("%s"), *Msg);
					break;
				case ELogVerbosity::Warning:
					UE_LOG(LogMw, Warning, TEXT("%s"), *Msg);
					break;
				case ELogVerbosity::Display:
					UE_LOG(LogMw, Display, TEXT("%s"), *Msg);
					break;
				case ELogVerbosity::Log:
					UE_LOG(LogMw, Log, TEXT("%s"), *Msg);
					break;
				case ELogVerbosity::Verbose:
					UE_LOG(LogMw, Verbose, TEXT("%s"), *Msg);
					break;
				case ELogVerbosity::VeryVerbose:
					UE_LOG(LogMw, VeryVerbose, TEXT("%s"), *Msg);
					break;
				default:
					UE_LOG(LogMw, Log, TEXT("%s"), *Msg);
					break;
				}
			}
			if (Mw_LogType == EMwLogType::LogMwTemp)
			{
				if (ShowScreen)
				{
					GEngine->AddOnScreenDebugMessage(InKey, 7.f, InColor, Msg);
				}
            
				// 根据LogVerbosity使用不同的UE_LOG宏
				switch (LogVerbosity)
				{
				case ELogVerbosity::Fatal:
					UE_LOG(LogMwTemp, Fatal, TEXT("%s"), *Msg);
					break;
				case ELogVerbosity::Error:
					UE_LOG(LogMwTemp, Error, TEXT("%s"), *Msg);
					break;
				case ELogVerbosity::Warning:
					UE_LOG(LogMwTemp, Warning, TEXT("%s"), *Msg);
					break;
				case ELogVerbosity::Display:
					UE_LOG(LogMwTemp, Display, TEXT("%s"), *Msg);
					break;
				case ELogVerbosity::Log:
					UE_LOG(LogMwTemp, Log, TEXT("%s"), *Msg);
					break;
				case ELogVerbosity::Verbose:
					UE_LOG(LogMwTemp, Verbose, TEXT("%s"), *Msg);
					break;
				case ELogVerbosity::VeryVerbose:
					UE_LOG(LogMwTemp, VeryVerbose, TEXT("%s"), *Msg);
					break;
				default:
					UE_LOG(LogMwTemp, Log, TEXT("%s"), *Msg);
					break;
				}
			}
			if (Mw_LogType == EMwLogType::LogMwExperience)
			{
				if (ShowScreen)
				{
					GEngine->AddOnScreenDebugMessage(InKey, 7.f, InColor, Msg);
				}
            
				// 根据LogVerbosity使用不同的UE_LOG宏
				switch (LogVerbosity)
				{
				case ELogVerbosity::Fatal:
					UE_LOG(LogMwExperience, Fatal, TEXT("%s"), *Msg);
					break;
				case ELogVerbosity::Error:
					UE_LOG(LogMwExperience, Error, TEXT("%s"), *Msg);
					break;
				case ELogVerbosity::Warning:
					UE_LOG(LogMwExperience, Warning, TEXT("%s"), *Msg);
					break;
				case ELogVerbosity::Display:
					UE_LOG(LogMwExperience, Display, TEXT("%s"), *Msg);
					break;
				case ELogVerbosity::Log:
					UE_LOG(LogMwExperience, Log, TEXT("%s"), *Msg);
					break;
				case ELogVerbosity::Verbose:
					UE_LOG(LogMwExperience, Verbose, TEXT("%s"), *Msg);
					break;
				case ELogVerbosity::VeryVerbose:
					UE_LOG(LogMwExperience, VeryVerbose, TEXT("%s"), *Msg);
					break;
				default:
					UE_LOG(LogMwExperience, Log, TEXT("%s"), *Msg);
					break;
				}
			}
			if (Mw_LogType == EMwLogType::LogMwAbilitySystem)
			{
				if (ShowScreen)
				{
					GEngine->AddOnScreenDebugMessage(InKey, 7.f, InColor, Msg);
				}
            
				// 根据LogVerbosity使用不同的UE_LOG宏
				switch (LogVerbosity)
				{
				case ELogVerbosity::Fatal:
					UE_LOG(LogMwAbilitySystem, Fatal, TEXT("%s"), *Msg);
					break;
				case ELogVerbosity::Error:
					UE_LOG(LogMwAbilitySystem, Error, TEXT("%s"), *Msg);
					break;
				case ELogVerbosity::Warning:
					UE_LOG(LogMwAbilitySystem, Warning, TEXT("%s"), *Msg);
					break;
				case ELogVerbosity::Display:
					UE_LOG(LogMwAbilitySystem, Display, TEXT("%s"), *Msg);
					break;
				case ELogVerbosity::Log:
					UE_LOG(LogMwAbilitySystem, Log, TEXT("%s"), *Msg);
					break;
				case ELogVerbosity::Verbose:
					UE_LOG(LogMwAbilitySystem, Verbose, TEXT("%s"), *Msg);
					break;
				case ELogVerbosity::VeryVerbose:
					UE_LOG(LogMwAbilitySystem, VeryVerbose, TEXT("%s"), *Msg);
					break;
				default:
					UE_LOG(LogMwAbilitySystem, Log, TEXT("%s"), *Msg);
					break;
				}
			}
			if (Mw_LogType == EMwLogType::LogMwTeams)
			{
				if (ShowScreen)
				{
					GEngine->AddOnScreenDebugMessage(InKey, 7.f, InColor, Msg);
				}
            
				// 根据LogVerbosity使用不同的UE_LOG宏
				switch (LogVerbosity)
				{
				case ELogVerbosity::Fatal:
					UE_LOG(LogMwTeams, Fatal, TEXT("%s"), *Msg);
					break;
				case ELogVerbosity::Error:
					UE_LOG(LogMwTeams, Error, TEXT("%s"), *Msg);
					break;
				case ELogVerbosity::Warning:
					UE_LOG(LogMwTeams, Warning, TEXT("%s"), *Msg);
					break;
				case ELogVerbosity::Display:
					UE_LOG(LogMwTeams, Display, TEXT("%s"), *Msg);
					break;
				case ELogVerbosity::Log:
					UE_LOG(LogMwTeams, Log, TEXT("%s"), *Msg);
					break;
				case ELogVerbosity::Verbose:
					UE_LOG(LogMwTeams, Verbose, TEXT("%s"), *Msg);
					break;
				case ELogVerbosity::VeryVerbose:
					UE_LOG(LogMwTeams, VeryVerbose, TEXT("%s"), *Msg);
					break;
				default:
					UE_LOG(LogMwTeams, Log, TEXT("%s"), *Msg);
					break;
				}
			}
		
		}
	}
}
