// Fill out your copyright notice in the Description page of Project Settings.

#include "FGameInstance.h"
#include "FItemManager.h"

AFItemManager * UFGameInstance::GetItemManager()
{
	if (nullptr == ItemManager)
	{
		if (UWorld* world = GetWorld())
		{
			ItemManager = world->SpawnActor<AFItemManager>(FVector::ZeroVector, FRotator::ZeroRotator);
		}
	}
	return ItemManager;
}
