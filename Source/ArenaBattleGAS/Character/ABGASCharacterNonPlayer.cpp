// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGASCharacterNonPlayer.h"

#include "AbilitySystemComponent.h"
#include "Attribute/ABCharacterAttributeSet.h"


AABGASCharacterNonPlayer::AABGASCharacterNonPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>("ASC");
	AttributeSet = CreateDefaultSubobject<UABCharacterAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AABGASCharacterNonPlayer::GetAbilitySystemComponent() const
{
	return ASC;
}

void AABGASCharacterNonPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	ASC->InitAbilityActorInfo(this, this);
}

void AABGASCharacterNonPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void AABGASCharacterNonPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AABGASCharacterNonPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

