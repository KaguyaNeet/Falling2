// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine/DataTable.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FBaseUnit.generated.h"

UENUM(BlueprintType)
enum class EElemental : uint8
{
	ENormal UMETA(DisplayName = "Normal"),
	EFire UMETA(DisplayName = "Fire"),
	EIce UMETA(DisplayName = "Ice"),
	EThunder UMETA(DisplayName = "Thunder"),
};

struct Damage
{
	// The causer of this damage
	class AFBaseUnit* Causer = nullptr;

	// The value of this damage
	UINT DamageValue = 0;

	// The piercing of this damage
	UINT Piercing = 0;

	// The elemental of this damage
	EElemental Elemental = EElemental::ENormal;

	// The level of this damage's elemental
	UINT ElementLevel = 1;
};


UENUM(BlueprintType)
enum class EUnitCamp : uint8
{
	EPlayer UMETA(DisplayName = "Player"),
	EEnemy UMETA(DisplayName = "Enemy"),
};

USTRUCT()
struct FUnitAttribute : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// The max life value of this unit
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MaxLifeValue = 100;

	// The current life value of this unit
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CurrentLifeValue = 100;

	// The armor of this unit
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Armor = 0;

	// The elemental resistance of this unit
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int ElementalResistance = 0;

	// The moving speed of this unit
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MovingSpeed = 300.f;
};

UCLASS()
class FALLING2_API AFBaseUnit : public ACharacter
{
	GENERATED_BODY()

public:
	// The unit attribute of this unit
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitProperty")
		FUnitAttribute UnitAttribute;

	// The camp of this unit
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitProperty")
		EUnitCamp UnitCamp = EUnitCamp::EPlayer;

	// The buff owned by this unit
	UPROPERTY()
		TArray<class UFBuff*> Buffs;

	// The observer manager of this unit
	UPROPERTY()
		class UFUnitObserverManager* UnitObserverManager = nullptr;



public:
	// Sets default values for this character's properties
	AFBaseUnit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Cause damage to this unit
	virtual void ApplyDamage(const Damage& damage);

private:
	// Tick buffs of this unit
	void TickBuff(float delta);

	
private:
	// The buff tick timer
	float BuffTickTimer = 0.f;
	
};
