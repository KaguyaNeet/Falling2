// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FItemManager.generated.h"

UCLASS()
class FALLING2_API AFItemManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFItemManager();

	static class AFBaseItem* CreateItem(AActor* caller, FName itemName);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	TArray<FName> ItemNames;
	class UDataTable* WeaponTable = nullptr;
	class UDataTable* ClipTable = nullptr;
	
};
