// Fill out your copyright notice in the Description page of Project Settings.

#include "FBaseWeapon.h"
#include "FBaseUnit.h"
#include "FBullet.h"

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
	FireArrow->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
}

void AFBaseWeapon::InitializeWeapon(const FWeaponProperty & weaponProperty)
{
	WeaponProperty = weaponProperty;
	Mesh->SetSkeletalMesh(weaponProperty.WeaponMesh);
	FireArrow->SetRelativeLocation(weaponProperty.FireLocation);
}

void AFBaseWeapon::Tick(float DeltaTime)
{
	if (CurrentCD > 0.f)
	{
		CurrentCD -= DeltaTime;
	}
	else if (EFireMode::EBurstMode == WeaponProperty.FireMode && isFire)
	{
		CheckFire();
	}
	if (CurrentScatteringAngle > 0.f)
	{
		CurrentScatteringAngle -= WeaponProperty.ScatteringAngleReduction * DeltaTime;
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
	AttachToComponent(owner->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("index_01_r"));
	SetActorRelativeLocation(WeaponProperty.AttachLocation);
	SetActorRelativeRotation(WeaponProperty.AttachRotation);
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
	CurrentCD = WeaponProperty.MaxCD;
	//CurrentBulletElement = CurrentClip->BulletElement;
	//CurrentBulletDamage = CurrentClip->BulletDamage;


	TArray<FVector> directions = CalculationDirection();
	SpawnFire(directions);
	return true;
}

TArray<FVector> AFBaseWeapon::CalculationDirection()
{
	FVector direction = FVector(FireArrow->GetForwardVector().X, FireArrow->GetForwardVector().Y, 0.f);
	TArray<FVector> result;
	if (1 == WeaponProperty.ProjectileNum)
	{
		direction = FRotator(0.f, direction.Rotation().Yaw + FMath::FRandRange(-CurrentScatteringAngle, CurrentScatteringAngle), 0.f).Vector();
		result.Add(direction);
		CurrentScatteringAngle = FMath::Clamp(CurrentScatteringAngle + WeaponProperty.ScatteringAngleIncrement, 0.f, WeaponProperty.MaxScatteringAngle);
	}
	else
	{
		FVector tempDirection = FVector::ZeroVector;
		for (int i = 0; i < WeaponProperty.ProjectileNum; ++i)
		{
			tempDirection = FRotator(0.f, direction.Rotation().Yaw + FMath::FRandRange(-WeaponProperty.ScatteringAngle, WeaponProperty.ScatteringAngle), 0.f).Vector();
			result.Add(tempDirection);
		}
	}

	return result;
}

void AFBaseWeapon::SpawnFire(const TArray<FVector>& directions)
{
	UGameplayStatics::SpawnEmitterAttached(WeaponProperty.MuzzleParticle, FireArrow);
	if (((UINT)WeaponProperty.WeaponType & ((UINT)EWeaponType::ERifle | (UINT)EWeaponType::EShotgun | (UINT)EWeaponType::ESniper)) > 0)
	{
		for (int i = 0; i < directions.Num(); ++i)
		{
			SpawnTraceBullet(directions[i]);
		}
	}
	else
	{
		for (int i = 0; i < directions.Num(); ++i)
		{
			SpawnActorBullet(directions[i]);
		}
	}
}

void AFBaseWeapon::SpawnActorBullet(FVector direction)
{
	if (nullptr != WeaponProperty.Bullet)
	{
		UWorld* world = GetWorld();
		AFBullet* bullet = world->SpawnActor<AFBullet>(WeaponProperty.Bullet, FireArrow->GetComponentLocation(), direction.Rotation());
		if (nullptr != bullet)
		{
			bullet->Initialize(ItemOwner, CurrentBulletElement, WeaponProperty.BaseDamageValue + CurrentBulletDamage, WeaponProperty.BulletSpeed, WeaponProperty.FireRange, WeaponProperty.Piercing);
		}
	}
}

void AFBaseWeapon::SpawnTraceBullet(FVector direction)
{
	FVector start = FireArrow->GetComponentLocation();
	FVector end = start + direction * WeaponProperty.FireRange;
	TArray<AActor*> ignoreActor;
	FHitResult hit;
	UWorld* world = GetWorld();
	if (UKismetSystemLibrary::LineTraceSingle(this, start, end, ETraceTypeQuery::TraceTypeQuery3, true, ignoreActor, EDrawDebugTrace::None, hit, true))
	{
		end = hit.Location;

		FTransform hitTrans;
		hitTrans.SetLocation(hit.Location);
		hitTrans.SetRotation(hit.Normal.ToOrientationQuat());
		UGameplayStatics::SpawnEmitterAtLocation(world, WeaponProperty.HitParticle, hitTrans);

		if (AFBaseUnit* unit = Cast<AFBaseUnit>(hit.Actor))
		{
			unit->ApplyDamage(ItemOwner, CurrentBulletElement, WeaponProperty.BaseDamageValue + CurrentBulletDamage, WeaponProperty.Piercing);
		}
	}
	if (auto trace = UGameplayStatics::SpawnEmitterAtLocation(world, WeaponProperty.TraceParticle, FTransform()))
	{
		trace->SetBeamSourcePoint(0, start, 0);
		trace->SetBeamTargetPoint(0, end, 0);
	}
}
