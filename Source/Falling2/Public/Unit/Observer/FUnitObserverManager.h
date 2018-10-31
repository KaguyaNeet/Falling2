// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "FUnitObserver.h"

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

	// Already registed observer
	static TMap<FName, EUnitObserverType> ObserverList;

	// Lazy initialize trigger
	bool isInitialize = false;

public:
	// Constructor
	UFUnitObserverManager();

	// Create Observer
	static void CreateObserver(UFUnitObserverManager* manager, const FName& name);

	// Broadcast the damage event
	static struct Damage BroadcastDamageEvent(UFUnitObserverManager* manager, class AFBaseUnit* owner, const struct Damage& damage);

	// Registered the observer to the observer list
	static void RegisteredObserver(const FName& name, EUnitObserverType observerType);

	
	
	
};
