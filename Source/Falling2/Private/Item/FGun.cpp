// Fill out your copyright notice in the Description page of Project Settings.

#include "FGun.h"
#include "FBullet.h"

#include "Classes/Components/SkeletalMeshComponent.h"
#include "Classes/Components/ArrowComponent.h"

AFGun::AFGun()
{
	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	
	FireArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("FireArrow"));
	FireArrow->AttachToComponent(GunMesh, FAttachmentTransformRules::KeepRelativeTransform);
	FireArrow->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
}

void AFGun::StartFire()
{
	isFire = true;
	if (GunCDTimer <= 0.f)
	{
		Fire();
	}
}

void AFGun::EndFire()
{
	isFire = false;
}

void AFGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GunCDTimer > 0.f)
	{
		GunCDTimer -= DeltaTime;
	}
	else if(EGunFireMode::EBurstMode == GunAttribute.FireMode && isFire)
	{
		Fire();
	}
}

const TArray<FVector> AFGun::CalculationDirection()
{
	FVector forward = FireArrow->GetForwardVector();
	FVector direction = FVector(forward.X, forward.Y, 0.f);

	TArray<FVector> result;

	for (int counter = 0; counter < GunAttribute.ProjectileNum; ++counter)
	{
		forward = FRotator(0.f, direction.Rotation().Yaw + FMath::FRandRange(-GunAttribute.ScatteringAngle, GunAttribute.ScatteringAngle), 0.f).Vector();
		result.Add(forward);
	}

	return result;
}

void AFGun::Fire()
{
	if (CurrentBulletNum > 0)
	{
		--CurrentBulletNum;
		GunCDTimer = GunAttribute.MaxCD;

		SpawnBullet(CalculationDirection());
	}
}

void AFGun::SpawnBullet(const TArray<FVector>& directions)
{
	if (nullptr != GunAttribute.Bullet)
	{
		for (auto it : directions)
		{
			if (AFBullet* bullet = GetWorld()->SpawnActor<AFBullet>(GunAttribute.Bullet, FireArrow->GetComponentLocation(), it.Rotation()))
			{
				bullet->Initialize();
			}
		}
	}
}

