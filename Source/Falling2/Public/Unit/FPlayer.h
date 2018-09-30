// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Unit/FCharacter.h"
#include "FPlayer.generated.h"

/**
 * 
 */
UCLASS()
class FALLING2_API AFPlayer : public AFCharacter
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UArrowComponent* CorrectionArrow;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerProperty")
		float CurrentOffset = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerProperty")
		float VelocityOffset = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerProperty")
		bool Turn = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerProperty")
		bool RightTurn = false;

	UPROPERTY(EditAnywhere, Category = "PlayerProperty")
		float RollingDistance = 1000.f;
	UPROPERTY(EditAnywhere, Category = "PlayerProperty")
		float LifeTime = 1.f;

	FVector Direction = FVector::ZeroVector;
private:
	
	FHitResult lastHit;
	

public:
	AFPlayer();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* inputComponent) override;

	void PlayerBaseAnimUpdate(float DeltaTime);

private:
	void MoveForward(float value);
	void MoveRight(float value);

	void LeftMouseButtonDown();
	void LeftMouseButtonUp();
	void RightMouseButtonDown();
	void RightMouseButtonUp();

	void TriggerRolling();
	
	
};
