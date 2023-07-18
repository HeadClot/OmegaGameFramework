// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Gameplay/CombatantComponent.h"
#include "CombatantGambits.generated.h"

USTRUCT(BlueprintType)
struct FCombatantGambit
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gambit", Instanced, DisplayName="IF")
	UCombatantGambitCondition* Gambit_IF = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gambit", Instanced, DisplayName="THEN")
	UCombatantGambitAction* Gambit_THEN = nullptr;
	
};

UCLASS(Blueprintable, BlueprintType, EditInlineNew, Const, CollapseCategories)
class OMEGAGAMEFRAMEWORK_API UCombatantGambitCondition : public UObject
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintImplementableEvent, Category="Combat|Gambit")
	bool RunGambitCheck(const UCombatantComponent* Combatant) const;

};

UCLASS(Blueprintable, BlueprintType, EditInlineNew, Const, CollapseCategories)
class OMEGAGAMEFRAMEWORK_API UCombatantGambitAction : public UObject
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintImplementableEvent, Category="Combat|Gambit")
	void RunGambitAction(const UCombatantComponent* Combatant, TSubclassOf<AOmegaAbility>& AbilityClass, UObject*& AbilityContext) const;

};


UCLASS(Blueprintable, BlueprintType)
class OMEGAGAMEFRAMEWORK_API UCombatantGambitAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Gambits")
	TArray<FCombatantGambit> GambitActions;
	
};

