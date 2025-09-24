// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGASCharacterPlayer.h"

#include "AbilitySystemComponent.h"
#include "Player/ABGASPlayerState.h"


AABGASCharacterPlayer::AABGASCharacterPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	ASC = nullptr;
}

UAbilitySystemComponent* AABGASCharacterPlayer::GetAbilitySystemComponent() const
{
	return ASC;
}

void AABGASCharacterPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AABGASPlayerState* GASPS = Cast<AABGASPlayerState>(NewController->PlayerState);
	if (GASPS)
	{
		ASC = GASPS->GetAbilitySystemComponent();
		ASC->InitAbilityActorInfo(GASPS, this);

		for (const auto& StartAbility : StartAbilities)
		{
			FGameplayAbilitySpec StartSpec(StartAbility);
			ASC->GiveAbility(StartSpec);
		}
	}
}

void AABGASCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void AABGASCharacterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AABGASCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

