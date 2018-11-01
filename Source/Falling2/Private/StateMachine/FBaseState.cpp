// Fill out your copyright notice in the Description page of Project Settings.

#include "FBaseState.h"
#include "FBaseUnit.h"



void UFBaseState::Initialize(AFBaseUnit* owner)
{
	StateOwner = owner;
}

void UFBaseState::Release()
{
	StateOwner = nullptr;
}
