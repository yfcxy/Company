// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System;
using System.IO;

public class XDGamePlugin : ModuleRules
{

    public XDGamePlugin(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		if (Target.Platform == UnrealTargetPlatform.Win32 ||
				Target.Platform == UnrealTargetPlatform.Win64)
		{
        	string PlatformDir = Target.Platform == UnrealTargetPlatform.Win64 ? "64/" : "32/";
        	string XDGameDllName = "XdGame.dll";
        	string XDGameDllPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty", PlatformDir));
        	PublicDelayLoadDLLs.Add(XDGameDllName);
        	RuntimeDependencies.Add(new RuntimeDependency(Path.Combine(XDGameDllPath, XDGameDllName)));
			//win10上使用xaudio2必须添加该库
			AddEngineThirdPartyPrivateStaticDependencies(Target, "DirectSound");
			//XDSound wav file path
        	RuntimeDependencies.Add(new RuntimeDependency("$(ProjectDir)/XDWav/*.wav"));
		}
        PublicIncludePaths.AddRange(
			new string[] {
				"XDGamePlugin/Public"
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"XDGamePlugin/Private",
				// ... add other private include paths required here ...
			}
			);
		
		PrivateIncludePathModuleNames.AddRange(
			new string[] {
				"TargetPlatform",
			}
		);
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"Lua",
				"UnLua",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
