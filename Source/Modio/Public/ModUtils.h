// Copyright (C) Helm Boy Studios. 2022. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ModUtils.generated.h"

/**
 * 
 */
UCLASS()
class MODIO_API UModUtils : public UObject
{
	GENERATED_BODY()

public:

	static bool IsApiInitialized() ;
	static bool IsUserAuthenticated() ;
	static int64 GetUserID();
	static bool IsModManagementEnabled() ;
	static FString GetUserDataPath();
	static FString GetUserModCachePath();
};
