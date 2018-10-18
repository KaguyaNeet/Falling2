// Fill out your copyright notice in the Description page of Project Settings.

#include "FAICharacter.h"
#include "FAIController.h"


AFAICharacter::AFAICharacter()
{
	AIControllerClass = AFAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

