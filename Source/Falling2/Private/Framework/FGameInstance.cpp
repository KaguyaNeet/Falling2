// Fill out your copyright notice in the Description page of Project Settings.

#include "FGameInstance.h"
#include "FBuffManager.h"

AFBuffManager * UFGameInstance::GetBuffManager()
{
	if (nullptr == BuffManager)
	{
		UWorld* world = GetWorld();
		BuffManager = world->SpawnActor<AFBuffManager>(FVector::ZeroVector, FRotator::ZeroRotator);
	}
	return BuffManager;
}
