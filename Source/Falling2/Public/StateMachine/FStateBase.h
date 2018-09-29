// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FStateBase.generated.h"

/**
 * 
 */
UCLASS()
class FALLING2_API UFStateBase : public UObject
{
	GENERATED_BODY()

public:
	class AFBaseUnit* StateOwner = nullptr;
	
public:
	void Initialize(class AFBaseUnit* owner);
	virtual void EnterState(){ }
	virtual void UpdateState(float DeltaTime){ }
	virtual void ExitState(){ }
	
	virtual void Release();
};
