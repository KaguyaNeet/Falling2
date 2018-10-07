// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FBuff.generated.h"

/**
 * 
 */
UCLASS()
class FALLING2_API UFBuff : public UObject
{
	GENERATED_BODY()
	
public:
	using BuffFunc = void(*)(class AFBaseUnit*, float, float);


public:
	void Initialize(BuffFunc start, BuffFunc tick, BuffFunc end);
	void BuffStart();
	void BuffTick();
	void BuffEnd();

private:
	BuffFunc StartFunc = nullptr;
	BuffFunc TickFunc = nullptr;
	BuffFunc EndFunc = nullptr;
	
	
};
