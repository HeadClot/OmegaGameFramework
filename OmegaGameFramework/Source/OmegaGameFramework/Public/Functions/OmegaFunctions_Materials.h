// Copyright Studio Syndicat 2021. All Rights Reserved.

// Common Use Gameplay Functions

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "OmegaFunctions_Materials.generated.h"



UCLASS()
class UOmegaMaterialFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable,Category="Omega|Materials")
	static void ApplyMaterialsToSlots(UPrimitiveComponent* Component, TMap<FName,UMaterialInterface*> Materials);

};


UCLASS()
class UOmegaTextureFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable,Category="Omega|Texture")
	static TArray<FLinearColor> GetTexturePixelColors(UTexture2D* Texture);

};
