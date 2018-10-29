// Fill out your copyright notice in the Description page of Project Settings.

#include "FBuffManager.h"
#include "FBuff.h"
#include "FBaseUnit.h"
#include "FGameInstance.h"

#include "GameFramework/Actor.h"

// Sets default values
AFBuffManager::AFBuffManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFBuffManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFBuffManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UFBuff * AFBuffManager::CreateBuff(AActor * caller, const FName & name, AFBaseUnit * owner, AFBaseUnit * adder, UINT8 level, UINT8 lifetime, UINT8 buffType, bool canOverlap)
{
	UFBuff* buff = nullptr;
	if (AFBuffManager* manager = GetBuffManager(caller))
	{
		if (BuffFuncs* funcs = manager->Funcs.Find(name))
		{
			buff = NewObject<UFBuff>();
			BuffAttribute attribute;
			attribute.adder = adder;
			attribute.BuffType = buffType;
			attribute.CanOverlap = canOverlap;
			attribute.DisableFunc = funcs->DisableFunc;
			attribute.EnableFunc = funcs->EnableFunc;
			attribute.TickFunc = funcs->TickFunc;
			attribute.Level = level;
			attribute.LifeTime = lifetime;
			attribute.Name = name;
			attribute.owner = owner;
			buff->Initialize(attribute);
			if (nullptr != owner)
			{
				//owner->AddBuff(attribute);
			}
		}

	}
	return nullptr;
}

AFBuffManager * AFBuffManager::GetBuffManager(AActor * caller)
{
	AFBuffManager* manager = nullptr;
	if (UFGameInstance* instance = Cast<UFGameInstance>(caller->GetGameInstance()))
	{
		manager = instance->GetBuffManager();
	}
	return manager;
}

