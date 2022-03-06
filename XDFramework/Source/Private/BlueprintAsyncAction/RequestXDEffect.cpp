// Fill out your copyright notice in the Description page of Project Settings.


#include "RequestXDEffect.h"

#include "XDGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/BlueprintFunctionLibrary"

URequestXDEffect::URequestXDEffect(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	WorldContextObject = (UObject *)nullptr;
	EffectType = 0;
	DurationTime = 0.0f;
	Level = 0;
	DeviceNo = 0;

	
}

URequestXDEffect* URequestXDEffect::RequestXDEffect(UObject* InWorldContextObject, int32 InEffectType, float InDurationTime, int32 InLevel, int32 InDeviceNo)
{
	URequestXDEffect* OutRequestXDEffect = (URequestXDEffect * )nullptr;
	if (IsValid(InWorldContextObject))
	{
		URequestXDEffect* = NewObject<URequestXDEffect>(InWorldContextObject, URequestXDEffect::StaticClass());
		WorldContextObject = InWorldContextObject;
		EffectType = InEffectType;
		DurationTime = InDurationTime;
		Level = InLevel;
		DeviceNo = InDeviceNo;
	}
	
	return OutRequestXDEffect;
}

void URequestXDEffect::Activate()
{
	
	if (!WorldContextObject->Get()) 
	{
		return;
	}
	if (UXDGameInstance* XDGameInstance = Cast<UXDGameInstance>(UGameplayStaitcs::GetGameInstance()))
	{
		if (!XDGameInstance->IsInit())
		{
			return;
		}
		else
		{
			XDGameInstance->RequestEffect(EffectType,  Level,  DeviceNo);
			
			K2_SetTimerDelegate(FTimerDynamicDelegate::CreateUObject(this, &URequestXDEffect::DeactivateXDEffect()));


		}
	}
	else
	{
		return;
	}
	
}

void URequestXDEffect::DeactivateXDEffect()const
{
	XDGameInstance->RequestEffect(EffectType, 0, DeviceNo);

	FOnComplete.Broadcast();
}