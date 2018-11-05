// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "FRoomTemplate.h"
#include "FRoomPortal.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FRoomManager.generated.h"

UCLASS()
class FALLING2_API AFRoomManager : public AActor
{
	GENERATED_BODY()

private:
	// All the template rooms
	TMap<EMapType, TArray<AFRoomTemplate*> > RoomTemplates;

	
public:	
	// Sets default values for this actor's properties
	AFRoomManager();

	// Add Room template to room manager
	static void AddRoomTemplate(AFRoomTemplate* roomTemplate);

	// Create map
	static class AFMap* CreateMap(AActor* caller, EMapType mapType, UINT8 roomNum);

private:
	// Find room with room type
	static TArray<AFRoomTemplate*> FindRooms(TArray<AFRoomTemplate*>& rooms, ERoomType roomtype);

	// Add portals to the base portal array
	static TArray<AFRoomPortal*> AddPortals(TArray<AFRoomPortal*> base, TArray<AFRoomPortal*> adds);

	// Get a portal from enable portal array
	static class AFRoomPortal* GetEnablePortal(TArray<AFRoomPortal*>& enablePortals);

	// Rand a room from template
	static TPair<class AFRoomInstance*, AFRoomPortal*> GetEnableRoom(TArray<AFRoomTemplate*>& rooms, EPortalDirection direction);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Get room manager singleton
	static AFRoomManager* GetRoomManager(AActor* caller);

	
	
};
