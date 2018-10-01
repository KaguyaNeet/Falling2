// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Unit/FBaseUnit.h"
#include "FCharacter.generated.h"

/**
 * 
 */
UCLASS()
class FALLING2_API AFCharacter : public AFBaseUnit
{
	GENERATED_BODY()
	
public:
	void Rolling(float lifetime, float distance, FVector direction);
	void PlayRollingAnimation(UINT8 num);
public:
	UPROPERTY(EditAnywhere, Category = "RollingMontage")
		UAnimMontage* RollingFront = nullptr;
	UPROPERTY(EditAnywhere, Category = "RollingMontage")
		UAnimMontage* RollingBack = nullptr;
	UPROPERTY(EditAnywhere, Category = "RollingMontage")
		UAnimMontage* RollingBack2 = nullptr;
	UPROPERTY(EditAnywhere, Category = "RollingMontage")
		UAnimMontage* RollingRight = nullptr;
	UPROPERTY(EditAnywhere, Category = "RollingMontage")
		UAnimMontage* RollingLeft = nullptr;
	UPROPERTY(EditAnywhere, Category = "RollingMontage")
		float AngleAlpha = 10.f;
};
