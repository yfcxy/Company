#pragma once

#include "CoreMinimal.h"

class XDGAMEPLUGIN_API XDGameBuffer
{
public:
	void Push(FString Data);
	FString Pop();
	bool IsFull();
	bool IsEmpty();
	void Reset() { Front = Rear = 0; }
private:
	FString EventDatas[64];
	uint32_t Front	= 0;
	uint32_t Rear	= 0;
};

typedef int(_stdcall* CallBackFun)(const char* Data);
typedef bool (*InitXDGameInstanceFunc)();
typedef bool (*ExitXDGameInstanceFunc)();
typedef int (*RegistXDGameNotifyFunc)(CallBackFun CallFun);
typedef int (*XDGameRequestFunc)(const char* Data);

class XDGAMEPLUGIN_API XDGameLib
{
public:
	static bool LoadXDGameDll();

	static bool InitXDGameInstance();

	static bool ExitXDGameInstance();

	static const XDGameRequestFunc GetRequestXD() { return RequestXD; };
	
	static XDGameBuffer EventBuffer;
private:
	static int XDGameCallBackFun(const char* Data);
	static InitXDGameInstanceFunc InitXD;
	static ExitXDGameInstanceFunc ExitXD;
	static RegistXDGameNotifyFunc RegistXD;
	static XDGameRequestFunc RequestXD;
};