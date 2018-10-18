// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Unit/FCharacter.h"
#include "FAICharacter.generated.h"

/**
 * 
 */
UCLASS()
class FALLING2_API AFAICharacter : public AFCharacter
{
	GENERATED_BODY()
	
public:
	AFAICharacter();

public:
	UPROPERTY(EditAnywhere, Category = "AI")
		class UBehaviorTree* BehaviorTree = nullptr;
	UPROPERTY(EditAnywhere, Category = "AI")
		float AlertDistance = 1000.f;
	
};
