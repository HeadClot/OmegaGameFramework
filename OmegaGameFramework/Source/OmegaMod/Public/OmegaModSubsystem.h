// Copyright Studio Syndicat 2021. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DataInterface_General.h"
#include "Gameplay/GameplayTagsInterface.h"
#include "Gameplay/OmegaGameplayModule.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "OmegaModSubsystem.generated.h"


UCLASS(DisplayName="Omega Subsystm: Mods")
class OMEGAMOD_API UOmegaModSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	virtual void Initialize(FSubsystemCollectionBase& Colection) override;
	virtual void Deinitialize() override;

public:
	
	UPROPERTY()
	UOmegaModManager* ModManager;
	UPROPERTY()
	TArray<UOmegaMod*> ModList;

	UFUNCTION(BlueprintPure, Category="OmegaMods")
	TArray<FString> GetModListPaths();
	
	UFUNCTION(BlueprintPure, Category="OmegaMods")
	FString GetModsDirectory();
		
	UFUNCTION(BlueprintPure, Category="Omega|Mods")
	TArray<UOmegaMod*> GetInstalledMods();

	UFUNCTION(BlueprintPure, Category="Omega|Mods")
	TArray<UOmegaMod*> GetActiveMods();

	UFUNCTION(BlueprintCallable, Category="Omega|Mods")
	void SetModActive(UOmegaMod* Mod, bool IsActive);
	
};

UCLASS(Blueprintable,BlueprintType)
class OMEGAMOD_API UOmegaMod : public UObject, public IDataInterface_General, public IGameplayTagsInterface
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadWrite, Category="Mod")
	FText ModName;
	
	UPROPERTY(BlueprintReadWrite, Category="Mod")
	FText ModDescription;

	UPROPERTY(BlueprintReadWrite, Category="Mod")
	FSlateBrush ModThumbnail;

	UPROPERTY(BlueprintReadWrite, Category="Mod")
	FGameplayTag ModCategory;

	UPROPERTY(BlueprintReadOnly, Category="Mod", DisplayName="Mod Path")
	FString ModStringData;

	virtual void GetGeneralDataText_Implementation(const FString& Label, const UObject* Context, FText& Name, FText& Description) override;
	virtual void GetGeneralDataImages_Implementation(const FString& Label, const UObject* Context, UTexture2D*& Texture, UMaterialInterface*& Material, FSlateBrush& Brush) override;
};

UCLASS()
class OMEGAMOD_API UOmegaModManager : public UOmegaGameplayModule
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, Category="Mods")
	FString GetModFiletype();

	UFUNCTION(BlueprintImplementableEvent, Category="Mods")
	void OnSetModActive(UOmegaMod* Mod, bool IsActive);

	UFUNCTION(BlueprintImplementableEvent, Category="Mods")
	bool OnGetModActive(UOmegaMod* Mod);

	UFUNCTION(BlueprintImplementableEvent, Category="Mods")
	void OnModInitialized(UOmegaMod* Mod);
	
};