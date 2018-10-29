// Fill out your copyright notice in the Description page of Project Settings.

#include "FBuff.h"
#include "FBaseUnit.h"


void UFBuff::TickBuff()
{
	if (nullptr != Attribute.TickFunc && IsActive)
	{
		Attribute.LifeTime--;
		Attribute.TickFunc(Attribute.owner, Attribute.adder, this, Attribute.LifeTime, Attribute.Level);
		if (Attribute.LifeTime <= 0)
		{
			EndBuff();
		}
	}
}

void UFBuff::StartBuff()
{
	EnableBuff();
}

void UFBuff::EnableBuff()
{
	if (nullptr != Attribute.EnableFunc)
	{
		Attribute.EnableFunc(Attribute.owner, Attribute.adder, this, Attribute.LifeTime, Attribute.Level);
	}
}

void UFBuff::DisableBuff()
{
	if (nullptr != Attribute.DisableFunc)
	{
		Attribute.DisableFunc(Attribute.owner, Attribute.adder, this, Attribute.LifeTime, Attribute.Level);
	}
}

void UFBuff::EndBuff()
{
	DisableBuff();
}

void UFBuff::Initialize(const BuffAttribute & attribute)
{
	Attribute = attribute;
}

void UFBuff::ResetBuff(UINT time)
{
	if (!Attribute.CanOverlap)
	{
		Attribute.LifeTime = time;
	}
}

