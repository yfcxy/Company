#include "Windows/AllowWindowsPlatformTypes.h"
#include <xaudio2.h>
#include "Windows/HideWindowsPlatformTypes.h"
#include "XDAudio.generated.h"

UCLASS(Blueprintable)
class XDGAMEPLUGIN_API UXDAudio : public UObject
{
	GENERATED_BODY()
public:
    UXDAudio();
    ~UXDAudio();
    UFUNCTION(BlueprintCallable, Category = "XDSound")
    UXDAudioHandle* Create(const FString& SoundName);
    static FString DeviceName;
private:
    IXAudio2* AudioEngine;
    IXAudio2MasteringVoice* Master;
};

UCLASS(Blueprintable)
class XDGAMEPLUGIN_API UXDAudioHandle : public UObject
{
	GENERATED_BODY()
public:
    void Setup(IXAudio2* InAudioEngine, XAUDIO2_BUFFER InAudioBuffer, WAVEFORMATEXTENSIBLE InWfx);
    UFUNCTION(BlueprintCallable, Category = "XDAudioHandle")
    void Play(const bool IsLooping);
    UFUNCTION(BlueprintCallable, Category = "XDAudioHandle")
    void Stop();
private:
    IXAudio2* AudioEngine;
    XAUDIO2_BUFFER AudioBuffer;
    WAVEFORMATEXTENSIBLE Wfx;
    IXAudio2SourceVoice* SourceVoice;
};