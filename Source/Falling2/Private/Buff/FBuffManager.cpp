// Fill out your copyright notice in the Description page of Project Settings.

#include "FBuffManager.h"
#include "FBuff.h"
#include "FBaseUnit.h"
#include "FGameInstance.h"

#include "GameFramework/Actor.h"
#include "Public/UObject/ConstructorHelpers.h"

// Sets default values
AFBuffManager::AFBuffManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BuffFunc enable = nullptr;
	BuffFunc tick = nullptr;
	BuffFunc disable = nullptr;
	Register_BUFF(Incendiary);
	Register_BUFF(Frozen);

	//ConstructorHelpers::FObjectFinder<UParticleSystem> FrozenP(TEXT("ParticleSystem'/Game/Particles/P_ICe.P_ICe'"));
	//if (FrozenP.Succeeded())
	//{
	//	FrozenParticle = FrozenP.Object;
	//}

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
				owner->AddBuff(buff);
			}
		}

	}
	return buff;
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

// Implement the Incendiary buff
Implement_BUFF_Enable(Incendiary)
{

}
Implement_BUFF_Tick(Incendiary)
{

}
Implement_BUFF_Disable(Incendiary)
{
	
}

// Implement the Frozen buff
Implement_BUFF_Enable(Frozen)
{
	if (AFBuffManager* manager = AFBuffManager::GetBuffManager(owner))
	{
		//FTransform transform = owner->GetActorTransform();
		//transform.SetLocation(FVector(owner->GetActorLocation().X, owner->GetActorLocation().Y, owner->GetActorLocation().Z - owner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
		//auto particle = UGameplayStatics::SpawnEmitterAtLocation(owner->GetWorld(), manager->FrozenParticle, transform);
		//particle->SetFloatParameter(FName("LifeTime"), value2);
		//particle->SetFloatParameter(FName("LifeTime2"), value2);

		//if (UFBuff* findbuff = owner->FindBuff(buff))
		//{
		//	findbuff->ResetBuff(value2);
		//	owner->RemoveBuff(buff);
		//	buff->isAlive = false;
		//	return;
		//}
		//owner->FrozenMaterial(true);
	}
	//owner->GetCharacterMovement()->SetActive(false);
	//owner->GetMesh()->SetActive(false);
	//owner->AllowBaseAnimUpdate = false;
}
Implement_BUFF_Tick(Frozen)
{

}
Implement_BUFF_Disable(Frozen)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("BuffEndFrozen"));
	//owner->GetCharacterMovement()->SetActive(true);
	//owner->GetMesh()->SetActive(true);
	//owner->AllowBaseAnimUpdate = true;
	//owner->FrozenMaterial(false);
}