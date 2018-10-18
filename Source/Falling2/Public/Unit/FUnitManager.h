// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FUnitManager.generated.h"

UCLASS()
class FALLING2_API AFUnitManager : public AActor
{
	GENERATED_BODY()

public:
	struct loc
	{
	public:
		loc(int x_, int y_) :x(x_), y(y_){ }
		loc():x(0), y(0){ }
		int x, y;
		
		static bool Adjacent(const loc& loc1, const loc& loc2)
		{
			if (FMath::Abs(loc1.x - loc2.x) <= 1 && FMath::Abs(loc1.y - loc2.y) <= 1)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	};
	
public:	
	// Sets default values for this actor's properties
	AFUnitManager();

	static float GetUnitsDistance(AActor* caller, class AFBaseUnit* unit1, class AFBaseUnit* unit2);
	static void AddUnitToList(AActor* caller, class AFBaseUnit* unit);
	static void RemoveUnitFromList(AActor* caller, class AFBaseUnit* unit);

private:
	static AFUnitManager* GetUnitManager(AActor* caller);
	loc GetLoc(class AFBaseUnit* unit);

	void UpdateUnits();

private:
	TMap<class AFBaseUnit*, loc> Units;

public:
	UPROPERTY(EditAnywhere, Category = "UnitManagerProperty")
		float GridDistance = 1000.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
