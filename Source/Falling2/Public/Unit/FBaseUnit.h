// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "FBaseClip.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FBaseUnit.generated.h"

UCLASS()
class FALLING2_API AFBaseUnit : public ACharacter
{
	GENERATED_BODY()

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

	void ReleaseStateMachine();

	void Reload(){ }

	UFUNCTION(BlueprintCallable)
		void Equip(class AFBaseWeapon* weapon);

	virtual void ApplyDamage(AFBaseUnit* causer, EBulletElement element, UINT baseValue, UINT piercing);

public:
	UPROPERTY()
		class UFStateMachine* StateMachine = nullptr;
	
	class AFBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Property")
		int Armor = 0;

	
	
};
