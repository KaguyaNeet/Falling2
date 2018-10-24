// Fill out your copyright notice in the Description page of Project Settings.

#include "FAIController.h"
#include "FAICharacter.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


AFAIController::AFAIController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree"));

	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
}

void AFAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateAIState();
}

void AFAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AFAIController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	AFAICharacter* unit = Cast<AFAICharacter>(InPawn);
	if (nullptr != unit && nullptr != unit->BehaviorTree && nullptr != unit->BehaviorTree->BlackboardAsset)
	{
		BlackboardComponent->InitializeBlackboard(*unit->BehaviorTree->BlackboardAsset);
		Blackboard = BlackboardComponent;
		BehaviorTreeComponent->StartTree(*unit->BehaviorTree);
	}
}


EAIState AFAIController::UpdateAIState()
{
	EAIState result = EAIState::EPatrol;
	if (nullptr != Blackboard)
	{
		if (AFAICharacter* character = Cast<AFAICharacter>(GetPawn()))
		{
			float distance = Blackboard->GetValueAsFloat(FName("Distance"));
			if (distance <= character->AlertDistance)
			{
				result = EAIState::ETrack;
			}
			else
			{
				result = EAIState::EPatrol;
			}
			if (distance <= character->AttackDistance)
			{
				result = EAIState::EAttack;
			}
		}
	}
	return result;
}