// Fill out your copyright notice in the Description page of Project Settings.

#include "FBuffManager.h"
#include "FGameInstance.h"
#include "FBuff.h"
#include "FBaseUnit.h"
#include "FPlayer.h"

#include "Classes/GameFramework/CharacterMovementComponent.h"
#include "Classes/Components/SkeletalMeshComponent.h"
#include "Public/UObject/ConstructorHelpers.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Classes/Particles/ParticleSystemComponent.h"
#include "Classes/Components/CapsuleComponent.h"

UFBuffManager::UFBuffManager()
{
	BuffFunc start = nullptr;
	BuffFunc tick = nullptr;
	BuffFunc end = nullptr;
	Register_BUFF(Incendiary);
	Register_BUFF(Frozen);

	ConstructorHelpers::FObjectFinder<UParticleSystem> FrozenP(TEXT("ParticleSystem'/Game/Particles/P_ICe.P_ICe'"));
	if (FrozenP.Succeeded())
	{
		FrozenParticle = FrozenP.Object;
	}
}

UFBuffManager* UFBuffManager::GetBuffManager(AActor* caller)
{
	UFBuffManager* manager = nullptr;
	if (UFGameInstance* gameInstance = Cast<UFGameInstance>(caller->GetGameInstance()))
	{
		manager = gameInstance->GetBuffManager();
	}
	return manager;
}

UFBuff* UFBuffManager::CreateBuff(AActor* caller, const FName& name, UINT8 lifeTime, UINT8 level, AFBaseUnit* target)
{
	UFBuff* buff = nullptr;
	if (UFBuffManager* manager = GetBuffManager(caller))
	{
		if (BuffFuncs* funcs = manager->Funcs.Find(name))
		{
			buff = NewObject<UFBuff>();
			buff->Initialize(name, funcs->StartFunc, funcs->TickFunc, funcs->EndFunc, lifeTime, level, target);
			if (nullptr != target)
			{
				target->AddBuff(buff);
			}
		}
	}
	
	return buff;
}

Implement_BUFF_Start(Incendiary)
{

}
Implement_BUFF_Tick(Incendiary)
{

}
Implement_BUFF_End(Incendiary)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("BuffEndIncendiary"));
}

Implement_BUFF_Start(Frozen)
{
	if (UFBuffManager* manager = UFBuffManager::GetBuffManager(owner))
	{
		FTransform transform = owner->GetActorTransform();
		transform.SetLocation(FVector(owner->GetActorLocation().X, owner->GetActorLocation().Y, owner->GetActorLocation().Z - owner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
		auto particle = UGameplayStatics::SpawnEmitterAtLocation(owner->GetWorld(), manager->FrozenParticle, transform);
		particle->SetFloatParameter(FName("LifeTime"), value2);
		particle->SetFloatParameter(FName("LifeTime2"), value2);
		
		if (UFBuff* findbuff = owner->FindBuff(buff))
		{
			findbuff->ResetBuff(value2);
			owner->RemoveBuff(buff);
			buff->isAlive = false;
			return;
		}
		owner->FrozenMaterial(true);
	}
	owner->GetCharacterMovement()->SetActive(false);
	owner->GetMesh()->SetActive(false);
	owner->AllowBaseAnimUpdate = false;
}
Implement_BUFF_Tick(Frozen)
{

}
Implement_BUFF_End(Frozen)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("BuffEndFrozen"));
	owner->GetCharacterMovement()->SetActive(true);
	owner->GetMesh()->SetActive(true);
	owner->AllowBaseAnimUpdate = true;
	owner->FrozenMaterial(false);
}