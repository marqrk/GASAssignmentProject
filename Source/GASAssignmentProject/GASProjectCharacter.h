// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GASProjectASC.h"
#include "GASProjectAttributeSet.h"
#include "GASProjectGameplayAbility.h"
#include "UGASProjectPlayerState.h"
#include "AbilitySystemInterface.h"
#include "GASProjectGameplayAbility.h"
#include <GameplayEffectTypes.h>
#include "GASProjectCharacter.generated.h"


UCLASS()
class GASASSIGNMENTPROJECT_API AGASProjectCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGASProjectCharacter();

	UPROPERTY(EditAnywhere)
	class UGASProjectASC* AbilitySystemComponent;



	UPROPERTY()
		class UGASProjectAttributeSet* Attributes;

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void InitializeAttributes();
	virtual void GiveStartAbilities();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	//functions to alter the gameplay tags. They first check if there are instances of the tag in the ASC and if not it sets the # of instances to 1
	void MaxHealthLevelReached();
	void MaxStaminaLevelReached();

	//function to level up a given ability from its spec handle
	void LevelUpAbility(FGameplayAbilitySpecHandle ability);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Initialize")
		TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Initialize")
		TArray <TSubclassOf<class UGASProjectGameplayAbility>> DefaultAbilities;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FGameplayTag HealthMaxLvl;
	FGameplayTag StamMaxLvl;

	bool ASCIBound = false;
public:	
	UFUNCTION(BluePrintCallable, Category = "CharacterAttributes")
	float GetHealth() const;

	UFUNCTION(BluePrintCallable, Category = "CharacterAttributes")
	float GetStamina() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void BindASCInputs();
};
