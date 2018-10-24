// Fill out your copyright notice in the Description page of Project Settings.

#include "FBTService.h"
#include "FAIController.h"
#include "FAICharacter.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"


void UFBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AFAIController* controller = Cast<AFAIController>(OwnerComp.GetAIOwner());
	AFAICharacter* character = Cast<AFAICharacter>(OwnerComp.GetAIOwner()->GetPawn());
	UBlackboardComponent* blackboard = OwnerComp.GetAIOwner()->GetBlackboardComponent();
	if (nullptr != controller && nullptr != character && nullptr != blackboard)
	{
		
		if (AFBaseUnit* unit = Cast<AFBaseUnit>(blackboard->GetValueAsObject(FName("Target"))))
		{
			float distance = FVector::Distance(unit->GetActorLocation(), character->GetActorLocation());
			blackboard->SetValueAsFloat(FName("Distance"), distance);
		}
		else
		{
			if (AFBaseUnit* unit = Cast<AFBaseUnit>(UGameplayStatics::GetPlayerController(controller, 0)->GetPawn()))
			{
				blackboard->SetValueAsObject(FName("Target"), unit);
			}
		}
		blackboard->SetValueAsEnum(FName("AIState"), (uint8)controller->UpdateAIState());
	}
}