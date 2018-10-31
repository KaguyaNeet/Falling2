// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Unit/Observer/FUnitObserver.h"
#include "FUnitObserver_UnderAttack.generated.h"



/**
 * 
 */
UCLASS()
class FALLING2_API UFUnitObserver_UnderAttack : public UFUnitObserver
{
	GENERATED_BODY()
	
		
public:
	using DamageFunc = void(*)(class AFBaseUnit* owner, struct Damage& damage);
		
private:
	// Function of this observer
	DamageFunc Func = nullptr;
		
public:
	// Functions of damage observer
	static TMap<FName, DamageFunc> Funcs;
			
public:
	// Initializer
	void Initialize(const FName& name);
		
	// Execute this observer's function
	void ExecuteEvent(class AFBaseUnit* owner, struct Damage& damage);
			
	// Registered all the damage function
	static void Registered();
};

