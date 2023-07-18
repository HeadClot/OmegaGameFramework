// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Event/OmegaLinearEvent.h"
#include "Choice/OmegaLinearChoiceInstance.h"
#include "OmegaLinearEventSubsystem.generated.h"

class UOmegaLinearEventInstance;

USTRUCT(BlueprintType)
struct FLinearEventSequence
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category="LinearEvents", instanced, EditAnywhere)
	TArray<class UOmegaLinearEvent*> Events;
};

USTRUCT(BlueprintType)
struct FOmegaLinearEventScriptData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Script")
	FString Event_Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Script")
	FString Event_Data;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLinearEventBegin, const UOmegaLinearEvent*, Event);

UCLASS(DisplayName="Omega Subsystem: Linear Events")
class OMEGASEQUENCE_API UOmegaLinearEventSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;


public:
	UPROPERTY()
	UGameInstance* GameInstanceReference;
	
	UFUNCTION(BlueprintCallable, Category="LinearEvent", meta=(AdvancedDisplay="StartingEvent"))
	UOmegaLinearEventInstance* PlayLinearEvent(FLinearEventSequence Sequence, int32 StartingEvent);

	UFUNCTION(BlueprintCallable, Category="LinearEvent", meta=(AdvancedDisplay="StartingEvent"))
	UOmegaLinearEventInstance* PlayLinearEventFromID(FLinearEventSequence Sequence, FName ID);
	
	UPROPERTY()
	TArray<UOmegaLinearEventInstance*> TempEvents;

	UFUNCTION(BlueprintPure, Category="LinearEvent")
	TArray<UOmegaLinearEventInstance*> GetActiveEventInstances() const
	{
		return TempEvents;
	}

	UPROPERTY(BlueprintAssignable)
	FOnLinearEventBegin OnLinearEventBegin;
	
	///CHOICE
	UFUNCTION(BlueprintCallable, Category="LinearEvent")
	AOmegaLinearChoiceInstance* PlayLinearChoice(FOmegaLinearChoices Choices, TSubclassOf<AOmegaLinearChoiceInstance> InstanceClass);
};

UCLASS(Blueprintable, BlueprintType)
class OMEGASEQUENCE_API UOmegaLinearEventScriptReader : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, Category="Script")
	TSubclassOf<UOmegaDataParserReader> GetParserClass();
	
	UFUNCTION(BlueprintImplementableEvent, Category="Script")
	TArray<FOmegaLinearEventScriptData> ConvertScriptToEventData(const FString& Script);

	UFUNCTION(BlueprintImplementableEvent, Category="Script")
	TSubclassOf<UOmegaLinearEvent> GetEventClassFromString(const FString& Script);

	UFUNCTION(BlueprintCallable, Category="Script")
	FLinearEventSequence ConvertToLinearEventSequence(const FString& Script, TSubclassOf<UOmegaDataParserReader> ReaderClass, bool ScriptIsPath);
	
};
