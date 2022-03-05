#include "XDGameLib.h"

void XDGameBuffer::Push(FString Data)
{
	if (!IsFull())
	{
		EventDatas[Rear] = Data;
		Rear = (Rear + 1) % 64;
	}
}

FString XDGameBuffer::Pop()
{
	FString& Tmp = EventDatas[Front];
	Front = (Front + 1) % 64;
	return Tmp;
}

bool XDGameBuffer::IsFull()
{
	return Front == (Rear + 1) % 64;
}

bool XDGameBuffer::IsEmpty()
{
	return Front == Rear;
}

InitXDGameInstanceFunc XDGameLib::InitXD	= nullptr;
ExitXDGameInstanceFunc XDGameLib::ExitXD	= nullptr;
RegistXDGameNotifyFunc XDGameLib::RegistXD	= nullptr;
XDGameRequestFunc XDGameLib::RequestXD		= nullptr;
XDGameBuffer XDGameLib::EventBuffer;

bool XDGameLib::LoadXDGameDll()
{
	FString filePath;
	#ifdef PLATFORM_64BITS
	filePath = FPaths::Combine(*FPaths::ProjectPluginsDir(), TEXT("XDGamePlugin/ThirdParty/64/"), TEXT("XDGame.dll"));
	#else
	filePath = FPaths::Combine(*FPaths::ProjectPluginsDir(), TEXT("XDGamePlugin/ThirdParty/32/"), TEXT("XDGame.dll"));
	#endif // PLATFORM_64BITS

	if (FPaths::FileExists(filePath))		//Can the file be found?
	{
		void* DLLHandle;
		DLLHandle = FPlatformProcess::GetDllHandle(*filePath);
		if (DLLHandle != NULL)
		{		 //The name of the function defined in the DLL
			FString InitName	= "InitInstance";
			FString ExitName	= "ExitInstance";
			FString RegistName	= "RegistNotifyFunction";
			FString RequestName = "GameRequest";
			InitXD		= (InitXDGameInstanceFunc)FPlatformProcess::GetDllExport(DLLHandle, *InitName);
			ExitXD		= (ExitXDGameInstanceFunc)FPlatformProcess::GetDllExport(DLLHandle, *ExitName);
			RegistXD	= (RegistXDGameNotifyFunc)FPlatformProcess::GetDllExport(DLLHandle, *RegistName);
			RequestXD 	= (XDGameRequestFunc)FPlatformProcess::GetDllExport(DLLHandle, *RequestName);
			if (InitXD && ExitXD && RegistXD && RequestXD)
			{
				RegistXD(XDGameCallBackFun);
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}

bool XDGameLib::InitXDGameInstance()
{
	if (InitXD != nullptr)
	{
		EventBuffer.Reset();
		return InitXD();
	}
	return false;
}

bool XDGameLib::ExitXDGameInstance()
{
	if (ExitXD != nullptr)
	{
		bool Result = ExitXD();
		RegistXD(NULL);
		InitXD 		= nullptr;
		ExitXD 		= nullptr;
		RegistXD 	= nullptr;
		RequestXD 	= nullptr;
		return Result;
	}
	return false;
}

int XDGameLib::XDGameCallBackFun(const char* Data)
{
	EventBuffer.Push(Data);
	return 0; //todo
}

