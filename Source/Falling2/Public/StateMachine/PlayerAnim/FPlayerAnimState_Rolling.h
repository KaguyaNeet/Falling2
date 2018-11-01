// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateMachine/FBaseState.h"
#include "FPlayerAnimState_Rolling.generated.h"

/**
 * 
 */
UCLASS()
class FALLING2_API UFPlayerAnimState_Rolling : public UFBaseState
{
	GENERATED_BODY()
	
public:
	// Set the rolling info
	void SetRolling(float lifetime, float distance, FVector direction);

	// Update the rolling state
	virtual void UpdateState(float DeltaTime) override;

private:
	// This state's lifetime
	float RollingTimer = 3.f;
	
	// Rolling distance per second
	float PerDistance = 50.f;

	// The direction of rolling
	FVector Direction = FVector::ZeroVector;
};
