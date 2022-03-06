// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "XDGameInstance.generated.h"


class UNetworkProxy;

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

	UFUNCTION(BlueprintCallable, Category = "XDFramework")
		virtual void Init();

	UFUNCTION(BlueprintCallable, Category = "XDFramework")
		virtual void GetPlayerIndex()const;


	UFUNCTION(BlueprintImplementableEvent, Category = "XDFramework")
		void SetXDGame(UXDGame* InXDGame);

	UFUNCTION(BlueprintCallable, Category = "XDFramework")
		virtual void IsInit()const;
	

	UFUNCTION(BlueprintCallable, Category = "XDFramework")
		virtual void OnInitXDGame(bool bSucceed);


	UPROPERTY(BlueprintReadOnly, Category = "XDFramework")
		int32 PlayerIndex;

	UPROPERTY(BlueprintReadOnly, Category = "XDFramework")
		bool bIsServer :1 ;

	

	UPROPERTY(BlueprintReadOnly, Category = "XDFramework")
		FString ServerIP;


	UPROPERTY(BlueprintReadOnly, Category = "XDFramework")
		UXDGame* XDGame;


	
public:

	UFUNCTION(BlueprintImplementableEvent,  Category = "XDFramework")
	void RequestEffect(int32 InEffectType, int32 InLevel, int32 InDeviceNo);

	UFUNCTION(BlueprintImplementableEvent, Category = "XDFramework")
	 void NotifyGameStart();

	UFUNCTION(BlueprintImplementableEvent, Category = "XDFramework")
	 void NotifyGameOver();


protected:

	void RequestData(const FString& Data)const;

	bool bIsInit : 1 ;

	//// --- Network  ------------------------------
	//

	TMap<FName, UNetworkProxy> Sockets;
};
