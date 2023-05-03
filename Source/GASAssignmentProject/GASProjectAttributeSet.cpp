// Fill out your copyright notice in the Description page of Project Settings.


#include "GASProjectAttributeSet.h"
#include "Net/UnrealNetwork.h"

UGASProjectAttributeSet::UGASProjectAttributeSet()
{
}

void UGASProjectAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGASProjectAttributeSet, Health, COND_None, REPNOTIFY_Always);
}

void UGASProjectAttributeSet::Onrep_Health(const FGameplayAttributeData& oldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASProjectAttributeSet, Health, oldHealth);
}

void UGASProjectAttributeSet::Onrep_Stamina(const FGameplayAttributeData& oldStam)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASProjectAttributeSet, Stamina, oldStam);
}
