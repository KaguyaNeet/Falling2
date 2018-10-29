// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Unit/Observer/FUnitObserver.h"
#include "FUnitObserver_Damage.generated.h"

/**
 * 
 */
UCLASS()
class FALLING2_API UFUnitObserver_Damage : public UFUnitObserver
{
	GENERATED_BODY()
	
public:
	void ExecuteEvent(class UFUnitObserverManager* manager, class AFBaseUnit* owner, const struct Damage& damage);
	
	
};
