// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "FBaseClip.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FBaseUnit.generated.h"

UENUM(BlueprintType)
enum class EUnitCamp : uint8
{
	EFriendly UMETA(DisplayName = "Friendly"),
	EHostility UMETA(DisplayName = "Hostility"),
	ENeutral UMETA(DisplayName = "Neutral"),
};

UCLASS()
class FALLING2_API AFBaseUnit : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFBaseUnit();

	void RemoveBuff(class UFBuff* buff);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ReleaseStateMachine();

	virtual void Reload(){ }

	UFUNCTION(BlueprintCallable)
		void Equip(class AFBaseWeapon* weapon);

	UFUNCTION(BlueprintImplementableEvent)
		void FrozenMaterial(bool choose);

	virtual void ApplyDamage(AFBaseUnit* causer, UINT baseValue);

	void AddBuff(class UFBuff* buff);

	UFBuff* FindBuff(class UFBuff* buff);

public:
	UPROPERTY()
		class UFStateMachine* StateMachine = nullptr;
	
	class AFBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
		int Armor = 0;

	bool AllowBaseAnimUpdate = true;

	EUnitCamp UnitCamp = EUnitCamp::EFriendly;

private:
	UPROPERTY()
		TArray<class UFBuff*> Buffs;

	float BuffTickCounter = 0.f;

private:
	void TickBuff();
};
