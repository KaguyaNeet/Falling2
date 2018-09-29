// Fill out your copyright notice in the Description page of Project Settings.

#include "FStateMachine.h"
#include "FStateBase.h"


UFStateMachine::UFStateMachine()
{
	ChangeState(UFStateBase::StaticClass());
}

UClass * UFStateMachine::GetCurrentState()
{
	return CurrentState->StaticClass();
}

bool UFStateMachine::CheckState(UClass * newState)
{
	if (nullptr == CurrentState)
	{
		return false;
	}
	return CurrentState->StaticClass() == newState ? true : false;
}

void UFStateMachine::ChangeState(UClass* newState)
{
	UFStateBase* state = *States.Find(newState);
	if (nullptr == state)
	{
		state = NewObject<UFStateBase>(this, newState);
		States.Add(newState) = state;
	}
	if (nullptr != CurrentState)
	{
		CurrentState->ExitState();
	}
	state->EnterState();
	CurrentState = state;
}

void UFStateMachine::UpdateStateMachine(float DeltaTime)
{
	CurrentState->UpdateState(DeltaTime);
}

