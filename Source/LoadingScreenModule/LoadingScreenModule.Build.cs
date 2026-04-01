using UnrealBuildTool;

public class LoadingScreenModule : ModuleRules
{
    public LoadingScreenModule(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivatePCHHeaderFile = "Public/LoadingScreenModule.h";

        PCHUsage = PCHUsageMode.UseSharedPCHs;

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "MoviePlayer",
                "Engine",
                "Slate",
                "SlateCore",
                "DeveloperSettings"
            }
                );
    }
}
