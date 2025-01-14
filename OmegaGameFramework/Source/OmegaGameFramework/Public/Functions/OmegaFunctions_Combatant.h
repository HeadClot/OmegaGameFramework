// Fill out your copyright notice in the Description page of Project Settings.

// Functions that may commonly be used in relation to the combatant component.

#pragma once

#include "CoreMinimal.h"
#include "OmegaFunctions_ScriptedEffects.h"
#include "Components/CombatantComponent.h"
#include "Actors/OmegaGameplayEffect.h"
#include "Misc/OmegaUtils_Enums.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "OmegaFunctions_Combatant.generated.h"

UENUM(Blueprintable, BlueprintType)
enum EOmegaCombatTarget
{
	Target_Self					UMETA(DisplayName = "Self"),
	Target_ActiveTarget			UMETA(DisplayName = "Active Target"),
	Target_AllTargets			UMETA(DisplayName = "All Targets"),
};


UCLASS()
class OMEGAGAMEFRAMEWORK_API UCombatantFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="Combat")
	static TArray<UCombatantComponent*> FilterCombatantsByTags(TArray<UCombatantComponent*> Combatants, FGameplayTagContainer Tags, bool bExact, bool bExclude);

	UFUNCTION(BlueprintPure, Category="Combat")
	static TArray<UCombatantComponent*> FilterCombatantsByFaction(TArray<UCombatantComponent*> Combatants, FGameplayTag Faction, bool bExclude);

	UFUNCTION(BlueprintPure, Category="Combat")
	static UCombatantComponent* GetCombatantWithHighestAttributeValue(TArray<UCombatantComponent*> Combatants, UOmegaAttribute* Attribute, bool bUseCurrentValue);

	UFUNCTION(BlueprintPure, Category="Combat")
	static TArray<UCombatantComponent*> GetCombatantFromTargetSelection(UCombatantComponent* Instigator, EOmegaCombatTarget Selection);
	//-----------------------------------------------------------------------------------
	// Effects
	//-----------------------------------------------------------------------------------
	
	// Applies an Effect From a Container struct
	UFUNCTION(BlueprintCallable, Category="Combat", meta=(AdvancedDisplay = "Context"))
	static void ApplyEffectFromContainer(UCombatantComponent* Combatant, UCombatantComponent* Instigator, FOmegaEffectContainer Effect, UObject* Context);

	//NOTE: Asset must implement "DataInterface_OmegaEffect".
	UFUNCTION(BlueprintCallable, Category="Combat")
	static void ApplyEffectFromAsset(UCombatantComponent* Combatant, UCombatantComponent* Instigator, UObject* Asset);

	UFUNCTION(BlueprintPure, Category="Combat", meta = (WorldContext = "WorldContextObject")) 
	static UCombatantComponent* GetPlayerCombatant(const UObject* WorldContextObject, int32 Index);

	UFUNCTION(BlueprintCallable, Category="Combat", meta = (WorldContext = "WorldContextObject")) 
	static void NotifyCombatantFaction(const UObject* WorldContextObject, FGameplayTag Faction, FName Notify);

	//Will attempt to get a combatant component, casting the object as a combatant, and actor, or a sibling component.
	

	//-----------------------------------------------------------------------------------
	// ATTRIBUTES
	//-----------------------------------------------------------------------------------
	UFUNCTION(BlueprintPure, Category="Attributes", meta=(CompactNodeTitle="Attribute ID"))
	static UOmegaAttribute* GetAttributeByUniqueID(const FString& ID);
	
	UFUNCTION(BlueprintCallable, Category="Attributes")
	static TArray<FOmegaAttributeModifier> FlatAttributesToModifierValues(TMap<UOmegaAttribute*, float> FlatAttributes,bool AsMultiplier);

	/*
	UFUNCTION(BlueprintPure, Category="Attributes")
	static TMap<UOmegaAttribute*, float> CompareAttributeModifiers(UCombatantComponent* Combatant, UObject* ComparedModifier, UObject* UncomparedModifer);
	*/
	UFUNCTION(BlueprintPure, Category="Attributes")
	static float CompareSingleAttributeModifiers(UCombatantComponent* Combatant, UOmegaAttribute* Attribute, UObject* ComparedSource, UObject* UncomparedSource);
	
	//-----------------------------------------------------------------------------------
	// Targets
	//-----------------------------------------------------------------------------------

	UFUNCTION(BlueprintPure, Category="Omega|Combat|Targeting")
	static float GetCombatantDistantToActiveTarget(UCombatantComponent* Combatant);

	UFUNCTION(BlueprintPure, Category="Omega|Combat|Targeting")
	static bool IsCombatantActiveTargetInRange(UCombatantComponent* Combatant, float Range);

	//-----------------------------------------------------------------------------------
	// Branches
	//-----------------------------------------------------------------------------------
/*
	//Checks if the Current Attribute Value is at given value
	UFUNCTION(BlueprintCallable, Category="Omega|Actors", meta=(DeterminesOutputType="Class", ExpandEnumAsExecs = "Outcome"))
	static void IsAttributeAtValue(UCombatantComponent* Combatant, UOmegaAttribute* Attribute, float Value, EComparisonMethod Method, TEnumAsByte<EOmegaBranch>& Outcome);

	//Checks if the Current Attribute Value is at a given percentage
	UFUNCTION(BlueprintCallable, Category="Omega|Actors", meta=(DeterminesOutputType="Class", ExpandEnumAsExecs = "Outcome"))
	static void IsAttributeAtPercentage(UCombatantComponent* Combatant, UOmegaAttribute* Attribute, float Percentage, EComparisonMethod Method, TEnumAsByte<EOmegaBranch>& Outcome);
*/
	//Checks if the Attribute is at 100%.
	UFUNCTION(BlueprintCallable, Category="Omega|Actors", meta=(DeterminesOutputType="Class", ExpandEnumAsExecs = "Outcome"))
	static void DoesCombatantHaveTag(UCombatantComponent* Combatant, FGameplayTag Tag, TEnumAsByte<EOmegaBranch>& Outcome);
	
	//Checks if the Attribute is at 100%.
	UFUNCTION(BlueprintCallable, Category="Omega|Actors", meta=(DeterminesOutputType="Class", ExpandEnumAsExecs = "Outcome"))
	static void DoesCombatantHaveEffectWithTag(UCombatantComponent* Combatant, FGameplayTagContainer Tags, TEnumAsByte<EOmegaBranch>& Outcome);
};


UCLASS(Blueprintable, BlueprintType)
class OMEGAGAMEFRAMEWORK_API UCombatantFilter : public UObject
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintImplementableEvent, Category="CombatantFilter")
	const TArray<UCombatantComponent*> FilterCombatants(UCombatantComponent* Instigator, const TArray<UCombatantComponent*>& Combatants);

};

UCLASS(Blueprintable, BlueprintType)
class OMEGAGAMEFRAMEWORK_API UOmegaCommonSkill : public UPrimaryDataAsset, public IDataInterface_General, public IGameplayTagsInterface,
																			public IDataInterface_Skill
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="General",DisplayName="Name") FText DisplayName;
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="General",DisplayName="Icon") FSlateBrush DisplayIcon;
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="General",DisplayName="Description",meta=(MultiLine)) FText DisplayDescription;
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="General",DisplayName="Label") FString DisplayLabel;
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="General",DisplayName="Category") FGameplayTag CategoryTag;
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="General",DisplayName="Tags") FGameplayTagContainer GameplayTags;
	virtual FGameplayTag GetObjectGameplayCategory_Implementation() override;
	virtual FGameplayTagContainer GetObjectGameplayTags_Implementation() override;
	virtual void GetGeneralDataText_Implementation(const FString& Label, const UObject* Context, FText& Name, FText& Description) override;
	virtual void GetGeneralAssetLabel_Implementation(FString& Label) override;
	virtual void GetGeneralDataImages_Implementation(const FString& Label, const UObject* Context, UTexture2D*& Texture, UMaterialInterface*& Material, FSlateBrush& Brush) override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Skill")
	TSubclassOf<UCombatantFilter> TargetFilter;
	virtual TSubclassOf<UCombatantFilter> GetSkillTargetFilter_Implementation() override;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Skill")
	TMap<UOmegaAttribute*, float> AttributeUseCost;
	//virtual TMap<UOmegaAttribute*, float> GetSkillAttributeCosts_Implementation(UCombatantComponent* Combatant,UObject* Context) override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Skill")
	FOmegaCustomScriptedEffects Effects_Target;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Skill")
	FOmegaCustomScriptedEffects Effects_Instigator;
};