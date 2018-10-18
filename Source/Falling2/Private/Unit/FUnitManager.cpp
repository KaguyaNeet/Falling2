// Fill out your copyright notice in the Description page of Project Settings.

#include "FUnitManager.h"
#include "FBaseUnit.h"
#include "FGameInstance.h"


// Sets default values
AFUnitManager::AFUnitManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFUnitManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFUnitManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateUnits();
}

float AFUnitManager::GetUnitsDistance(AActor* caller, AFBaseUnit* unit1, AFBaseUnit* unit2)
{
	if (AFUnitManager* manager = GetUnitManager(caller))
	{
		if (loc* l1 = manager->Units.Find(unit1))
		{
			if (loc* l2 = manager->Units.Find(unit2))
			{
				if (loc::Adjacent(*l1, *l2))
				{
					return FVector::Distance(unit1->GetActorLocation(), unit2->GetActorLocation());
				}
			}
		}
	}
	return -1.f;
}

AFUnitManager * AFUnitManager::GetUnitManager(AActor* caller)
{
	AFUnitManager* unitManager = nullptr;
	if (UFGameInstance* gameInstance = Cast<UFGameInstance>(caller->GetGameInstance()))
	{
		unitManager = gameInstance->GetUnitManager();
	}
	return unitManager;
}

void AFUnitManager::UpdateUnits()
{
	for (auto it : Units)
	{
		it.Value = GetLoc(it.Key);
	}
}

void AFUnitManager::AddUnitToList(AActor * caller, AFBaseUnit * unit)
{
	if (AFUnitManager* manager = GetUnitManager(caller))
	{
		if (nullptr != unit)
		{
			manager->Units.Add(unit, manager->GetLoc(unit));
		}
	}
}

void AFUnitManager::RemoveUnitFromList(AActor* caller, AFBaseUnit* unit)
{
	if (AFUnitManager* manager = GetUnitManager(caller))
	{
		if (nullptr != unit)
		{
			manager->Units.Remove(unit);
		}
	}
}

AFUnitManager::loc AFUnitManager::GetLoc(AFBaseUnit * unit)
{
	loc result = loc();
	if (nullptr != unit)
	{
		FVector location = unit->GetActorLocation();
		result.x = location.X >= 0.f ? (int)(location.X / GridDistance) : (int)(location.X / GridDistance) - 1;
		result.y = location.Y >= 0.f ? (int)(location.Y / GridDistance) : (int)(location.Y / GridDistance) - 1;
	}
	return result;
}
