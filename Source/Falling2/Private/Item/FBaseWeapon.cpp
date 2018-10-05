// Fill out your copyright notice in the Description page of Project Settings.

#include "FBaseWeapon.h"
#include "FBaseClip.h"
#include "FBaseUnit.h"

#include "Classes/Components/SkeletalMeshComponent.h"
#include "Classes/Components/ArrowComponent.h"
#include "Classes/Components/SphereComponent.h"
#include "Classes/Particles/ParticleSystemComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

AFBaseWeapon::AFBaseWeapon()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->AttachTo(Trigger);

	FireArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("FireArrow"));
	FireArrow->AttachTo(Mesh);
}

void AFBaseWeapon::Tick(float DeltaTime)
{
	if (CurrentCD > 0.f)
	{
		CurrentCD -= DeltaTime;
	}
	else if (EFireMode::EBurstMode == FireMode && isFire)
	{
		CheckFire();
	}
}

void AFBaseWeapon::Invisible(bool newState)
{
	Mesh->SetVisibility(!newState);
}

void AFBaseWeapon::EquipWeapon(class AFBaseUnit* owner)
{
	ItemOwner = owner;
	Invisible(false);
	SetActorRelativeLocation(WeaponLocation);
	SetActorRelativeRotation(WeaponRotator);
}

void AFBaseWeapon::Reload(class AFBaseClip* clip)
{
	if (nullptr != CurrentClip)
	{
		CurrentClip->Destroy();
	}
	CurrentClip = clip;
}

void AFBaseWeapon::StartFire()
{
	isFire = true;
	if (CurrentCD <= 0.f)
	{
		CheckFire();
	}
}

void AFBaseWeapon::EndFire()
{
	isFire = false;
}

void AFBaseWeapon::RequestReload()
{
	if (nullptr != ItemOwner)
	{
		ItemOwner->Reload();
	}
}

void AFBaseWeapon::Fire()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleParticle, FireArrow);

	FVector start = FireArrow->GetComponentLocation();
	FVector end = start + FireArrow->GetForwardVector() * FireRange;
	TArray<AActor*> ignoreActor;
	FHitResult hit;
	UWorld* world = GetWorld();
	if (UKismetSystemLibrary::LineTraceSingle(this, start, end, ETraceTypeQuery::TraceTypeQuery1, true, ignoreActor, EDrawDebugTrace::None, hit, true))
	{
		end = hit.Location;

		FTransform hitTrans;
		hitTrans.SetLocation(hit.Location);
		hitTrans.SetRotation(hit.Normal.ToOrientationQuat());
		UGameplayStatics::SpawnEmitterAtLocation(world, HitParticle, hitTrans);

		if (AFBaseUnit* unit = Cast<AFBaseUnit>(hit.Actor))
		{
			unit->ApplyDamage(ItemOwner, DamageValue);
		}
	}
	auto trace = UGameplayStatics::SpawnEmitterAtLocation(world, TraceParticle, FTransform());
	trace->SetBeamSourcePoint(0, start, 0);
	trace->SetBeamTargetPoint(0, end, 0);
}

bool AFBaseWeapon::CheckFire()
{
	/*if (nullptr == CurrentClip)
	{
		RequestReload();
		return false;
	}
	else if (CurrentClip->CurrentBulletCount <= 0)
	{
		RequestReload();
		return false;
	}
	--CurrentClip->CurrentBulletCount;*/
	CurrentCD = MaxCD;
	//Test use.
	Fire();

	TArray<FRotator> directions = CalculationDirection();
	SpawnFire(directions);
	return true;
}

TArray<FRotator> AFBaseWeapon::CalculationDirection()
{
	return TArray<FRotator>();
}

void AFBaseWeapon::SpawnFire(const TArray<FRotator>& directions)
{

}
