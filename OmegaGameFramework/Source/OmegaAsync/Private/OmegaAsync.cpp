// Copyright Studio Syndicat 2021. All Rights Reserved.

#include "OmegaAsync.h"

DEFINE_LOG_CATEGORY(OmegaAsync);

#define LOCTEXT_NAMESPACE "FOmegaAsync"

void FOmegaAsync::StartupModule()
{
	UE_LOG(OmegaAsync, Warning, TEXT("OmegaAsync module has been loaded"));
}

void FOmegaAsync::ShutdownModule()
{
	UE_LOG(OmegaAsync, Warning, TEXT("OmegaAsync module has been unloaded"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FOmegaAsync, OmegaAsync)