// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "OmegaFileSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class OMEGAGAMEFRAMEWORK_API UOmegaFileSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION()
	TArray<FString> GetFilesOfExtension(FString path, FString extension);

	UPROPERTY()
	FString over_path="ovr";
	UPROPERTY()
	FString override_images_path="images";
	UPROPERTY()
	FString override_audio_path="audio";
	
public:
	UFUNCTION(BlueprintPure)
	FString GetOverrideDirectory() const;
	UFUNCTION(BlueprintPure)
	FString GetOverrideDirectory_Images() const;
	UFUNCTION(BlueprintPure)
	FString GetOverrideDirectory_Audio() const;



	UPROPERTY(BlueprintReadOnly)
	TMap<FString, UTexture2D*> imported_images;
	UPROPERTY(BlueprintReadOnly)
	TMap<FString, USoundBase*> imported_sounds;
};

UCLASS()
class OMEGAGAMEFRAMEWORK_API UOmegaFileFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category="Omega|File", meta=(WorldContext="WorldContextObject"))
	static UTexture2D* GetOverride_Texture(UObject* WorldContextObject, const FString& name);
};