// Fill out your copyright notice in the Description page of Project Settings.

#include "FBuff.h"
#include "FBaseUnit.h"

void UFBuff::Initialize(FName name, BuffFunc start, BuffFunc tick, BuffFunc end, UINT8 lifeTime, UINT8 level, AFBaseUnit* owner)
{
	BuffName = name;
	StartFunc = start;
	TickFunc = tick;
	EndFunc = end;
	BuffLife = lifeTime;
	BuffLevel = level;
	BuffOwner = owner;
}

void UFBuff::BuffStart()
{
	if (nullptr != BuffOwner)
	{
		StartFunc(BuffOwner, this, BuffLevel, BuffLife);
	}
}

void UFBuff::BuffTick()
{
	if (nullptr != BuffOwner && isAlive)
	{
		BuffLife--;
		TickFunc(BuffOwner, this, BuffLevel, BuffLife);
		if (BuffLife <= 0)
		{
			BuffEnd();
		}
	}
}

void UFBuff::BuffEnd()
{
	if (nullptr != BuffOwner)
	{
		EndFunc(BuffOwner, this, BuffLevel, BuffLife);
		BuffOwner->RemoveBuff(this);
	}
}

void UFBuff::ResetBuff(UINT time)
{
	BuffLife = time;
}
