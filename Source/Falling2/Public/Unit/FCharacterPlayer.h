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
	//Cameraboom of this player.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class USpringArmComponent* SpringArm;
	//Main camera of this game.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UCameraComponent* Camera;
	//The arrow help for repairing the mesh direction.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UArrowComponent* CorrectionArrow;

public:
	// Constructor
	AFCharacterPlayer();

	// Input function
	virtual void SetupPlayerInputComponent(class UInputComponent* inputComponent) override;

	// Begin play function
	virtual void BeginPlay() override;

	// Tick function
	virtual void Tick(float DeltaTime) override;
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
