#pragma once

#include "Windows/AllowWindowsPlatformTypes.h"  
#include <Windows.h>
#include "Windows/HideWindowsPlatformTypes.h"
#include "CoreMinimal.h"
#include "XDSerialPort.generated.h"

UCLASS(Blueprintable)
class XDGAMEPLUGIN_API UXDSerialPort : public UObject
{
	GENERATED_BODY()
public:
	UXDSerialPort();
	~UXDSerialPort();
	UFUNCTION(BlueprintCallable, Category = "XDSerialPort")
	bool Open(const FString& COM);
	UFUNCTION(BlueprintCallable, Category = "XDSerialPort")
	void Close();
	UFUNCTION(BlueprintCallable, Category = "XDSerialPort")
	bool IsOpen() const;
	
	bool WriteData(char* DataPtr, int Size);
	UFUNCTION(BlueprintCallable, Category = "XDSerialPort")
	bool WriteHexData(const FString& Data);
	UFUNCTION(BlueprintCallable, Category = "XDSerialPort")
	bool WriteASCIIData(const FString& Data);
private:
	HANDLE SerialPort;
};