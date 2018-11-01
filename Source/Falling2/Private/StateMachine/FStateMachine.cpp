// Fill out your copyright notice in the Description page of Project Settings.

#include "FStateMachine.h"
#include "FBaseUnit.h"

UFStateMachine::UFStateMachine()
{
}

UClass * UFStateMachine::GetCurrentState()
{
	return (nullptr != CurrentState) ? CurrentState->GetClass() : nullptr;
}

UFBaseState * UFStateMachine::UpdateState(UClass * newState)
{
	if (nullptr == newState)
	{
		return nullptr;
	}
	
	UFBaseState* state = nullptr;

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
		state = NewObject<UFBaseState>(this, newState, MakeUniqueObjectName(this, newState));
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
	{
		return;
	}
	CurrentState->UpdateState(DeltaTime);
}

void UFStateMachine::Release()
{
	for (auto it : States)
	{
		it = nullptr;
	}
	CurrentState = nullptr;
}
