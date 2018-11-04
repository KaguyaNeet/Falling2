// Fill out your copyright notice in the Description page of Project Settings.

#include "FRoomManager.h"
#include "FGameInstance.h"


// Sets default values
AFRoomManager::AFRoomManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AFRoomManager::AddRoomTemplate(AFRoomTemplate * roomTemplate)
{
	if (nullptr == roomTemplate)
	{
		return;
	}
	if (AFRoomManager* manager = GetRoomManager(roomTemplate))
	{
		if (TArray<AFRoomTemplate*>* rooms = manager->RoomTemplates.Find(roomTemplate->RoomType))
		{
			rooms->Add(roomTemplate);
		}
	}
}

// Called when the game starts or when spawned
void AFRoomManager::BeginPlay()
{
	Super::BeginPlay();
	
	for (uint8 i = 0; i < (uint8)ERoomType::EMAX; ++i)
	{
		TArray<AFRoomTemplate*> roomtemplate = TArray<AFRoomTemplate*>();
		RoomTemplates.Add((ERoomType)i, roomtemplate);
	}
}

// Called every frame
void AFRoomManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AFRoomManager * AFRoomManager::GetRoomManager(AActor * caller)
{
	if(UFGameInstance* instance = Cast<UFGameInstance>(caller->GetGameInstance()))
	{
		AFRoomManager* manager = instance->GetRoomManager();
		return manager;
	}
	return nullptr;
}

