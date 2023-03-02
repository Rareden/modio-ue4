// Copyright (C) Helm Boy Studios. 2022. All Rights Reserved.


#include "HandleModDownlod.h"

#include <asio/unyield.hpp>
#include <modio/detail/ModioSDKSessionData.h>
#include <modio/file/ModioFileService.h>
#include "Internal/Convert/ModInfo.h"
#include "Internal/ModioConvert.h"

#include <modio/detail/ops/modmanagement/UninstallMod.h>


// Sets default values
bool HeliosModDownload::StartModDownload(const FModioModInfo ModInfo)
{
	// auto Func =[this](Modio::ErrorCode Error) {
	//
	// 	UE_LOG(LogTemp,Display,TEXT("Download Callback"));
	// 	FString Msg=FString(UTF8_TO_TCHAR(Error.message().c_str()));
	// 	
	// 	UE_LOG(LogTemp,Display,TEXT("%s \n") ,*Msg);
	// };
	//
	// Modio::Detail::InstallOrUpdateModAsync(ToModio(ModId),std::move(Func));
	// HeliosModDownload::StartModDownload()
	//
	// if(Modio::Optional<const Modio::ModProgressInfo> PendingDownload = Modio::Detail::SDKSessionData::GetModProgress())
	// {
	// 	FModioModProgressInfo DownloadInfo = ToUnreal(*PendingDownload);
	// 	
	// 	UE_LOG(LogTemp,Display,TEXT("CurrentMod Download: ModID=%s,  Size=%i"),*DownloadInfo.ID.ToString(), DownloadInfo.CurrentlyDownloadedBytes)
	// 	return false;
	// }
	// else
	// {
	// 	std::weak_ptr<Modio::ModProgressInfo> NewDownload= Modio::Detail::SDKSessionData::StartModDownloadOrUpdate(ToModio(ModId));
	// 	return !NewDownload.expired();
	// 	
	// }
	// return false;
	// Modio::Detail::SDKSessionData::GetSystemModCollection().AddOrUpdateMod(
	// 							ProfileData.value(),
	// 							Modio::Detail::Services::GetGlobalService<Modio::Detail::FileService>().MakeModPath(
	// 								ProfileData->ModId));
	Modio::ModInfo NativeModInfo ;
	NativeModInfo.ModId=ToModio(ModInfo.ModId);
	NativeModInfo.ProfileName=TCHAR_TO_UTF8(*ModInfo.ProfileName);
	NativeModInfo.ProfileSummary=TCHAR_TO_UTF8(*ModInfo.ProfileSummary);
	NativeModInfo.ProfileDescription=TCHAR_TO_UTF8(*ModInfo.ProfileDescription);
	NativeModInfo.ProfileDescriptionPlaintext=TCHAR_TO_UTF8(*ModInfo.ProfileDescriptionPlaintext);
	NativeModInfo.ProfileURL=TCHAR_TO_UTF8(*ModInfo.ProfileURL);
	NativeModInfo.ProfileSubmittedBy.UserId=  ToModio(ModInfo.ProfileSubmittedBy.UserId);
	NativeModInfo.ProfileSubmittedBy.Username= TCHAR_TO_UTF8(*ModInfo.ProfileSubmittedBy.Username);
	
	
	const bool WasAdded = Modio::Detail::SDKSessionData::GetSystemModCollection().AddOrUpdateMod(NativeModInfo,
		Modio::Detail::Services::GetGlobalService<Modio::Detail::FileService>().MakeModPath(NativeModInfo.ModId).generic_string());

	
	return true;
}

bool HeliosModDownload::StartModUninstall(const FModioModID ModId)
{
	Modio::Optional<Modio::ModCollectionEntry&> ModEntry= Modio::Detail::SDKSessionData::GetSystemModCollection()
		.GetByModID(ToModio(ModId));
	if(ModEntry)
	{
		
		if(ModEntry->GetModState() != Modio::ModState::UninstallPending)
			ModEntry->SetModState(Modio::ModState::UninstallPending);

		return ModEntry->GetModState() == Modio::ModState::UninstallPending;
		
		//return Modio::Detail::SDKSessionData::GetSystemModCollection().RemoveMod(ToModio(ModId));
	}
	
	return false;
}
