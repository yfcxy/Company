// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/Macro"
#include "NetProxy.generated.h"

DECLARE_DELEGATE(FOnDataReceive)



UENUM()
enum class ENetError :uint8
{
	Invalid = 0,
	TimeOut = 1,
	Abort = 2,
	Succeed = 3
};

UCLASS(Abstract)
class XDFRAMEWORK_API UNetProxy: public UObject
{
	GENERATED_BODY()

public:

	typedef UObject Super;

public:

	UNetProxy();

	void Init();

	UFUNCTION(BlueprintImplementableEvent, Category = "XDFramework",DisplayName = "Init Socket ")
	bool K2_Init();

	UFUNCTION(BlueprintCallable, Category = "XDFramework")
	virtual bool IsInit()const;

	UFUNCTION(BlueprintCallable, Category = "XDFramework")
	virtual void OnInit(bool bSucceed)const;

	UFUNCTION(BlueprintImplementableEvent, Category = "XDFramework")
		int32	RegisterCallback(const FString& InReceive);

	UPROPERTY(EditDefautsOnly,BlueprintReadOnly)
	FName SocketType;

	bool bIsInit;

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "XDFramework")
		void	SendData(constFString& Data);

	

	
}




