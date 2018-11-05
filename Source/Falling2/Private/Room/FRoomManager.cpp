// Fill out your copyright notice in the Description page of Project Settings.

#include "FRoomManager.h"
#include "FGameInstance.h"
#include "FMap.h"
#include "FRoomInstance.h"

#include "Classes/Engine/World.h"


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
		if (TArray<AFRoomTemplate*>* rooms = manager->RoomTemplates.Find(roomTemplate->MapType))
		{
			rooms->Add(roomTemplate);
		}
	}
}

AFMap * AFRoomManager::CreateMap(AActor* caller, EMapType mapType, UINT8 roomNum)
{
	UWorld* world = caller->GetWorld();
	if (nullptr == world)
	{
		return nullptr;
	}

	AFRoomManager* manager = GetRoomManager(caller);
	if (nullptr == manager)
	{
		return nullptr;
	}

	if (AFMap* map = world->SpawnActor<AFMap>(FVector::ZeroVector, FRotator::ZeroRotator))
	{
		TArray<AFRoomTemplate*>* templatesPtr = manager->RoomTemplates.Find(mapType);
		if (nullptr == templatesPtr)
		{
			UE_LOG(LogTemp, Warning, TEXT("No this map type!"));
			return nullptr;
		}
		TArray<AFRoomTemplate*> templates = *templatesPtr;

		TArray<AFRoomTemplate*> startingRooms = FindRooms(templates, ERoomType::EStartingRoom);
		if (startingRooms.Num() <= 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("No starting room of this may type!"));
			return nullptr;
		}
		AFRoomInstance* startingRoom = world->SpawnActor<AFRoomInstance>(FVector::ZeroVector, FRotator::ZeroRotator);
		startingRoom->Initialize(startingRooms[0]);

		map->StartingRoom = startingRoom;

		TArray<AFRoomPortal*> EnablePortals;

		EnablePortals = AddPortals(EnablePortals, startingRoom->GetAllRoomPortals());

		for (int i = 0; i < roomNum; ++i)
		{
			
		}

		return map;
	}
	return nullptr;
}

TArray<AFRoomTemplate*> AFRoomManager::FindRooms(TArray<AFRoomTemplate*>& rooms, ERoomType roomtype)
{
	return TArray<AFRoomTemplate*>();
}

TArray<AFRoomPortal*> AFRoomManager::AddPortals(TArray<AFRoomPortal*> base, TArray<AFRoomPortal*> adds)
{
	for (auto it : adds)
	{
		base.Add(it);
	}
	return base;
}

AFRoomPortal * AFRoomManager::GetEnablePortal(TArray<AFRoomPortal*>& enablePortals)
{
	if (enablePortals.Num() == 0)
		return nullptr;

	int32 luckyOne = FMath::RandRange(0, enablePortals.Num() - 1);
	AFRoomPortal* result = enablePortals[luckyOne];
	enablePortals.RemoveAt(luckyOne);
	return result;
}

TPair<AFRoomInstance*, AFRoomPortal*> AFRoomManager::GetEnableRoom(TArray<AFRoomTemplate*>& rooms, EPortalDirection direction)
{
	TPair<class AFRoomInstance*, AFRoomPortal*> result = TPair<class AFRoomInstance*, AFRoomPortal*>();

	if (rooms.Num() > 0)
	{
		int32 luckyOne = FMath::RandRange(0, rooms.Num() - 1);
		AFRoomInstance* room = rooms[luckyOne]->GetWorld()->SpawnActor<AFRoomInstance>(FVector::ZeroVector, FRotator::ZeroRotator);
		room->Initialize(rooms[luckyOne]);
		
		TArray<AFRoomPortal*> portals = rooms[luckyOne]->GetPortal(direction);
		if (portals.Num() > 0)
		{
			int32 lucky = FMath::RandRange(0, portals.Num() - 1);
			result.Key = room;
			result.Value = portals[lucky];
		}
	}
	
	return result;
}

// Called when the game starts or when spawned
void AFRoomManager::BeginPlay()
{
	Super::BeginPlay();
	
	for (uint8 i = 0; i < (uint8)EMapType::EMAX; ++i)
	{
		TArray<AFRoomTemplate*> roomtemplate = TArray<AFRoomTemplate*>();
		RoomTemplates.Add((EMapType)i, roomtemplate);
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

