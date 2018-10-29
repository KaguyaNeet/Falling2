// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FUnitObserverManager.generated.h"

/**
 * 
 */
UCLASS()
class FALLING2_API UFUnitObserverManager : public UObject
{
	GENERATED_BODY()
	
private:
	// Observers that this unit owned
	TArray<class UFUnitObserver*> Observers;

public:
	// Broadcast the damage event
	static void BroadcastDamageEvent(UFUnitObserverManager* manager, class AFBaseUnit* owner, const struct Damage& damage);
	
	
};
