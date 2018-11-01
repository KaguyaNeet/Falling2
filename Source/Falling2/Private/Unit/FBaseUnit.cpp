// Fill out your copyright notice in the Description page of Project Settings.

#include "FBaseUnit.h"
#include "FBuff.h"
#include "FMainGameMode.h"
#include "FUnitObserverManager.h"
#include "FStateMachine.h"


// Sets default values
AFBaseUnit::AFBaseUnit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFBaseUnit::BeginPlay()
{
	Super::BeginPlay();
	
	//Create unit observer manager
	UnitObserverManager = NewObject<UFUnitObserverManager>(this, UFUnitObserverManager::StaticClass(), MakeUniqueObjectName(this, UFUnitObserverManager::StaticClass()));
}

// Called every frame
void AFBaseUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TickBuff(DeltaTime);
}

// Called to bind functionality to input
void AFBaseUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AFBaseUnit::ApplyDamage(const Damage & damage)
{
	UFUnitObserverManager::BroadcastDamageEvent(UnitObserverManager, this, damage);


}

void AFBaseUnit::AddBuff(UFBuff * buff)
{
	if (nullptr != buff)
	{
		Buffs.Add(buff);
		buff->StartBuff();
	}
}

bool AFBaseUnit::RemoveBuffByType(UINT8 buffType)
{
	bool result = false;

	for (auto it : Buffs)
	{
		if ((it->GetBuffType() & buffType) > 0)
		{
			it->EndBuff();
			it = nullptr;
			result = true;
		}
	}
	Buffs.Remove(nullptr);

	return result;
}

void AFBaseUnit::TickBuff(float delta)
{
	BuffTickTimer += delta;
	if (BuffTickTimer >= BUFF_TICK_INTERVAL)
	{
		BuffTickTimer = 0.f;
		for (auto it : Buffs)
		{
			it->TickBuff();
		}
	}
}

