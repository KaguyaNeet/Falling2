// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FUnitObserver.generated.h"

enum class EUnitObserverType : uint8
{
	EDamage,
};

/**
 * 
 */
UCLASS()
class FALLING2_API UFUnitObserver : public UObject
{
	GENERATED_BODY()
	
public:
	//Observer type of this Observer
	EUnitObserverType ObserverType = EUnitObserverType::EDamage;
	
	
};
