// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GASProjectASC.h"
#include "GASProjectAttributeSet.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "UGASProjectPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class GASASSIGNMENTPROJECT_API AUGASProjectPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AUGASProjectPlayerState();

	class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UGASProjectAttributeSet* GetAttributes() const;

	UFUNCTION(BluePrintCallable, Category = "CharacterAttributes")
		float GetHealth() const;

	UFUNCTION(BluePrintCallable, Category = "CharacterAttributes")
		float GetStamina() const;

protected:
	UPROPERTY(EditAnywhere)
		class UGASProjectASC* AbilitySystemComponent;

	UPROPERTY()
		class UGASProjectAttributeSet* Attributes;
};
