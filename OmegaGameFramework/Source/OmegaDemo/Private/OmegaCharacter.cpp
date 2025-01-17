// Fill out your copyright notice in the Description page of Project Settings.


#include "OmegaCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AOmegaCharacter::AOmegaCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Combatant = CreateDefaultSubobject<UCombatantComponent>(TEXT("Combatant"));
	DataItem = CreateDefaultSubobject<UDataItemComponent>(TEXT("DataItem"));
	if(DataItem)
	{
		DataItem->FlagOnApplied="SetCharacter";
	}
	Equipment = CreateDefaultSubobject<UEquipmentComponent>(TEXT("Equipment"));
	Inventory = CreateDefaultSubobject<UDataAssetCollectionComponent>(TEXT("Inventory"));
	Leveling = CreateDefaultSubobject<ULevelingComponent>(TEXT("Leveling"));
	ActorState = CreateDefaultSubobject<UActorStateComponent>(TEXT("ActorState"));
	SaveVisibility = CreateDefaultSubobject<UOmegaSaveStateComponent>(TEXT("SaveVisibility"));
	SubscriptComponent = CreateDefaultSubobject<USubscriptComponent>(TEXT("Subscript"));
}

void AOmegaCharacter::OnConstruction(const FTransform& Transform)
{
	if(CharacterAsset)
	{
		DataItem->SetDataItem(CharacterAsset);
	}
	Super::OnConstruction(Transform);
}

// Called when the game starts or when spawned
void AOmegaCharacter::BeginPlay()
{
	Super::BeginPlay();
	Leveling->OnLevelUp.AddDynamic(this, &AOmegaCharacter::Local_LevelUpdate);
	Leveling->OnLevelDown.AddDynamic(this, &AOmegaCharacter::Local_LevelUpdate);
	DataItem->OnDataItemChanged.AddDynamic(this, &AOmegaCharacter::Local_UpdateDataItem);
	
}

void AOmegaCharacter::Local_AddCombatantSource(UObject* Source)
{
	if(Source)
	{
		Combatant->AddAttrbuteModifier(Source);
		Combatant->SetSkillSourceActive(DataItem, true);
	}
}

// Called every frame
void AOmegaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AOmegaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AOmegaCharacter::Local_LevelUpdate(int32 NewLevel)
{
	Combatant->Level = Leveling->GetCurrentLevel();
}
