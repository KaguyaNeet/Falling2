// Fill out your copyright notice in the Description page of Project Settings.

#include "FBaseWeapon.h"
#include "FBaseUnit.h"
#include "FBullet.h"
#include "FBuffManager.h"
#include "FBuff.h"

#include "Classes/Components/SkeletalMeshComponent.h"
#include "Classes/Components/ArrowComponent.h"
#include "Classes/Components/SphereComponent.h"
#include "Classes/Particles/ParticleSystemComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"

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
	CurrentClipProperty.WeaponType = weaponProperty.WeaponType;
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

void AFBaseWeapon::Reload(const FClipListBP& clip)
{
	CurrentClipProperty = clip;
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

bool AFBaseWeapon::CheckFire()
{
	if (CurrentClipProperty.CurrentBulletCount <= 0)
	{
		if (nullptr != ItemOwner)
		{
			ItemOwner->Reload();
		}
		return false;
	}
	--CurrentClipProperty.CurrentBulletCount;
	CurrentCD = WeaponProperty.MaxCD;

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
			bullet->Initialize(ItemOwner, WeaponProperty.WeaponType, CurrentClipProperty.BulletElement, (UINT)ItemProperty.ItemQuality, WeaponProperty.BaseDamageValue + CurrentClipProperty.BulletDamage, WeaponProperty.BulletSpeed, WeaponProperty.FireRange, WeaponProperty.Piercing);
		}
	}
}

void AFBaseWeapon::SpawnTraceBullet(FVector direction)
{
	FVector start = FireArrow->GetComponentLocation();
	FVector end = start + direction * WeaponProperty.FireRange;
	TArray<AActor*> ignoreActor;
	FHitResult hit;
	TArray<FHitResult> hits;
	UWorld* world = GetWorld();
	TArray<TEnumAsByte<EObjectTypeQuery>> types;
	//WorldStatic
	types.Add(EObjectTypeQuery::ObjectTypeQuery1);
	//Pawn
	types.Add(EObjectTypeQuery::ObjectTypeQuery3);
	if (UKismetSystemLibrary::LineTraceMultiForObjects(this, start, end, types, true, ignoreActor, EDrawDebugTrace::None, hits, true))
	{
		FTransform hitTrans;
		int currentPiercing = WeaponProperty.Piercing;
		const uint8 hitnum = hits.Num();
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, UKismetStringLibrary::Conv_IntToString(hitnum));
		for (int i = 0; i < hits.Num(); ++i)
		{
			hitTrans.SetLocation(hits[i].Location);
			hitTrans.SetRotation(hits[i].Normal.ToOrientationQuat());
			UGameplayStatics::SpawnEmitterAtLocation(world, WeaponProperty.HitParticle, hitTrans);
			if (AFBaseUnit* unit = Cast<AFBaseUnit>(hits[i].Actor))
			{
				int currentArmor = unit->Armor - currentPiercing;
				currentPiercing -= unit->Armor;
				UINT trueDamage = WeaponProperty.BaseDamageValue + CurrentClipProperty.BulletDamage;
				if (currentArmor > 0)
				{
					trueDamage = trueDamage - (trueDamage * (currentArmor / 10));
				}
				unit->ApplyDamage(ItemOwner, trueDamage);
				switch (CurrentClipProperty.BulletElement)
				{
					case EBulletElement::EFrozen: 
					{
						UFBuffManager::CreateBuff(this, FName("Frozen"), (int)ItemProperty.ItemQuality * 3.f, (int)ItemProperty.ItemQuality, unit);
						break;
					}
					case EBulletElement::EIncendiary:
					{
						UFBuffManager::CreateBuff(this, FName("Incendiary"), (int)ItemProperty.ItemQuality * 3.f, (int)ItemProperty.ItemQuality, unit);
						break;
					}
				}
				if (currentPiercing <= 0)
				{
					end = hits[i].Location;
					break;
				}
			}
			else
			{
				end = hits[i].Location;
				break;
			}
		}
	}
	if (auto trace = UGameplayStatics::SpawnEmitterAtLocation(world, WeaponProperty.TraceParticle, FTransform()))
	{
		trace->SetBeamSourcePoint(0, start, 0);
		trace->SetBeamTargetPoint(0, end, 0);
	}
}
