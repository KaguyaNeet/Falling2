// Fill out your copyright notice in the Description page of Project Settings.

#include "FSRolling.h"
#include "FBaseUnit.h"
#include "FStateMachine.h"
#include "FCharacter.h"
#include "FPlayer.h"

#include "Classes/GameFramework/CharacterMovementComponent.h"
#include "Classes/Components/SkeletalMeshComponent.h"


void UFSRolling::EnterState()
{

}

void UFSRolling::UpdateState(float DeltaTime)
{
	if (nullptr != StateOwner && CurrentLifeTime > 0.f)
	{
		CurrentLifeTime -= DeltaTime;
		StateOwner->GetMovementComponent()->Velocity = Direction * PerDistance;
	}
	else if (nullptr != StateOwner && nullptr != StateOwner->StateMachine)
	{
		StateOwner->StateMachine->ChangeState(UFSPlayerBaseMove::StaticClass());
	}
}

void UFSRolling::ExitState()
{

}

void UFSRolling::SetRolling(float lifetime, float distance, FVector direction)
{
	CurrentLifeTime = lifetime;
	PerDistance = distance / lifetime;
	direction.Normalize();
	Direction = direction;
	if (AFCharacter* character = Cast<AFCharacter>(StateOwner))
	{
		FVector faceDirection = FVector::ZeroVector;
		if (AFPlayer* player = Cast<AFPlayer>(character))
		{
			faceDirection = player->Direction;
		}
		else
		{
			faceDirection = character->GetMesh()->GetForwardVector();
		}
		FRotator faceRotation = FVector(faceDirection.X, faceDirection.Y, 0.f).Rotation();
		character->GetMesh()->SetRelativeRotation(faceRotation.Quaternion());

		float offset = faceRotation.Yaw - direction.Rotation().Yaw;

		if (FMath::Abs(offset) > 180.f)
		{
			float sign;
			sign = direction.Rotation().Yaw >= 0.f ? 1.f : -1.f;
			offset = sign * (360.f - (FMath::Abs(faceRotation.Yaw) + FMath::Abs(direction.Rotation().Yaw)));
		}

		float a = character->AngleAlpha;
		UINT8 playNum = 0;
		if (offset <= a && offset >= -a) playNum = 0;
		else if (offset <= 90.f + a && offset >= 90.f - a) playNum = 1;
		else if (offset <= -90.f + a && offset >= -90.f - a) playNum = 2;
		else if (offset <= -180.f + a || offset >= 180.f - a) playNum = 3;
		else if (FMath::Abs(offset) < 90.f)
		{
			character->GetMesh()->SetRelativeRotation(direction.Rotation().Quaternion());
			playNum = 0;
		}
		else
		{
			character->GetMesh()->SetRelativeRotation((-direction).Rotation().Quaternion());
			playNum = 3;
		}
		character->PlayRollingAnimation(playNum);
	}
}

