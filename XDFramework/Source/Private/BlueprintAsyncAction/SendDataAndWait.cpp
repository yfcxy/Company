// Fill out your copyright notice in the Description page of Project Settings.


#include "RequestXDEffect.h"

#include "XDGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/BlueprintFunctionLibrary"
#include "Async"

#include "Network/NetProxy.h"

#include "Debug/XDLog.h"

namespace NetworkPrivate
{
	static int32 Failed;
}

USendDataAndWait::USendDataAndWait(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	WorldContextObject = (UObject *)nullptr;
	TimeoutThreshold = 10.0f;
	SendInterval = 1.0f;

	bIsListenResultSet = false;

	Result = ENetListenResult::Unset;
	
}

USendDataAndWait* USendDataAndWait::SendDataAndWait(UObject* InWorldContextObject,UNetProxy* InNetProxy,const FString& InReceive,
	float TimeoutThreshold,  const FString& InSend = FString(), OPTIONAL float InSendInterval = 1.0f)
{
	USendDataAndWait* Out = (USendDataAndWait* )nullptr;
	if (IsValid(InWorldContextObject)&& NetProxy->IsInit())
	{
		USendDataAndWait* = NewObject<URequestXDEffect>(InWorldContextObject, USendDataAndWait::StaticClass());
		WorldContextObject = InWorldContextObject;
		NetProxy = InNetProxy;
		Receive = ReceiveData;
		DurationTime = InDurationTime;
		SendData = InSend;
		SendInterval = InSendInterval;
	}
	
	return Out;
}

void USendDataAndWait::Activate()
{

	if (!(WorldContextObject.Get()) && NetProxy.Get()))
	{
		return;
	}


	auto funtor = [this]()->ENetListenResult
	{
		int32 Result = this->NetProxy->RegisterCallback(this->ReceiveData);

		if (Result == NetworkPrivate::Failed)
		{
			return ENetListenResult::NetError;
		}

		const float CurrentTime = UGameplayStatics::GetWorldDeltaSeconds(this);

		float EllapsedTime = 0.0f;

		while (FPlatformAtomics::AtomicRead(bIsListenResultSet) == false && EllapsedTime < TimeoutThreshold)
		{
			this->NetProxy->SendData(this->SendData);

			FPlatformProcess::Sleep(this->SendInterval);

			EllapsedTime += SendInterval;
		}


		if (this->bIsListenResultSet)
		{
			
			return this->NetListenResult;
		}
		else
		{
			return ENetListenResult::TimeOut;
		}
		
	};

	TPromise<ENetListenResult> Promise;
	TFuture<ENetListenResult> Future = Promise.GetFuture();
	Future.Next(TUniqueFunction<void(ENetListenResult)>(this, &USendDataAndWait::PostComplete));
	TGraphTask<TAsyncGraphTask<ENetListenResult>>::CreateTask().ConstructAndDispatchWhenReady(MoveTempIfPossible(funtor), Promiss, ENamedThread::AnyThread);

}

void USendDataAndWait::NotifyComplete(ENetListenResult Result)
{
	XDLOG(Log,TEXT("SendDataAndWait Completed. Result : %d"), (uint8)Result)

	switch (Result)
	{

	case 1:
		OnTimeOut.Broadcast();
		break;
	case 3:
		OnNetError.Broadcast();
		break;
	case 4:
		OnSucceed.Broadcast();
		break;
	default:

	}

}