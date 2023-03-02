// Copyright (C) Helm Boy Studios. 2022. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types/ModioModInfo.h"


namespace HeliosModDownload
{
	bool StartModDownload(const FModioModInfo ModInfo);
	
	bool StartModUninstall(const FModioModID ModId);
}
