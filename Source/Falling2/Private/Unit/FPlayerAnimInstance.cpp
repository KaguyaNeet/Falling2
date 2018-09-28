// Fill out your copyright notice in the Description page of Project Settings.

#include "FPlayerAnimInstance.h"
#include "FPlayer.h"

#include "Classes/GameFramework/CharacterMovementComponent.h"


UFPlayerAnimInstance::UFPlayerAnimInstance()
{
	TurnSpeed = 70.f;
	TurnAnimPlaySpeed = 1.5f;
}

void UFPlayerAnimInstance::Tick(float DeltaTime)
{
	if (AFPlayer* player = Cast<AFPlayer>(TryGetPawnOwner()))
	{
		OwnerMoveSpeed = (player->GetVelocity().Size() / player->GetCharacterMovement()->MaxWalkSpeed) * 375.f;
		AimOffset = player->CurrentOffset;
		VelocityOffset = player->VelocityOffset;
		isTurn = player->Turn;
		isRightTurn = player->RightTurn;
		isIdleTurn = OwnerMoveSpeed > 0.f ? false : true;
	}
}