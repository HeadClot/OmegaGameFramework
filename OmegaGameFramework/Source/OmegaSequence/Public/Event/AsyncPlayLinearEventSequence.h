﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OmegaLinearEventSubsystem.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncPlayLinearEventSequence.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFinished, const FString&, Flag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAsynLinEventUpdated, int32, NewEventIndex, UOmegaLinearEvent*, NewEvent, UOmegaLinearEventInstance*, Instance);

UCLASS()
class OMEGASEQUENCE_API UAsyncPlayLinearEventSequence : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UOmegaLinearEventSubsystem* SubsystemRef;
	UPROPERTY()
	FLinearEventSequence EventData;
	UPROPERTY()
	int32 Local_StartingIndex;
	UFUNCTION()
	void Local_Finish(const FString& Flag);
	UPROPERTY()
	UOmegaLinearEventInstance* EventInstance;
	
	UFUNCTION()
	void Local_NewEvent(int32 Index, UOmegaLinearEvent* EventRef);
	UPROPERTY(BlueprintAssignable)
	FOnAsynLinEventUpdated NewEvent;
	
	UPROPERTY(BlueprintAssignable)
	FOnFinished OnFinished;
	
	
	virtual void Activate() override;
	
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category="OmegaSequence", DisplayName="Play Linear Event Sequence")
	static UAsyncPlayLinearEventSequence* PlayLinearEventSequence(UObject* WorldContextObject, FLinearEventSequence Events, int32 StartingIndex);

};

