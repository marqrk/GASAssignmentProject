// Fill out your copyright notice in the Description page of Project Settings.


#include "GAStaminaLvlUpReal.h"
#include "AbilitySystemComponent.h"
#include "GASProjectCharacter.h"

UGAStaminaLvlUpReal::UGAStaminaLvlUpReal()
{
	AbilityInputID = E_GASProjectInputID::StaminaLvlup;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;

	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag("StaminaAtMaxLevel"));

}

void UGAStaminaLvlUpReal::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}

	AGASProjectCharacter* chara = Cast<AGASProjectCharacter>(GetAvatarActorFromActorInfo());

	if (GetAbilityLevel() > 30) {
		//adds a gameplay tag to show max level has been reached
		chara->MaxStaminaLevelReached();
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}

	FGameplayEffectSpecHandle StamLvlUpEffSpecHandle = MakeOutgoingGameplayEffectSpec(StamLvlupGE, GetAbilityLevel());

	ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, StamLvlUpEffSpecHandle);

	chara->LevelUpAbility(Handle);


	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
