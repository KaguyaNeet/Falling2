// Fill out your copyright notice in the Description page of Project Settings.

#include "FUnitObserverManager.h"
#include "FBaseUnit.h"
#include "FUnitObserver.h"
#include "FUnitObserver_Damage.h"

void UFUnitObserverManager::BroadcastDamageEvent(UFUnitObserverManager* manager, AFBaseUnit* owner, const Damage& damage)
{
	for (auto it : manager->Observers)
	{
		if (EUnitObserverType::EDamage == it->ObserverType)
		{
			if (UFUnitObserver_Damage* ob = Cast<UFUnitObserver_Damage>(it))
			{
				ob->ExecuteEvent(manager, owner, damage);
			}
		}
	}
}

