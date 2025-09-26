// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGASCharacterPlayer.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "Player/ABGASPlayerState.h"


AABGASCharacterPlayer::AABGASCharacterPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	ASC = nullptr;
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ComboActionMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/ArenaBattleGas/Animation/AM_ComboAttack.AM_ComboAttack'"));
	if (ComboActionMontageRef.Object)
	{
		ComboActionMontage = ComboActionMontageRef.Object;
	}
}

UAbilitySystemComponent* AABGASCharacterPlayer::GetAbilitySystemComponent() const
{
	return ASC; 
}

void AABGASCharacterPlayer::SetupAbilitySystemComponent()
{
	AABGASPlayerState* GASPS = Cast<AABGASPlayerState>(GetPlayerState());
	if (GASPS)
	{
		ASC = GASPS->GetAbilitySystemComponent();
		ASC->InitAbilityActorInfo(GASPS, this);

		int32 InputId = 0;
		for (const auto& StartAbility : StartAbilities)
		{
			FGameplayAbilitySpec StartSpec(StartAbility);
			ASC->GiveAbility(StartSpec);
		}

		for (const auto& StartInputAbility : StartInputAbilities)
		{
			FGameplayAbilitySpec StartSpec(StartInputAbility.Value);
			StartSpec.InputID = static_cast<int>(StartInputAbility.Key);
			ASC->GiveAbility(StartSpec);
		}
	}
	SetupGASInputComponent();

	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	PlayerController->ConsoleCommand(TEXT("showdebug abilitysystem"));
}

// 서버에서만 호출
void AABGASCharacterPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	SetupAbilitySystemComponent();

}

void AABGASCharacterPlayer::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	//SetupAbilitySystemComponent();
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
	SetupGASInputComponent();
}

void AABGASCharacterPlayer::SetupGASInputComponent()
{
	if (IsValid(ASC) && IsValid(InputComponent))
	{
		UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AABGASCharacterPlayer::GASInputPressed, EGAType::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AABGASCharacterPlayer::GASInputReleased, EGAType::Jump);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AABGASCharacterPlayer::GASInputPressed, EGAType::Attack);
	}
}

void AABGASCharacterPlayer::GASInputPressed(EGAType InputId)
{
	UE_LOG(LogTemp, Warning, TEXT("GASInputPressed"));
	FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromInputID(static_cast<int>(InputId));
	if (Spec)
	{
		Spec->InputPressed = true;
		if (Spec->IsActive())
		{
			ASC->AbilitySpecInputPressed(*Spec);
		}
		else
		{
			ASC->TryActivateAbility(Spec->Handle);
		}
	}
}

void AABGASCharacterPlayer::GASInputReleased(EGAType InputId)
{
	FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromInputID(static_cast<int>(InputId));
	if (Spec)
	{
		Spec->InputPressed = false;
		if (Spec->IsActive())
		{
			ASC->AbilitySpecInputReleased(*Spec);
		}
	}
}



