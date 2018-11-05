// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FRoomInstance.generated.h"

UCLASS()
class FALLING2_API AFRoomInstance : public AActor
{
	GENERATED_BODY()
	
private:
	// The template of this room
	class AFRoomTemplate* RoomTemplate = nullptr;

public:	
	// Sets default values for this actor's properties
	AFRoomInstance();

	// Initialize this room
	void Initialize(class AFRoomTemplate* room);

	// Get all portals of this room
	TArray<class AFRoomPortal*> GetAllRoomPortals();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
