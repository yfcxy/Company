// Fill out your copyright notice in the Description page of Project Settings.



#include "XDGameInstance.h"

#include "XDGameLib.h"
#include "XDSettingLib.h"
#include "BpJsonLibrary.h"

#include "Debug/XDLog.h"



//int32 UXDGameInstance::HostPlayerIndex = 0;


UXDGameInstance::UXDGameInstance():Super()
{
	

	//grab settings

	bIsServer = UXDSettingLib::GetIsServer();

	ServerIP = UXDSettingLib::GetServerIp();



	PlayerIndex = 0;

	bIsInit = false;
}

void UXDGameInstance::Init()
{
	//bIsXDGameInit = XDGameLib::LoadXDGameDll()?XDGameLib::InitXDGameInstance():false;

	//OnInitXDGame(bIsXDGameInit);
		
		
	
}

void UXDGameInstance::IsInit()const
{

}

void UXDGameInstance::OnInitXDGame(bool bSucceed)
{
	if (bSucceed)
	{
		bIsInit = true;
	}
	else
	{
		//XDLOG(Warning, TEXT("Failed to Init XDGame"))
	}
}


//void UXDGameInstance::ReceiveData(const FString& Data)
//{
//	FString OutString;
//	FBpJson BPJson;
//	BPJson.Json.Values.Add(Data);

//	UBpJsonLibrary::GetStringField(BPJson, "type", OutString);
//}



