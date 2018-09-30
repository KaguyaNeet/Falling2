// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FALLING2_API UFPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
	
public:
	UFPlayerAnimInstance();

	UFUNCTION(BlueprintCallable)
		void Tick(float DeltaTime);
	UFUNCTION(BlueprintCallable)
		void EndRolling();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Property")
		float OwnerMoveSpeed = 0.f;
	UPROPERTY(BlueprintReadOnly, Category = "Property")
		float AimOffset = 0.f;
	UPROPERTY(BlueprintReadOnly, Category = "Property")
		float VelocityOffset = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
		float TurnSpeed = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
		float TurnAnimPlaySpeed = 0.f;
	UPROPERTY(BlueprintReadOnly, Category = "Property")
		bool isTurn = false;
	UPROPERTY(BlueprintReadOnly, Category = "Property")
		bool isRightTurn = false;
	UPROPERTY(BlueprintReadOnly, Category = "Property")
		bool isIdleTurn = false;
	UPROPERTY(BlueprintReadOnly, Category = "Property")
		bool isRolling = false;
	UPROPERTY(BlueprintReadOnly, Category = "Property")
		bool isFrontRolling = true;
	UPROPERTY(BlueprintReadOnly, Category = "Property")
		float RollingDirection = 0.f;
	
};
