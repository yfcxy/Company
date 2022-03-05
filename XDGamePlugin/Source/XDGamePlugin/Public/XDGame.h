// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tickable.h"
#include "XDGameLib.h"
#include "XDGame.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class XDGAMEPLUGIN_API UXDGame : public UObject, public FTickableGameObject
{
	GENERATED_BODY()
public:
	virtual UWorld* GetWorld() const override;

	UFUNCTION(BlueprintNativeEvent, Category = "XDGame")
	void OnXDGameEvent(const FString& Data);
	
	virtual void OnXDGameEvent_Implementation(const FString& Data);

	// Begin FTickableGameObject Interface.
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override { return Super::GetStatID(); };
	// End FTickableGameObject Interface.
	UFUNCTION(BlueprintCallable, Category = "XDGame")
	bool Init();

	UFUNCTION(BlueprintCallable, Category = "XDGame")
	void Exit();

	UFUNCTION(BlueprintCallable, Category = "XDGame")
	void Request(const FString& Data) const;

	UFUNCTION(BlueprintCallable, Category = "XDGame")
	void SetScript(const FString& ScriptName, const TArray<uint8> Name, const FString& Key, const FString& Data);

	UFUNCTION(BlueprintCallable, Category = "XDGame")
	void CheckTime(int64 Time, int64 Range, bool& Success);

private:
	bool IsUseTickable = false;
};

