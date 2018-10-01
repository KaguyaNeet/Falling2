// Fill out your copyright notice in the Description page of Project Settings.

#include "FCharacter.h"
#include "FStateMachine.h"



void AFCharacter::Rolling(float lifetime, float distance, FVector direction)
{
	if (nullptr != StateMachine)
	{
		if (UFSRolling* state = Cast<UFSRolling>(StateMachine->ChangeState(UFSRolling::StaticClass())))
		{
			state->SetRolling(lifetime, distance, direction);
		}
		
	}
}

void AFCharacter::PlayRollingAnimation(UINT8 num)
{
	UAnimMontage* montage = nullptr;
	switch (num)
	{
		case 0:montage = RollingFront; break;
		case 1:montage = RollingLeft; break;
		case 2:montage = RollingRight; break;
		case 3:montage = FMath::FRand() > 0.5f ? RollingBack : RollingBack2; break;
		default:montage = RollingFront; break;
	}
	PlayAnimMontage(montage, 1.f, FName("Default"));
}
