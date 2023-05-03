// Fill out your copyright notice in the Description page of Project Settings.


#include "GAHealthLvlUpReal.h"
#include "AbilitySystemComponent.h"
#include "GASProjectCharacter.h"

UGAHealthLvlUpReal::UGAHealthLvlUpReal()
{
	AbilityInputID = E_GASProjectInputID::HealthLvlup;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;

	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag("HealthAtMaxLevel"));
}

void UGAHealthLvlUpReal::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}

	AGASProjectCharacter* chara = Cast<AGASProjectCharacter>(GetAvatarActorFromActorInfo());

	if (GetAbilityLevel() > 30) {
		//adds a gameplay tag to show max level has been reached
		chara->MaxHealthLevelReached();
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}

	

	FGameplayEffectSpecHandle HealthLvlUpEffSpecHandle = MakeOutgoingGameplayEffectSpec(HealthLvlupGE, GetAbilityLevel());

	ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, HealthLvlUpEffSpecHandle);

	chara->LevelUpAbility(Handle);


	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

