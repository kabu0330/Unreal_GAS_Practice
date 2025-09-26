﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "ABAT_Trace.generated.h"

class AABTA_Trace;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTraceResultDelegate, const FGameplayAbilityTargetDataHandle&, TargetDataHandle);
/**
 * 
 */
UCLASS()
class ARENABATTLEGAS_API UABAT_Trace : public UAbilityTask
{
	GENERATED_BODY()

public:
	UABAT_Trace();

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "WaitingForTrace",HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UABAT_Trace* CreateTask(UGameplayAbility* OwningAbility, TSubclassOf<AABTA_Trace> TargetActorClass);
	virtual void Activate() override;
	virtual void OnDestroy(bool AbilityEndedNormally) override;

	void SpawnAndInitializeTargetActor();
	void FinalizeTargetActor();

protected:
	void OnTargetDataReadyCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle);

	UPROPERTY()
	TSubclassOf<AABTA_Trace> TargetActorClass;

	UPROPERTY()
	TObjectPtr<AABTA_Trace> SpawnedTargetActor;

public:
	UPROPERTY(BlueprintAssignable)
	FTraceResultDelegate OnComplete;
};
