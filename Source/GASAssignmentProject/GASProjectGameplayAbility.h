// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GASAssignmentProject.h"
#include "GASProjectGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class GASASSIGNMENTPROJECT_API UGASProjectGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:

	UGASProjectGameplayAbility();

	UPROPERTY(BlueprintReadonly, EditAnywhere, Category = "Ability")
		E_GASProjectInputID AbilityInputID = E_GASProjectInputID::None;
};
