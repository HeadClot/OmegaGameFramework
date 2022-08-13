// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SoftPropertiesInterface.generated.h"

USTRUCT()
struct FSoftPropertyCollection
{
	GENERATED_BODY()

	UPROPERTY()
	TMap<FString, float> SoftProp_float;
	UPROPERTY()
	TMap<FString, int32> SoftProp_int;
	UPROPERTY()
	TMap<FString, FString> SoftProp_float;
	UPROPERTY()
	TMap<FString, bool> SoftProp_bool;
	UPROPERTY()
	TMap<FString, float> SoftProp_float;
	UPROPERTY()
	TMap<FString, float> SoftProp_float;
	UPROPERTY()
	TMap<FString, float> SoftProp_float;
};


// This class does not need to be modified.
UINTERFACE()
class USoftPropertiesInterface : public UInterface
{
	GENERATED_BODY()

	
};

/**
 * 
 */
class OMEGAGAMEFRAMEWORK_API ISoftPropertiesInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	//Properties
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="SoftPropertries", meta=(CompactNodeTitle="bool"))
	bool GetSoftProperty_Bool(const FString& Property);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="SoftPropertries", meta=(CompactNodeTitle="int32"))
	int32 GetSoftProperty_Int32(const FString& Property);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="SoftPropertries", meta=(CompactNodeTitle="float"))
	float GetSoftProperty_Float(const FString& Property);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="SoftPropertries", meta=(CompactNodeTitle="string"))
	FString GetSoftProperty_String(const FString& Property);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="SoftPropertries", meta=(CompactNodeTitle="object"))
	UObject* GetSoftProperty_Object(const FString& Property);


	


};
