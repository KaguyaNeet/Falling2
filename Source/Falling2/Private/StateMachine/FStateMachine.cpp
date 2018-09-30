// Fill out your copyright notice in the Description page of Project Settings.

#include "FStateMachine.h"
#include "FStateBase.h"
#include "FBaseUnit.h"


UFStateMachine::UFStateMachine()
{
	ChangeState(UFStateBase::StaticClass());
}

UClass * UFStateMachine::GetCurrentState()
{
	return (nullptr != CurrentState) ? CurrentState->GetClass() : nullptr;
}

bool UFStateMachine::CheckState(UClass * newState)
{
	if (nullptr == CurrentState)
	{
		return false;
	}
	UClass* currentClass = CurrentState->GetClass();
	bool result =  currentClass == newState ? true : false;
	return result;
}

UFStateBase* UFStateMachine::ChangeState(UClass* newState)
{
	if (nullptr == newState)
		return CurrentState;
	UFStateBase* state = nullptr;
	for (auto it : States)
	{
		if (it->GetClass() == newState)
		{
			state = it;
			break;
		}
	}
	if (nullptr == state)
	{
		state = NewObject<UFStateBase>(this, newState, newState->GetFName());
		AFBaseUnit* unit = Cast<AFBaseUnit>(GetOuter());
		state->Initialize(unit);
		States.Add(state);
	}
	if (nullptr != CurrentState)
	{
		CurrentState->ExitState();
	}
	state->EnterState();
	CurrentState = state;
	return CurrentState;
}

void UFStateMachine::UpdateStateMachine(float DeltaTime)
{
	if (nullptr == CurrentState)
		return;
	CurrentState->UpdateState(DeltaTime);
}

void UFStateMachine::Release()
{
	for (UINT8 i = 0; i < States.Num(); ++i)
	{
		States[i] = nullptr;
	}
	CurrentState = nullptr;
}

