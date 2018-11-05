// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "FRoomTemplate.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FMap.generated.h"

UCLASS()
class FALLING2_API AFMap : public AActor
{
	GENERATED_BODY()
	
public:
	// Type of this map
	EMapType MapType = EMapType::ENormal;

	// Connections of all the portals
	TPair<class AFRoomPortal*, class AFRoomPortal*> Portals;

	// Starting room of this map
	class AFRoomInstance* StartingRoom = nullptr;

public:	
	// Sets default values for this actor's properties
	AFMap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
