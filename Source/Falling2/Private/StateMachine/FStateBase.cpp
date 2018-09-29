// Fill out your copyright notice in the Description page of Project Settings.

#include "FStateBase.h"
#include "FBaseUnit.h"


void UFStateBase::Initialize(AFBaseUnit* owner)
{
	StateOwner = owner;
}
