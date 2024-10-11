// Copyright Studio Syndicat 2021. All Rights Reserved.


#include "Functions/OmegaFunctions_Animation.h"

#include "GameFramework/Character.h"

FGameplayTag UOmegaAnimationEmote::GetObjectGameplayCategory_Implementation() { return CategoryTag; }
FGameplayTagContainer UOmegaAnimationEmote::GetObjectGameplayTags_Implementation() { return GameplayTags; }
void UOmegaAnimationEmote::GetGeneralDataText_Implementation(const FString& Label, const UObject* Context, FText& Name,
	FText& Description) { Name=DisplayName; Description=DisplayDescription; }
void UOmegaAnimationEmote::GetGeneralAssetLabel_Implementation(FString& Label) { Label=DisplayLabel; }
void UOmegaAnimationEmote::GetGeneralDataImages_Implementation(const FString& Label, const UObject* Context,
	UTexture2D*& Texture, UMaterialInterface*& Material, FSlateBrush& Brush) { Brush=DisplayIcon; }

UAnimSequence* UOmegaAnimationFunctions::GetObjectAnimation_Sequence_FromTag(UObject* Object, FGameplayTag Tag)
{
	if(Object && Object->GetClass()->ImplementsInterface(UDataInterface_Animation::StaticClass()))
	{
		return IDataInterface_Animation::Execute_GetAnimationSequence_FromTag(Object,Tag);
	}
	return nullptr;
}

UAnimMontage* UOmegaAnimationFunctions::GetObjectAnimation_Montage_FromTag(UObject* Object, FGameplayTag Tag)
{
	if(Object && Object->GetClass()->ImplementsInterface(UDataInterface_Animation::StaticClass()))
	{
		return IDataInterface_Animation::Execute_GetAnimationMontage_FromTag(Object,Tag);
	}
	return nullptr;
}



void UOmegaAnimationFunctions::PlayEmoteAnimation(ACharacter* Character, UOmegaAnimationEmote* Emote)
{
	if(Character && Emote && Emote->Script)
	{
		Character->PlayAnimMontage(Emote->Script->GetEmoteMontage(Character));
	}
}