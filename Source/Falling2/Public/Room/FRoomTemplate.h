// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "FRoomPortal.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FRoomTemplate.generated.h"

UENUM(BlueprintType)
enum class EMapType : uint8
{
	ENormal,

	ESpaceStation UMETA(DisplayName = "SpaceStation"),

	EMAX
};

UENUM(BlueprintType)
enum class ERoomType : uint8
{
	ENormal,

	EStartingRoom UMETA(DisplayName = "StartingRoom"),
	EBossRoom UMETA(DisplayName = "BossRoom"),
	EReward UMETA(DisplayName = "RewardRoom"),

	EMAX
};

UCLASS()
class FALLING2_API AFRoomTemplate : public AActor
{
	GENERATED_BODY()

public:
	// Type of this map
	EMapType MapType = EMapType::ENormal;

	// Type of this room template
	ERoomType RoomType = ERoomType::ENormal;

	// Portals of this Room
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RoomProperty")
		TArray<AFRoomPortal*> RoomPortals;
	
public:	
	// Sets default values for this actor's properties
	AFRoomTemplate();


	// Get portal of this direction
	TArray<AFRoomPortal*> GetPortal(EPortalDirection direction);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
