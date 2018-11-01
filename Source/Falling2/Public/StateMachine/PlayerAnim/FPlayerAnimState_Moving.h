// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateMachine/FBaseState.h"
#include "FPlayerAnimState_Moving.generated.h"

/**
 * 
 */
UCLASS()
class FALLING2_API UFPlayerAnimState_Moving : public UFBaseState
{
	GENERATED_BODY()
	
public:
	// The owner player of this state
	class AFCharacterPlayer* OwnerPlayer = nullptr;

public:
	// Enter this state
	virtual void EnterState() override;

	// Update this state
	virtual void UpdateState(float DeltaTime) override;
};
