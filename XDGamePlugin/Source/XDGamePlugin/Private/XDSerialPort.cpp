#include "XDSerialPort.h"
#include <vector>

UXDSerialPort::UXDSerialPort()
{
	SerialPort = INVALID_HANDLE_VALUE;
}

UXDSerialPort::~UXDSerialPort()
{
	Close();
}

bool UXDSerialPort::Open(const FString& COM)
{
	if (SerialPort == INVALID_HANDLE_VALUE)
	{
		SerialPort = CreateFile(TCHAR_TO_WCHAR(*COM),
			GENERIC_READ | GENERIC_WRITE, 
			0, 
			NULL,
			OPEN_ALWAYS, 
			FILE_ATTRIBUTE_NORMAL,
			NULL);
	}
	return SerialPort != INVALID_HANDLE_VALUE;
}

void UXDSerialPort::Close()
{
	if (SerialPort != INVALID_HANDLE_VALUE)
	{
		CloseHandle(SerialPort);
		SerialPort = INVALID_HANDLE_VALUE;
	}
}

bool UXDSerialPort::IsOpen() const
{
	return SerialPort != INVALID_HANDLE_VALUE;
}

bool UXDSerialPort::WriteData(char* DataPtr, int Size)
{
	DWORD BytesWrite = 0;
	DWORD DataLen = Size;
	do {                                      
		WriteFile(SerialPort, DataPtr, DataLen, &BytesWrite, NULL);
		DataLen -= BytesWrite;
		DataPtr += BytesWrite;
	} while (DataLen > 0);
	return true;
}

bool UXDSerialPort::WriteHexData(const FString& Data)
{
	if (SerialPort != INVALID_HANDLE_VALUE)
	{
		FString NewData = Data;
		NewData.RemoveSpacesInline();
		uint8 DateChars[256];
		FString::ToHexBlob(NewData, DateChars, NewData.Len());
		return WriteData((char*)DateChars, NewData.Len() / 2);
	}
	return false;
}

bool UXDSerialPort::WriteASCIIData(const FString& Data)
{
	if (SerialPort != INVALID_HANDLE_VALUE)
	{
		char* DatePtr = TCHAR_TO_UTF8(*Data);
		return WriteData(DatePtr, Data.Len());
	}
	return false;
}