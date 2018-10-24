// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FAIController.generated.h"

UENUM(BlueprintType)
enum class EAIState : uint8
{
	EPatrol UMETA(DisplayName = "Patrol"),
	ETrack UMETA(DisplayName = "Track"),
	EAttack UMETA(DisplayName = "Attack"),
};

/**
 * 
 */
UCLASS()
class FALLING2_API AFAIController : public AAIController
{
	GENERATED_BODY()

public:
	AFAIController();

	virtual void BeginPlay() override;

	virtual void Possess(APawn* InPawn) override;

	virtual EAIState UpdateAIState();

protected:
	virtual void Tick(float DeltaTime) override;
	
public:
	UPROPERTY()
		class UBehaviorTreeComponent* BehaviorTreeComponent;
	UPROPERTY()
		class UBlackboardComponent* BlackboardComponent;

	UPROPERTY(BlueprintReadWrite)
		EAIState AIState = EAIState::EPatrol;
	
	
};
