// Fill out your copyright notice in the Description page of Project Settings.


#include "ABTA_Trace.h"

#include "Abilities/GameplayAbility.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Physics/ABCollision.h"


AABTA_Trace::AABTA_Trace()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AABTA_Trace::BeginPlay()
{
	Super::BeginPlay();
	
}

void AABTA_Trace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AABTA_Trace::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);

	SourceActor = Ability->GetCurrentActorInfo()->AvatarActor.Get();
}

void AABTA_Trace::ConfirmTargetingAndContinue()
{
	//Super::ConfirmTargetingAndContinue();

	if (SourceActor)
	{
		FGameplayAbilityTargetDataHandle TargetData = MakeTargetData();
		TargetDataReadyDelegate.Broadcast(TargetData);
	}
}

FGameplayAbilityTargetDataHandle AABTA_Trace::MakeTargetData() const
{
	ACharacter* Character = CastChecked<ACharacter>(SourceActor);
	FHitResult HitResult;

	const float AttackRange = 100.0f;
	const float AttackRadius = 50.f;

	FCollisionQueryParams Params(SCENE_QUERY_STAT(UABTA_Trace), false, Character);
	const FVector Forward = Character->GetActorForwardVector();
	const FVector Start = Character->GetActorLocation() + Forward * Character->GetCapsuleComponent()->GetScaledCapsuleRadius();
	const FVector End = Start + Forward * AttackRange;

	bool HitDetected = GetWorld()->SweepSingleByChannel(
		HitResult, Start, End, FQuat::Identity, CCHANNEL_ABACTION,
		FCollisionShape::MakeSphere(AttackRadius), Params);

	FGameplayAbilityTargetDataHandle DataHandle;
	if (HitDetected)
	{
		FGameplayAbilityTargetData_SingleTargetHit* TargetData = new FGameplayAbilityTargetData_SingleTargetHit(HitResult);
		DataHandle.Add(TargetData);
	}

#if ENABLE_DRAW_DEBUG
	if (bShowDebug)
	{
		FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
		float CapsuleHalfHeight = AttackRange * 0.5f;
		FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;
		DrawDebugCapsule(
			GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttackRadius,
			FRotationMatrix::MakeFromZ(Forward).ToQuat(), DrawColor,
			false, 5.0f);
	}
#endif

	return DataHandle;
}

