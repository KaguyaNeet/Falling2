// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FStateBase.h"
#include "FSPlayerBaseMove.h"
#include "FSRolling.h"

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
	UPROPERTY()
		TArray<UFStateBase*> States;
	UPROPERTY()
		UFStateBase* CurrentState = nullptr;

public:
	UFStateMachine();
	UClass* GetCurrentState();
	bool CheckState(UClass* newState);

	UFStateBase* ChangeState(UClass* newState);
	void UpdateStateMachine(float DeltaTime);

	void Release();


	
	
};
