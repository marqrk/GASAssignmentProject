// Fill out your copyright notice in the Description page of Project Settings.


#include "GASProjectCharacter.h"

// Sets default values
AGASProjectCharacter::AGASProjectCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Tags should be under parents but for simplicity of the project they do not have parents
	HealthMaxLvl = FGameplayTag::RequestGameplayTag(FName("HealthAtMaxLevel"));
	StamMaxLvl = FGameplayTag::RequestGameplayTag(FName("StaminaAtMaxLevel"));
}

UAbilitySystemComponent* AGASProjectCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;

}

void AGASProjectCharacter::InitializeAttributes()
{
	if (AbilitySystemComponent && DefaultAttributeEffect) {
		FGameplayEffectContextHandle EffContext = AbilitySystemComponent->MakeEffectContext();
		EffContext.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffContext);

		if (SpecHandle.IsValid()) {
			FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

void AGASProjectCharacter::GiveStartAbilities()
{
	if (HasAuthority() && AbilitySystemComponent) {
		for (TSubclassOf<UGASProjectGameplayAbility>& StartupAbility : DefaultAbilities) {
			AbilitySystemComponent->GiveAbility(
				FGameplayAbilitySpec(StartupAbility, 1, static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));
		}
	}
}

void AGASProjectCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AUGASProjectPlayerState* PS = GetPlayerState<AUGASProjectPlayerState>();
	if (PS) {
		AbilitySystemComponent = Cast<UGASProjectASC>(PS->GetAbilitySystemComponent());

		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);

		Attributes = PS->GetAttributes();

		InitializeAttributes();

		//set the gameplay tags to 0 so they are "off" right now
		AbilitySystemComponent->SetTagMapCount(HealthMaxLvl, 0);
		AbilitySystemComponent->SetTagMapCount(StamMaxLvl, 0);

		GiveStartAbilities();
	}
}

void AGASProjectCharacter::OnRep_PlayerState()
{
	AUGASProjectPlayerState* PS = GetPlayerState<AUGASProjectPlayerState>();
	if (PS) {
		AbilitySystemComponent = Cast<UGASProjectASC>(PS->GetAbilitySystemComponent());
		AbilitySystemComponent->InitAbilityActorInfo(PS, this);

		InitializeAttributes();

		//set the gameplay tags to 0 so they are "off" right now
		AbilitySystemComponent->SetTagMapCount(HealthMaxLvl, 0);
		AbilitySystemComponent->SetTagMapCount(StamMaxLvl, 0);

		//if (AbilitySystemComponent && InputComponent && !ASCIBound) {
		//	const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", "E_GASProjectInputID", static_cast<int32>(E_GASProjectInputID::Confirm),
		//		static_cast<int32>(E_GASProjectInputID::Cancel));
		//	AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
		//}
		BindASCInputs();
	}
}

void AGASProjectCharacter::MaxHealthLevelReached()
{
	if (!AbilitySystemComponent->HasMatchingGameplayTag(HealthMaxLvl)) {
		AbilitySystemComponent->SetTagMapCount(HealthMaxLvl, 1);
	}
}

void AGASProjectCharacter::MaxStaminaLevelReached()
{
	if (!AbilitySystemComponent->HasMatchingGameplayTag(StamMaxLvl)) {
		AbilitySystemComponent->SetTagMapCount(StamMaxLvl, 1);
	}
}

void AGASProjectCharacter::LevelUpAbility(FGameplayAbilitySpecHandle ability)
{
	if (HasAuthority() && AbilitySystemComponent) {
		/*FGameplayAbilitySpec* abilityToLevel = AbilitySystemComponent->FindAbilitySpecFromHandle(ability);
		abilityToLevel->Level += 1;*/

		AbilitySystemComponent->FindAbilitySpecFromHandle(ability)->Level += 1;

		//AbilitySystemComponent->ClearAbility(ability);
		//AbilitySystemComponent->GiveAbility(*abilityToLevel);
	}

	
}

// Called when the game starts or when spawned
void AGASProjectCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

float AGASProjectCharacter::GetHealth() const
{
	if (Attributes) {
		return Attributes->GetHealth();
	}
	
	return 0.0f;
}

float AGASProjectCharacter::GetStamina() const
{
	if (Attributes) {
		return Attributes->GetStamina();
	}

	return 0.0f;
}

// Called every frame
void AGASProjectCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGASProjectCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//if (AbilitySystemComponent && InputComponent && !ASCIBound) {
	//	const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", "E_GASProjectInputID", static_cast<int32>(E_GASProjectInputID::Confirm),
	//		static_cast<int32>(E_GASProjectInputID::Cancel));
	//	AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
	//}
	BindASCInputs();

}

void AGASProjectCharacter::BindASCInputs()
{
	if (!ASCIBound && AbilitySystemComponent && InputComponent) {
		FTopLevelAssetPath AbilEnumAssetPath = FTopLevelAssetPath(FName("/script/GASAssignmentProject"), FName("E_GASProjectInputID"));
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent,
			FGameplayAbilityInputBinds(FString("ConfirmTarget"),FString("CancelTarget"), AbilEnumAssetPath, static_cast<int32>(E_GASProjectInputID::Confirm),
				static_cast<int32>(E_GASProjectInputID::Cancel)));
	}
	ASCIBound = true;
}

