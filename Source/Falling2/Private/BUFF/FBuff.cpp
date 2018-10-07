// Fill out your copyright notice in the Description page of Project Settings.

#include "FBuff.h"
#include "FBaseUnit.h"

void UFBuff::Initialize(BuffFunc start, BuffFunc tick, BuffFunc end)
{
	StartFunc = start;
	TickFunc = tick;
	EndFunc = end;
}

void UFBuff::BuffStart()
{
}

void UFBuff::BuffTick()
{
}

void UFBuff::BuffEnd()
{
}
