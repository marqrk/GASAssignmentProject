// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GASProjectGameplayAbility.h"
#include "GAHealthLvlUpReal.generated.h"

/**
 * 
 */
UCLASS()
class GASASSIGNMENTPROJECT_API UGAHealthLvlUpReal : public UGASProjectGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGAHealthLvlUpReal();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<UGameplayEffect> HealthLvlupGE;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

};
