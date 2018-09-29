// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateMachine/FStateBase.h"
#include "FSPlayerBaseMove.generated.h"

/**
 * 
 */
UCLASS()
class FALLING2_API UFSPlayerBaseMove : public UFStateBase
{
	GENERATED_BODY()
	
public:
	class AFPlayer* OwnerPlayer;

public:
	virtual void EnterState() override;
	virtual void UpdateState(float DeltaTime) override;
	virtual void ExitState() override;
	
	
};
