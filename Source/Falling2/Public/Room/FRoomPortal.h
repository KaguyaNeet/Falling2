// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FRoomPortal.generated.h"

UENUM(BlueprintType)
enum class EPortalDirection : uint8
{
	EUp UMETA(DisplayName = "Up"),
	EDown UMETA(DisplayName = "Up"),
	ERight UMETA(DisplayName = "Right"),
	ELeft UMETA(DisplayName = "Left"),
	EMAX
};

UCLASS()
class FALLING2_API AFRoomPortal : public AActor
{
	GENERATED_BODY()
	
public:
	// The direction of this room
	EPortalDirection PortalDirection = EPortalDirection::EDown;

public:	
	// Sets default values for this actor's properties
	AFRoomPortal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
