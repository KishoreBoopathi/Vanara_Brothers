// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Vanara_Brothers : ModuleRules
{
	public Vanara_Brothers(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(new string[] { 
			"Vanara_Brothers/Character",
			"Vanara_Brothers/Components",
			// "Vanara_Brothers/Interfaces",
			// "Vanara_Brothers/Enemies",
			// "Vanara_Brothers/Weapons",
			// "Vanara_Brothers/Quest",
			// "Vanara_Brothers/Core"
		});
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
