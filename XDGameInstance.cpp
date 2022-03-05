// Fill out your copyright notice in the Description page of Project Settings.



#include "XDGameInstance.h"

#include "XDGameLib.h"
#include "XDSettingLib.h"
#include "Debug/XDLog.h"
#include "BpJsonLibrary.h"

//int32 UXDGameInstance::HostPlayerIndex = 0;


UXDGameInstance::UXDGameInstance()
{
	

	

	bIsServer = UXDSettingLib::GetIsServer();

	ServerIP = UXDSettingLib::GetServerIp();

}

void UXDGameInstance::InitFramework()
{
	bIsXDGameInit = XDGameLib::LoadXDGameDll()?XDGameLib::InitXDGameInstance():false;

	
	
	OnInitXDGame(bIsXDGameInit);
		
		
	
}

void OnInitXDGame(bool bSucceed)
{
	//XDLOG(Warning, TEXT("Failed to Init XDGame"))
}


void UXDGameInstance::ReceiveData(const FString& Data)
{
	FString OutString;
	FBpJson BPJson;
	BPJson.Json.Values.Add(Data);

	UBpJsonLibrary::GetStringField(BPJson, "type", OutString);
}

void UXDGameInstance::RequestData(const FString& Data)
{

}

void UXDGameInstance::OnInitXDGame(bool bSucceed)
{

}