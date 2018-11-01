// Fill out your copyright notice in the Description page of Project Settings.

#include "FPlayerAnimState_Moving.h"
#include "FCharacterPlayer.h"

void UFPlayerAnimState_Moving::EnterState()
{
	OwnerPlayer = Cast<AFCharacterPlayer>(StateOwner);
}

void UFPlayerAnimState_Moving::UpdateState(float DeltaTime)
{
	if (nullptr != OwnerPlayer)
	{
		//wnerPlayer->PlayerBaseAnimUpdate(DeltaTime);
	}
}
