// Fill out your copyright notice in the Description page of Project Settings.

#include "FGameInstance.h"
#include "FItemManager.h"
#include "FBuffManager.h"

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

UFBuffManager * UFGameInstance::GetBuffManager()
{
	if (nullptr == BuffManager)
	{
		BuffManager = NewObject<UFBuffManager>();
	}
	return BuffManager;
}
