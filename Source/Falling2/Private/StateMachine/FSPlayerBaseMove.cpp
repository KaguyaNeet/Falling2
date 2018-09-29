// Fill out your copyright notice in the Description page of Project Settings.

#include "FSPlayerBaseMove.h"
#include "FPlayer.h"


void UFSPlayerBaseMove::EnterState()
{
	AFPlayer* player = Cast<AFPlayer>(StateOwner);
	OwnerPlayer = (nullptr != player) ? player : nullptr; 
}
void UFSPlayerBaseMove::UpdateState(float DeltaTime)
{
	if (nullptr != OwnerPlayer)
	{
		OwnerPlayer->PlayerBaseAnimUpdate(DeltaTime);
	}
}
void UFSPlayerBaseMove::ExitState()
{

}
