// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GASProjectGameplayAbility.h"
#include "GAStaminaLvlUpReal.generated.h"

/**
 * 
 */
UCLASS()
class GASASSIGNMENTPROJECT_API UGAStaminaLvlUpReal : public UGASProjectGameplayAbility
{
	GENERATED_BODY()
public:
	UGAStaminaLvlUpReal();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<UGameplayEffect> StamLvlupGE;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

};
