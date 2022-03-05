// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "XDGameInstance.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGetJsonString,const FString& Value)

class UXDGame;
/**
 * 
 */
UCLASS()
class XDFRAMEWORK_API UXDGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	typedef UGameInstance Super;

public:
	
	UXDGameInstance();


public:

	UFUNCTION(BlueprintCallable, , Category = "XDFramework")
		virtual void InitFramework();

	UFUNCTION(BlueprintCallable, , Category = "XDFramework")
		virtual void GetPlayerIndex();

	UFUNCTION(BlueprintCallable, , Category = "XDFramework")
		virtual void ReceiveData(const FString& Data);

	UFUNCTION(BlueprintCallable, , Category = "XDFramework")
		virtual void RequestData(const FString& Data);

	UFUNCTION(BlueprintImplementableEvent)
		void OnInitXDGame(bool bSucceed);


	UPROPERTY(BlueprintReadOnly, Category = "XDFramework")
		int32 PlayerIndex;

	UPROPERTY(BlueprintReadOnly, Category = "XDFramework")
		bool bIsServer;

	UPROPERTY(BlueprintReadOnly, Category = "XDFramework")
		bool bIsXDGameInit;

	UPROPERTY(BlueprintReadOnly, Category = "XDFramework")
		FString ServerIP;
};
