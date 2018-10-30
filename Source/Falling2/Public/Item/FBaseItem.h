// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine/DataTable.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FBaseItem.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	EGun UMETA(DisplayName = "Gun"),
	EThrowable UMETA(DisplayName = "Throwable"),
	EBlade UMETA(DisplayName = "Blade")
};

UENUM(BlueprintType)
enum class EItemQuality : uint8
{
	ENormal = 1 UMETA(DisplayName = "Normal")
};

UCLASS()
class FALLING2_API AFBaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFBaseItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
