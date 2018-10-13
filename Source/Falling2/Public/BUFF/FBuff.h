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
	using BuffFunc = void(*)(class AFBaseUnit*, UFBuff* buff, float, float);

	FName BuffName;
	bool isAlive = true;
public:
	void Initialize(FName name, BuffFunc start, BuffFunc tick, BuffFunc end, UINT8 lifeTime, UINT8 level, AFBaseUnit* owner);
	void BuffStart();
	void BuffTick();
	void BuffEnd();
	void ResetBuff(UINT time);
private:
	BuffFunc StartFunc = nullptr;
	BuffFunc TickFunc = nullptr;
	BuffFunc EndFunc = nullptr;
	UINT8 BuffLife = 0;
	UINT8 BuffLevel = 1;
	class AFBaseUnit* BuffOwner = nullptr;
	
};
