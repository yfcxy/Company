#include "XDAudio.h"
#include <string>

FString UXDAudio::DeviceName;

#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'

HRESULT FindChunk(HANDLE file, DWORD fourcc, DWORD* dwChunkSize, DWORD* dwChunkDataPosition)
{
	if (SetFilePointer(file, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {
		return HRESULT_FROM_WIN32(GetLastError());
	}

	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD bytesRead = 0;
	DWORD dwOffset = 0;

	HRESULT hr = S_OK;
	while (hr == S_OK)
	{
		DWORD dwRead;
		if (0 == ReadFile(file, &dwChunkType, sizeof(DWORD), &dwRead, NULL)) {
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (0 == ReadFile(file, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL)) {
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case fourccRIFF:
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (0 == ReadFile(file, &dwFileType, sizeof(DWORD), &dwRead, NULL))
				hr = HRESULT_FROM_WIN32(GetLastError());
			break;

		default:
			if (INVALID_SET_FILE_POINTER == SetFilePointer(file, dwChunkDataSize, NULL, FILE_CURRENT))
				return HRESULT_FROM_WIN32(GetLastError());
		}

		dwOffset += sizeof(DWORD) * 2;

		if (dwChunkType == fourcc)
		{
			*dwChunkSize = dwChunkDataSize;
			*dwChunkDataPosition = dwOffset;
			return S_OK;
		}

		dwOffset += dwChunkDataSize;

		if (bytesRead >= dwRIFFDataSize) return S_FALSE;
	}

	return S_OK;
}

HRESULT ReadChunkData(HANDLE file, void* buffer, DWORD bufferSize, DWORD bufferOffset)
{
	HRESULT hr = S_OK;
	if (INVALID_SET_FILE_POINTER == SetFilePointer(file, bufferOffset, NULL, FILE_BEGIN)) {
		return HRESULT_FROM_WIN32(GetLastError());
	}

	DWORD dwRead;
	if (0 == ReadFile(file, buffer, bufferSize, &dwRead, NULL)) {
		hr = HRESULT_FROM_WIN32(GetLastError());
	}

	return hr;
}

std::wstring StringToWString(const std::string& s)
{
	std::wstring wszStr;
 
	int nLength = MultiByteToWideChar(CP_ACP, 0, s.c_str(), -1, NULL, NULL);
	wszStr.resize(nLength);
	LPWSTR lpwszStr = new wchar_t[nLength];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), -1, lpwszStr, nLength);
	wszStr = lpwszStr;
	delete[] lpwszStr;
	return wszStr;
}

HRESULT LoadWAV(const char* filename, WAVEFORMATEXTENSIBLE& wfx, XAUDIO2_BUFFER& buffer)
{
	HANDLE file = CreateFile(StringToWString(filename).c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

	if (INVALID_HANDLE_VALUE == file) {
        CloseHandle(file);        
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if (INVALID_SET_FILE_POINTER == SetFilePointer(file, 0, NULL, FILE_BEGIN)) {
        CloseHandle(file);
		return HRESULT_FROM_WIN32(GetLastError());
	}

	DWORD chunkSize;
	DWORD chunkPosition;
	FindChunk(file, fourccRIFF, &chunkSize, &chunkPosition);

	DWORD fileType;
	ReadChunkData(file, &fileType, sizeof(DWORD), chunkPosition);
	if (fileType != fourccWAVE) {
        CloseHandle(file);
		return S_FALSE;
	}

	FindChunk(file, fourccFMT, &chunkSize, &chunkPosition);
	ReadChunkData(file, &wfx, chunkSize, chunkPosition);

	FindChunk(file, fourccDATA, &chunkSize, &chunkPosition);
	BYTE* pDataBuffer = (BYTE*)malloc(chunkSize);
	ReadChunkData(file, pDataBuffer, chunkSize, chunkPosition);

	buffer.AudioBytes = chunkSize;
	buffer.pAudioData = pDataBuffer;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
    CloseHandle(file);
	return S_OK;
}

UXDAudio::UXDAudio()
{
#if (UE_EDITOR)
	FString IniPath = FPaths::ProjectDir() + FApp::GetProjectName() + "_Data/GameSetting.ini";
#else
	FString IniPath = FPaths::ProjectDir() + "../" + FApp::GetProjectName() + "_Data/GameSetting.ini";
#endif
    if (!GConfig->GetString(TEXT("XDSound"), TEXT("Device"), DeviceName, IniPath))
	{
		GConfig->SetString(TEXT("XDSound"), TEXT("Device"), TEXT(""), IniPath);
		GConfig->Flush(false, IniPath);
	}
	GConfig->Flush(true, IniPath);
}

UXDAudio::~UXDAudio()
{
    if (Master)
        Master->DestroyVoice();//释放资源
    if (AudioEngine)        
 	    AudioEngine->Release();//释放资源
 	CoUninitialize();//释放资源
}

UXDAudioHandle* UXDAudio::Create(const FString& SoundName)
{
    if(AudioEngine == nullptr)
    {
        XAudio2Create(&AudioEngine);
		CoInitialize(NULL);
		int DeviceIndex = -1;
		{
			UINT uPlayer = 0;
			AudioEngine->GetDeviceCount(&uPlayer);//获取音频输出设备个数
			
			XAUDIO2_DEVICE_DETAILS DeviceInfo;
			for (int i = 0; i < (int)uPlayer; i++)
			{
				AudioEngine->GetDeviceDetails(i, &DeviceInfo);//获取设备信息
				if (UXDAudio::DeviceName.Equals(DeviceInfo.DisplayName))
				{
					DeviceIndex = i;
				}
			}
            if (DeviceIndex == -1)
            {
                FString Msg;
                if(DeviceName.IsEmpty())
                {
                    Msg = "Please enter the device name!!!";
                }
                else
                {
                    Msg = FString::Printf(TEXT("Device: %s does not exist!!!"), *DeviceName);
                }
                GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.f, FColor::Red, Msg);
                DeviceIndex = 0;
            }
		}

		AudioEngine->CreateMasteringVoice(&Master, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, DeviceIndex);
    }

    FString Sound = SoundName + ".wav";
	FString SoundPath = FPaths::Combine(FPaths::ProjectDir(), L"XDWav", Sound);
	WAVEFORMATEXTENSIBLE Wfx = {};
	XAUDIO2_BUFFER Buffer = {};

	if(LoadWAV(TCHAR_TO_UTF8(*SoundPath), Wfx, Buffer) != S_OK)
    {
		FString Msg = FString::Printf(TEXT("< %s > does not exist!!!"), *Sound);
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.f, FColor::Red, Msg);
		return nullptr;
    }
	UXDAudioHandle* Handle = NewObject<UXDAudioHandle>(this);
	Handle->Setup(AudioEngine, Buffer, Wfx);
	return Handle;
}

void UXDAudioHandle::Setup(IXAudio2* InAudioEngine, XAUDIO2_BUFFER InAudioBuffer, WAVEFORMATEXTENSIBLE InWfx)
{
	AudioEngine = InAudioEngine;
	AudioBuffer = InAudioBuffer;
	Wfx = InWfx;
}

void UXDAudioHandle::Play(bool IsLooping)
{
	if (AudioEngine == nullptr)
	{
		return;
	}
	
	if(IsLooping)
	{
		Stop();
        AudioBuffer.LoopCount = XAUDIO2_LOOP_INFINITE;
		if(SourceVoice == nullptr)
		{
			AudioEngine->CreateSourceVoice(&SourceVoice, (WAVEFORMATEX*)& Wfx);
		}
		if (SourceVoice)
		{
			SourceVoice->SubmitSourceBuffer(&AudioBuffer);
			SourceVoice->Start();
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.f, FColor::Red, TEXT("Create Source Voice Fail!!!"));			
		}
	}
	else
	{
        AudioBuffer.LoopCount = 0;
		IXAudio2SourceVoice* Source = nullptr;
		AudioEngine->CreateSourceVoice(&Source, (WAVEFORMATEX*)& Wfx);
		if(Source)
		{
			Source->SubmitSourceBuffer(&AudioBuffer);
			Source->Start();
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.f, FColor::Red, TEXT("Create Source Voice Fail!!!"));
		}
		
	}
}

void UXDAudioHandle::Stop()
{
	if(SourceVoice)
	{
		SourceVoice->Stop();
	}	
}