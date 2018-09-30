// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateMachine/FStateBase.h"
#include "FSRolling.generated.h"

/**
 * 
 */
UCLASS()
class FALLING2_API UFSRolling : public UFStateBase
{
	GENERATED_BODY()
	
public:
	void SetRolling(float lifetime, float distance, FVector direction);
	virtual void EnterState() override;
	virtual void UpdateState(float DeltaTime) override;
	virtual void ExitState() override;;
	
private:
	float CurrentLifeTime = 3.f;
	float PerDistance = 50.f;
	FVector Direction = FVector::ZeroVector;
};
