// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FStateBase.h"
#include "FSPlayerBaseMove.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FStateMachine.generated.h"

/**
 * 
 */
UCLASS()
class FALLING2_API UFStateMachine : public UObject
{
	GENERATED_BODY()
	
public:
	TMap<UClass*, class UFStateBase*> States;
	UFStateBase* CurrentState = nullptr;

public:
	UFStateMachine();
	UClass* GetCurrentState();
	bool CheckState(UClass* newState);

	void ChangeState(UClass* newState);
	void UpdateStateMachine(float DeltaTime);


	
	
};
