// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GASProjectAttributeSet.generated.h"

/**
 * 
 */

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class GASASSIGNMENTPROJECT_API UGASProjectAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UGASProjectAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = "OnRep_Health")
		FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UGASProjectAttributeSet, Health)

		UFUNCTION()
		virtual void Onrep_Health(const FGameplayAttributeData& oldHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = "OnRep_Stamina")
		FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UGASProjectAttributeSet, Stamina)

		UFUNCTION()
		virtual void Onrep_Stamina(const FGameplayAttributeData& oldStam);
};
