// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGASFountain.h"

#include "AbilitySystemComponent.h"
#include "ArenaBattleGAS.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "GameplayAbilitySpec.h"
#include "Tag/ABGameplayTags.h"
//#include "GA/ABGA_Rotate.h"

AABGASFountain::AABGASFountain()
{
	PrimaryActorTick.bCanEverTick = true;

	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>("RotatingMovement");
	ActionPeriod = 3.0f;

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>("ASC");
}

UAbilitySystemComponent* AABGASFountain::GetAbilitySystemComponent() const
{
	return ASC;
}

void AABGASFountain::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(ActionTimer, this, &AABGASFountain::TimerAction,
		ActionPeriod, true, 0.0f);
}

void AABGASFountain::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	RotatingMovement->bAutoActivate = false;
	RotatingMovement->Deactivate();

	ASC->InitAbilityActorInfo(this, this);
	for (const auto& StartAbility : StartAbilities)
	{
		FGameplayAbilitySpec StartSpec(StartAbility);
		ASC->GiveAbility(StartSpec);
	}
	//FGameplayAbilitySpec RotateSkillSpec(UABGA_Rotate::StaticClass());
	//ASC->GiveAbility(RotateSkillSpec);
}

void AABGASFountain::TimerAction()
{
	ABGAS_LOG(LogABGAS, Log, TEXT("Begin"));

	FGameplayTagContainer TargetTag(ABTAG_ACTOR_ROTATE);
	if (!ASC->HasMatchingGameplayTag(ABTAG_ACTOR_ISROTATING))
	{
		ASC->TryActivateAbilitiesByTag(TargetTag);
	}
	else
	{
		ASC->CancelAbilities(&TargetTag);
	}
	
	// FGameplayAbilitySpec* RotateGASpec = ASC->FindAbilitySpecFromClass(UABGA_Rotate::StaticClass());
	// if (!RotateGASpec)
	// {
	// 	ABGAS_LOG(LogABGAS, Log, TEXT("RotateGASpec is null"));
	// 	return;
	// }
	//
	// if (!RotateGASpec->IsActive())
	// {
	// 	ASC->TryActivateAbility(RotateGASpec->Handle);
	// }
	// else
	// {
	// 	ASC->CancelAbilityHandle(RotateGASpec->Handle);	
	// }
	
	// if (!RotatingMovement->IsActive())
	// {
	// 	RotatingMovement->Activate(true);
	// }
	// else
	// {
	// 	RotatingMovement->Deactivate();
	// }
}

void AABGASFountain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

