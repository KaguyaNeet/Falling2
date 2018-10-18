// Fill out your copyright notice in the Description page of Project Settings.

#include "FBaseUnit.h"
#include "FStateMachine.h"
#include "FBaseWeapon.h"
#include "FBuff.h"

#include "Classes/Components/SkeletalMeshComponent.h"


// Sets default values
AFBaseUnit::AFBaseUnit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	
}

void AFBaseUnit::RemoveBuff(UFBuff * buff)
{
	Buffs.Remove(buff);
}

// Called when the game starts or when spawned
void AFBaseUnit::BeginPlay()
{
	Super::BeginPlay();

	FName name = MakeUniqueObjectName(this, UFStateMachine::StaticClass());
	StateMachine = NewObject<UFStateMachine>(this, UFStateMachine::StaticClass(), name);
}

// Called every frame
void AFBaseUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	StateMachine->UpdateStateMachine(DeltaTime);

	BuffTickCounter += DeltaTime;
	if (BuffTickCounter >= 1.f)
	{
		BuffTickCounter = 0.f;
		TickBuff();
	}
}

// Called to bind functionality to input
void AFBaseUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AFBaseUnit::ReleaseStateMachine()
{
	StateMachine->Release();
	StateMachine = nullptr;
}

void AFBaseUnit::ApplyDamage(AFBaseUnit* causer, UINT baseValue)
{

}

void AFBaseUnit::AddBuff(UFBuff * buff)
{
	if (nullptr != buff)
	{
		Buffs.Add(buff);
		buff->BuffStart();
	}
}

UFBuff * AFBaseUnit::FindBuff(UFBuff* buff)
{
	UFBuff* result = nullptr;
	if (nullptr != buff)
	{
		for (int i = 0; i < Buffs.Num(); ++i)
		{
			if (buff->BuffName == Buffs[i]->BuffName)
				if (buff != Buffs[i])
				{
					result = Buffs[i];
					break;
				}
		}
	}
	
	return result;
}

void AFBaseUnit::TickBuff()
{
	for (int i = 0; i < Buffs.Num(); ++i)
	{
		if (nullptr != Buffs[i])
		{
			Buffs[i]->BuffTick();
		}
	}
}

void AFBaseUnit::Equip(AFBaseWeapon* weapon)
{
	if (nullptr != weapon)
	{
		CurrentWeapon = weapon;
		FAttachmentTransformRules rules(EAttachmentRule::KeepRelative, false);
		weapon->AttachToComponent(GetMesh(), rules, FName("b_RightHandIndex1"));
		weapon->EquipWeapon(this);
	}
}
