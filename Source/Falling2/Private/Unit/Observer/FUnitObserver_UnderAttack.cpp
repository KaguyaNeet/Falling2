// Fill out your copyright notice in the Description page of Project Settings.

#include "FUnitObserver_UnderAttack.h"
#include "FUnitObserverManager.h"
#include "FBaseUnit.h"

#define Register_Damage_Observer(name) \
	UFUnitObserverManager::RegisteredObserver(FName(#name), EUnitObserverType::EDamage); \
	UFUnitObserver_UnderAttack::Funcs.Add(FName(#name), &DamageFuncs::name); \

#define Implement_Damage_Func(name) \
	void name (AFBaseUnit * owner, Damage & damage) \


TMap<FName, UFUnitObserver_UnderAttack::DamageFunc> UFUnitObserver_UnderAttack::Funcs = TMap<FName, DamageFunc>();

void UFUnitObserver_UnderAttack::Initialize(const FName & name)
{
	if (DamageFunc* func = Funcs.Find(name))
	{
		Func = *func;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("It's a not damage observer name, failed to create observer!"));
	}
}

void UFUnitObserver_UnderAttack::ExecuteEvent(AFBaseUnit* owner, Damage& damage)
{
	if (nullptr != Func)
	{
		Func(owner, damage);
	}
}

namespace DamageFuncs
{
	Implement_Damage_Func(DamageTest)
	{

	}
}

void UFUnitObserver_UnderAttack::Registered()
{
	Register_Damage_Observer(DamageTest);
}





