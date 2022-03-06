// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "RequestXDEffect.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnComplete);


class UNetProxy;

UENUM()
enum class ENetListenResult :uint8
{
	Unset = 0,
	TimeOut = 1,
	Abort = 2,
	NetError = 3,
	Succeed = 4
};

UCLASS()
class XDFRAMEWORK_API USendDataAndWait : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()


public:

	typedef UBlueprintAsyncActionBase Super;

public:

	USendDataAndWait(const FObjectInitializer& ObjectInitializer);

	
	UFUNCTION(BlueprintCallable, Category = "XDFramework", meta = (WorldContext = "InWorldContextObject")
		static USendDataAndWait * SendDataAndWait(UObject * InWorldContextObject, TSubclass<UNetProxy> InClass,const FString & InReceive,
			float TimeoutThreshold, OPTIONAL const FString & InSend = FString(), OPTIONAL float InSendInterval = 1.0f);

	

	void NotifyResult(uint8 Result);


	void NotifySucceed();

	void PostComplete(ENetListenResult Result);

	UPROPERTY(BlueprintAssignable)
	FOnComplete OnSucceed;

	UPROPERTY(BlueprintAssignable)
		FOnComplete OnTimeOut;

	UPROPERTY(BlueprintAssignable)
		FOnComplete OnNetError;

	
	

	// property
    /////////

	FWeakObjectPtr WorldContextObject;


	FWeakObjectPtr NetProxy;

	FString ReceiveData;

	float TimeoutThreshold;

	FString SendData;

	float SendInterval;

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

protected:
	
	

	int32 bIsListenResultSet;

	ENetListenResult Result;
};

FORCEINLINE void USendDataAndWait::NotifyResult(uint8 InResult)
{
	FPlatformAtomics::InterlockedIncrement(bIsListenResultSet);

	Result = InResult;
}



FORCEINLINE void USendDataAndWait::NotifySucceed()
{
	NotifyResult(ENetListenResult::Succeed);
}
