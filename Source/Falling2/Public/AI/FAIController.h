// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FAIController.generated.h"

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

protected:
	virtual void Tick(float DeltaTime) override;
	
	
public:
	UPROPERTY()
		class UBehaviorTreeComponent* BehaviorTreeComponent;
	UPROPERTY()
		class UBlackboardComponent* BlackboardComponent;
	
	
};
