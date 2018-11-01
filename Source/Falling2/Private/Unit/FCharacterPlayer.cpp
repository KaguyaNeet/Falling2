// Fill out your copyright notice in the Description page of Project Settings.

#include "FCharacterPlayer.h"



void AFCharacterPlayer::SetupPlayerInputComponent(UInputComponent* inputComponent)
{
	Super::SetupPlayerInputComponent(inputComponent);

	inputComponent->BindAxis("MoveForward", this, &AFCharacterPlayer::MoveForward);
	inputComponent->BindAxis("MoveRight", this, &AFCharacterPlayer::MoveRight);

	inputComponent->BindAction("MainFire", IE_Pressed, this, &AFCharacterPlayer::LeftMouseButtonDown);
	inputComponent->BindAction("MainFire", IE_Released, this, &AFCharacterPlayer::LeftMouseButtonUp);
	inputComponent->BindAction("SecondaryFire", IE_Pressed, this, &AFCharacterPlayer::RightMouseButtonDown);
	inputComponent->BindAction("SecondaryFire", IE_Released, this, &AFCharacterPlayer::RightMouseButtonUp);
	inputComponent->BindAction("Rolling", IE_Pressed, this, &AFCharacterPlayer::TriggerRolling);
	inputComponent->BindAction("Pick", IE_Pressed, this, &AFCharacterPlayer::PickUp);
}

void AFCharacterPlayer::MoveForward(float value)
{
}

void AFCharacterPlayer::MoveRight(float value)
{
}

void AFCharacterPlayer::LeftMouseButtonDown()
{
}

void AFCharacterPlayer::LeftMouseButtonUp()
{
}

void AFCharacterPlayer::RightMouseButtonDown()
{
}

void AFCharacterPlayer::RightMouseButtonUp()
{
}

void AFCharacterPlayer::TriggerRolling()
{
}

void AFCharacterPlayer::PickUp()
{
}
