// Fill out your copyright notice in the Description page of Project Settings.

#include "FRoomTemplate.h"
#include "FRoomManager.h"


// Sets default values
AFRoomTemplate::AFRoomTemplate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

TArray<AFRoomPortal*> AFRoomTemplate::GetPortal(EPortalDirection direction)
{
	TArray<AFRoomPortal*> result = TArray<AFRoomPortal*>();
	for (auto it : RoomPortals)
	{
		if (direction == it->PortalDirection)
		{
			result.Add(it);
		}
	}
	return result;
}

// Called when the game starts or when spawned
void AFRoomTemplate::BeginPlay()
{
	Super::BeginPlay();
	
	AFRoomManager::AddRoomTemplate(this);
}

// Called every frame
void AFRoomTemplate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

