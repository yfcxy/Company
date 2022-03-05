// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "XDSettingLib.generated.h"

/**
 * 
 */
UCLASS()
class XDGAMEPLUGIN_API UXDSettingLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "XDSettingLib")
	static bool GetIsServer();

	UFUNCTION(BlueprintPure, Category = "XDSettingLib")
	static FString GetServerIp();

	UFUNCTION(BlueprintPure, Category = "XDSettingLib")
	static int GetPlayerID();

	UFUNCTION(BlueprintPure, Category = "XDSettingLib")
	static FString GetLanguage();

	UFUNCTION(BlueprintPure, Category = "XDSettingLib")
	static int GetPlayerCount();
};
