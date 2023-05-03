// Fill out your copyright notice in the Description page of Project Settings.


#include "UGASProjectPlayerState.h"

AUGASProjectPlayerState::AUGASProjectPlayerState()
{

	AbilitySystemComponent = CreateDefaultSubobject<UGASProjectASC>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	Attributes = CreateDefaultSubobject<UGASProjectAttributeSet>("Attributes");
}

UAbilitySystemComponent* AUGASProjectPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UGASProjectAttributeSet* AUGASProjectPlayerState::GetAttributes() const
{
	return Attributes;
}



float AUGASProjectPlayerState::GetHealth() const
{
	return Attributes->GetHealth();
}

float AUGASProjectPlayerState::GetStamina() const
{
	return Attributes->GetStamina();
}
