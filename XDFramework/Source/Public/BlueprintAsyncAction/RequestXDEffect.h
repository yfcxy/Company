// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "RequestXDEffect.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnComplete);

UCLASS()
class XDFRAMEWORK_API URequestXDEffect : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()


public:

	typedef UBlueprintAsyncActionBase Super;

	URequestXDEffect(const FObjectInitializer& ObjectInitializer);

	
	UFUNCTION(BlueprintCallable, Category = "XDFramework",meta = (WorldContext = "InWorldContextObject")
	static URequestXDEffect * RequestXDEffect(UObject* InWorldContextObject , int32 InEffectType, float InDurationTime, int32 InLevel ,int32 InDeviceNo);

	UPROPERTY(BlueprintAssignable)
	FOnComplete OnCompleteEffect;

	int32 EffectType;

	int32 Level;

	float DurationTime;

	int32 DeviceNo;

	FWeakObjectPtr WorldContextObject;

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface


	UFUNCTION()
	void DeactivateXDEffect()const ;
};