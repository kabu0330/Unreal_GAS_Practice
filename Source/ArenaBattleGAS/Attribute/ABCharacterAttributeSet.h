// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "ABCharacterAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLEGAS_API UABCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UABCharacterAttributeSet();
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	ATTRIBUTE_ACCESSORS_BASIC(UABCharacterAttributeSet, AttackRange);
	ATTRIBUTE_ACCESSORS_BASIC(UABCharacterAttributeSet, MaxAttackRange);
	ATTRIBUTE_ACCESSORS_BASIC(UABCharacterAttributeSet, AttackRadius);
	ATTRIBUTE_ACCESSORS_BASIC(UABCharacterAttributeSet, MaxAttackRadius);
	ATTRIBUTE_ACCESSORS_BASIC(UABCharacterAttributeSet, AttackRate);
	ATTRIBUTE_ACCESSORS_BASIC(UABCharacterAttributeSet, MaxAttackRate);
	ATTRIBUTE_ACCESSORS_BASIC(UABCharacterAttributeSet, Health);
	ATTRIBUTE_ACCESSORS_BASIC(UABCharacterAttributeSet, MaxHealth);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData AttackRange;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxAttackRange; 

	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData AttackRadius;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxAttackRadius; 

	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData AttackRate;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxAttackRate; 

	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxHealth; 

	
};
