// Copyright (C) Helm Boy Studios. 2022. All Rights Reserved.


#include "ModUtils.h"
#include <modio/detail/ModioSDKSessionData.h>
#include <modio/file/ModioFileService.h>
#include <modio/impl/SDKPreconditionChecks.h>

bool UModUtils::IsApiInitialized() 
{
	return Modio::Detail::SDKSessionData::IsInitialized();
}

bool UModUtils::IsUserAuthenticated()
{
	return  Modio::Detail::SDKSessionData::GetAuthenticatedUser().has_value()  && (Modio::Detail::SDKSessionData::GetAuthenticatedUser().value().UserId != 0) ; 
}

int64 UModUtils::GetUserID()
{
	if(IsUserAuthenticated())
	{
		return Modio::Detail::SDKSessionData::GetAuthenticatedUser()->UserId;
	}
	return -1;
}

bool UModUtils::IsModManagementEnabled()
{
	return Modio::Detail::SDKSessionData::IsModManagementEnabled();
}

FString UModUtils::GetUserDataPath()
{
	
	Modio::Detail::FileService& FileService =
					Modio::Detail::Services::GetGlobalService<Modio::Detail::FileService>();

	return FileService.UserDataFolder().generic_u8string().c_str();
	

}

FString UModUtils::GetUserModCachePath()
{

	return Modio::Detail::SDKSessionData::GetUserModDirectoryOverride().has_value() ?Modio::Detail::SDKSessionData::GetUserModDirectoryOverride().value().generic_u8string().c_str() : GetUserDataPath() ;
}
