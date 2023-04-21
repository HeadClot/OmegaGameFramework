// Copyright Studio Syndicat 2021. All Rights Reserved.


#include "OmegaGameplaySystem.h"

#include "OmegaGameFrameworkBPLibrary.h"

#include "OmegaGameplaySubsystem.h"
#include "EnhancedInputSubsystems.h"
#include "OmegaGameManager.h"
#include "Kismet/GameplayStatics.h"
#include "Player/OmegaPlayerSubsystem.h"

// Sets default values
AOmegaGameplaySystem::AOmegaGameplaySystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetActorHiddenInGame(true);
	//bIsSpatiallyLoaded = false;
	
}

// Called when the game starts or when spawned
void AOmegaGameplaySystem::BeginPlay()
{
	Super::BeginPlay();
	
	///ATTACH TO GAME MODE
	//SetOwner(UGameplayStatics::GetGameMode(this));
	//AttachToActor(GetOwner(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
	
	//Get Players
	TArray <AActor*> FoundPlayers;
	UGameplayStatics::GetAllActorsOfClass(this, APlayerController::StaticClass(), FoundPlayers);

	GetGameInstance()->GetSubsystem<UOmegaGameManager>()->OnGlobalEvent.AddDynamic(this, &AOmegaGameplaySystem::OnGlobalEvent);
	
	for (AActor* TempActor : FoundPlayers)
	{
		
		const APlayerController* TempPlayer = Cast<APlayerController>(TempActor);
		
		//Add New Widgets To Player Screen
		for (class TSubclassOf <UHUDLayer> TempWidgetClass : AddedPlayerWidgets)
		{
			UOmegaPlayerSubsystem* LocalSystem = TempPlayer->GetLocalPlayer()->GetSubsystem<UOmegaPlayerSubsystem>();
			UHUDLayer* CreatedLayer = LocalSystem->AddHUDLayer(TempWidgetClass, this);
			ActivePlayerWidgets.Add(CreatedLayer);
		}
		//Set Input Mode
		{
			if(PlayerInputMode)
			{
				UGameplayStatics::GetPlayerController(this, 0)->GetLocalPlayer()->GetSubsystem<UOmegaPlayerSubsystem>()->SetCustomInputMode(PlayerInputMode);
			}
		}
		// Add New Mapping Context
		for(UInputMappingContext* TempMap : AddPlayerInputMapping)
		{
			Cast<APlayerController>(TempActor)->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()->AddMappingContext(TempMap, InputPriority);
		}
	}

	//Setup Game Preferences
	/*
	UGamePreferenceSubsystem* GamePrefSystemRef = GEngine->GetWorld()->GetSubsystem<UGamePreferenceSubsystem>();
	GamePrefSystemRef->OnBoolPreferenceUpdated.AddDynamic(this, &AOmegaGameplaySystem::GamePreferenceUpdatedBool);
	GamePrefSystemRef->OnFloatPreferenceUpdated.AddDynamic(this, &AOmegaGameplaySystem::GamePreferenceUpdatedFloat);
	SubsysRef = GEngine->GetWorld()->GetSubsystem<UOmegaGameplaySubsystem>();
	*/

	UOmegaGameplaySubsystem* GameplaySubsys = GetWorld()->GetSubsystem<UOmegaGameplaySubsystem>();

	GameplaySubsys->OnGameplayStateChange.AddDynamic(this, &AOmegaGameplaySystem::OnGameplayStateChange);
	
	//GRANT ABILITIES
	for(auto* TempComb : GameplaySubsys->GetAllCombatants())
	{
		Local_GrantAbilities(TempComb);
	}
	GetWorld()->GetSubsystem<UOmegaGameplaySubsystem>()->OnCombatantRegistered.AddDynamic(this, &AOmegaGameplaySystem::Local_GrantAbilities);

	//FLAGS
	Local_SetFlagsActive(true);
	
}

void AOmegaGameplaySystem::Local_SetFlagsActive(bool State)
{
	for(const auto LocalFlag : ActiveFlags)
	{
		GetGameInstance()->GetSubsystem<UOmegaGameManager>()->SetFlagActive(LocalFlag, State);
	}
}

// Called every frame
void AOmegaGameplaySystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOmegaGameplaySystem::SystemActivated_Implementation(UObject* Context, const FString& Flag)
{
	
}

void AOmegaGameplaySystem::SystemShutdown_Implementation(UObject* Context, const FString& Flag)
{
	
}

void AOmegaGameplaySystem::Shutdown(UObject* Context, FString Flag)
{
	// Block if already shutting down;
	if(bIsInShutdown)
	{
		return;
	}

	
	Shutdown_Context = nullptr;
	if(Context)
	{
		Shutdown_Context = Context;
	}
	Shutdown_Flag = Flag;
	
	bIsInShutdown = true;
	OnBeginShutdown(Shutdown_Context, Shutdown_Flag);
	
}

void AOmegaGameplaySystem::OnBeginShutdown_Implementation(UObject* Context, const FString& Flag)
{
	CompleteShutdown();
}

void AOmegaGameplaySystem::CompleteShutdown()
{
	if(bIsInShutdown)
	{
		TArray <AActor*> FoundPlayers;
		UGameplayStatics::GetAllActorsOfClass(this, APlayerController::StaticClass(), FoundPlayers);
	
		// Remove Player Widgets
		for (class UHUDLayer* TempWidget : ActivePlayerWidgets)
		{
			if(TempWidget)
			{
				TempWidget->RemoveFromParent();
			}
		}
		OnSystemShutdown.Broadcast(Shutdown_Context, Shutdown_Flag);
		SystemShutdown(Shutdown_Context, Shutdown_Flag);
		if (SubsysRef)
		{
			SubsysRef->NativeRemoveSystem(this);
		}

		//Remove Mapping Context
		for (AActor* TempActor : FoundPlayers)
		{
			for(UInputMappingContext* TempMap : AddPlayerInputMapping)
			{
				Cast<APlayerController>(TempActor)->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()->RemoveMappingContext(TempMap);
			}
		}

		//Remove Abilities
		for(FGameplaySystemAbilityRules TempData : GrantedAbilities)
		{
			for(auto* TempComb : GetWorld()->GetSubsystem<UOmegaGameplaySubsystem>()->GetAllCombatants())
			{
				TempComb->UngrantAbility(TempData.AbilityClass);
			}	
		}

		//Activate New Systems
		for(auto TempSys : SystemsActivatedOnShutdown)
		{
			if(TempSys)
			{
				GetWorld()->GetSubsystem<UOmegaGameplaySubsystem>()->ActivateGameplaySystem(TempSys, this, this->GetFName().ToString());
			}
		}

		
		//FLAGS
		Local_SetFlagsActive(false);
	
		K2_DestroyActor();
	}
}

void AOmegaGameplaySystem::Local_GrantAbilities(UCombatantComponent* Combatant)
{
	if(Combatant)
	{
		for(FGameplaySystemAbilityRules TempData : GrantedAbilities)
		{
			const bool AcceptFaction = (TempData.AcceptedFactions.HasTag(Combatant->GetFactionTag()) || TempData.AcceptedFactions.IsEmpty());
			const bool AcceptTags = (Combatant->GetCombatantTags().MatchesQuery(TempData.AcceptedCombatantTags)) || (TempData.AcceptedCombatantTags.IsEmpty());

			if(AcceptFaction & AcceptTags)
			{
				Combatant->GrantAbility(TempData.AbilityClass);
			}
		}
	}
}
