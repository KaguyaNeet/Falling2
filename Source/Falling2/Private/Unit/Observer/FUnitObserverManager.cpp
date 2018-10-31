// Fill out your copyright notice in the Description page of Project Settings.

#include "FUnitObserverManager.h"
#include "FBaseUnit.h"

#include "FUnitObserver_UnderAttack.h"

// Initialize the ObserverList
TMap<FName, EUnitObserverType> UFUnitObserverManager::ObserverList = TMap<FName, EUnitObserverType>();

UFUnitObserverManager::UFUnitObserverManager()
{
	if (!isInitialize)
	{
		isInitialize = true;
		UFUnitObserver_UnderAttack::Registered();
	}
	
}

void UFUnitObserverManager::CreateObserver(UFUnitObserverManager * manager, const FName& name)
{
	if (nullptr == manager)
	{
		UE_LOG(LogTemp, Warning, TEXT("Observer manager is null!"));
		return;
	}

	if (EUnitObserverType* type = ObserverList.Find(name))
	{
		switch (*type)
		{
			case EUnitObserverType::EDamage: 
			{
				UFUnitObserver_UnderAttack* observer = NewObject<UFUnitObserver_UnderAttack>();
				observer->Initialize(name);
				manager->Observers.Add(observer);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Observer manager not found the observer of this name, failed to create!"));
	}
}

Damage UFUnitObserverManager::BroadcastDamageEvent(UFUnitObserverManager* manager, AFBaseUnit* owner, const Damage& damage)
{
	Damage result = damage;
	for (auto it : manager->Observers)
	{
		if (EUnitObserverType::EDamage == it->ObserverType)
		{
			if (UFUnitObserver_UnderAttack* ob = Cast<UFUnitObserver_UnderAttack>(it))
			{
				ob->ExecuteEvent(owner, result);
			}
		}
	}
	return result;
}

void UFUnitObserverManager::RegisteredObserver(const FName & name, EUnitObserverType observerType)
{
	ObserverList.Add(name, observerType);
}

