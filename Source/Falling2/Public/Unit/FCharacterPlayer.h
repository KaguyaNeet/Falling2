// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Unit/FCharacterUnit.h"
#include "FCharacterPlayer.generated.h"

/**
 * 
 */
UCLASS()
class FALLING2_API AFCharacterPlayer : public AFCharacterUnit
{
	GENERATED_BODY()
	
public:
	// Input function
	virtual void SetupPlayerInputComponent(class UInputComponent* inputComponent) override;
	
private:

	// These functions are attaching with the input component
	void MoveForward(float value);
	void MoveRight(float value);

	void LeftMouseButtonDown();
	void LeftMouseButtonUp();
	void RightMouseButtonDown();
	void RightMouseButtonUp();

	void TriggerRolling();

	void PickUp();
};
