// Fill out your copyright notice in the Description page of Project Settings.

#include "XDSettingLib.h"

#if (UE_EDITOR)
FString ServerSettingPath = FPaths::ProjectDir() + FApp::GetProjectName() + "_Data/ZyData/Server/Server.ini";
FString VersionControlPath = FPaths::ProjectDir() + FApp::GetProjectName() + "_Data/ZyData/GameManager/VersionControl.ini";
#else
FString ServerSettingPath = FPaths::ProjectDir() + "../" + FApp::GetProjectName() + "_Data/ZyData/Server/Server.ini";
FString VersionControlPath = FPaths::ProjectDir() + "../" + FApp::GetProjectName() + "_Data/ZyData/GameManager/VersionControl.ini";
#endif

bool UXDSettingLib::GetIsServer()
{
	int NetworkType = 0;
	if (!GConfig->GetInt(TEXT("NetworkManager"), TEXT("NetworkType"), NetworkType, ServerSettingPath))
	{
		GConfig->SetInt(TEXT("NetworkManager"), TEXT("NetworkType"), NetworkType, ServerSettingPath);
		GConfig->Flush(true, ServerSettingPath);
	}
	return NetworkType == 0;
}
FString UXDSettingLib::GetServerIp()
{
	FString ServerIp = "127.0.0.1";
	if (!GConfig->GetString(TEXT("NetworkManager"), TEXT("IPAdress"), ServerIp, ServerSettingPath))
	{
		GConfig->SetString(TEXT("NetworkManager"), TEXT("IPAdress"), *ServerIp, ServerSettingPath);
		GConfig->Flush(true, ServerSettingPath);
	}
	return ServerIp;
}

int UXDSettingLib::GetPlayerID()
{
	int PlayerID = 0;
	if (!GConfig->GetInt(TEXT("NetworkManager"), TEXT("PlayerID"), PlayerID, ServerSettingPath))
	{
		GConfig->SetInt(TEXT("NetworkManager"), TEXT("PlayerID"), PlayerID, ServerSettingPath);
		GConfig->Flush(true, ServerSettingPath);
	}
	return PlayerID;
}

FString UXDSettingLib::GetLanguage()
{
	FString Language = "Chinese";
	if (!GConfig->GetString(TEXT("VersionControl"), TEXT("version"), Language, VersionControlPath))
	{
		GConfig->SetString(TEXT("VersionControl"), TEXT("version"), *Language, VersionControlPath);
		GConfig->Flush(true, VersionControlPath);
	}
	return Language;
}

int UXDSettingLib::GetPlayerCount()
{
	int PlayerCount = 0;
	if (!GConfig->GetInt(TEXT("NetworkManager"), TEXT("PlayerCount"), PlayerCount, ServerSettingPath))
	{
		GConfig->SetInt(TEXT("NetworkManager"), TEXT("PlayerCount"), PlayerCount, ServerSettingPath);
		GConfig->Flush(true, ServerSettingPath);
	}
	return PlayerCount;
}