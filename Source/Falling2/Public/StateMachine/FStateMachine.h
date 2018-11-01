// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "FBaseState.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FStateMachine.generated.h"

/**
 * 
 */
UCLASS()
class FALLING2_API UFStateMachine : public UObject
{
	GENERATED_BODY()
	
public:
	// States of this state machine
	UPROPERTY()
		TArray<UFBaseState*> States;

	// Current running state of this state machine
	UPROPERTY()
		UFBaseState* CurrentState = nullptr;
	

public:
	// Constructor
	UFStateMachine();

	// Get the current running state's class
	UClass* GetCurrentState();

	//
	bool CheckEqualState(UClass* newState);

	// Update the state machine to a new state
	UFBaseState* UpdateState(UClass* newState);

	// Called by unit's Tick() function, called every frame
	void UpdateStateMachine(float DeltaTime);

	// Release this state machine and all the states that this state machine owned.
	void Release();

};
