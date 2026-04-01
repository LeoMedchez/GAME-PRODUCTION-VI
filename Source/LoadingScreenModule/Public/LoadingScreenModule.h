#pragma once
#include "Modules/ModuleInterface.h"

class FLoadingScreenModule : public IModuleInterface
{
public:

	virtual void StartupModule() override;

	virtual bool IsGameModule() const override;

	virtual void StartLoadingScreen(const FString& MapName);

private:

	UTexture2D* BackgroundTexture;
};