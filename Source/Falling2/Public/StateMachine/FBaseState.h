// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FBaseState.generated.h"

/**
 * 
 */
UCLASS()
class FALLING2_API UFBaseState : public UObject
{
	GENERATED_BODY()
	
public:
	// The owner of this state
	class AFBaseUnit* StateOwner = nullptr;

public:
	// Initialize the state, set the owner
	void Initialize(class AFBaseUnit* owner);

	// Exit this state
	virtual void ExitState(){ }

	// Enter this state
	virtual void EnterState(){ }

	// Update this state
	virtual void UpdateState(float DeltaTime){ }

	// Release the state, called from statemachine's release function
	virtual void Release();
	
};
