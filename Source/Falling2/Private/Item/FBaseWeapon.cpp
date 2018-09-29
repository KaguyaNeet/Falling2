// Fill out your copyright notice in the Description page of Project Settings.

#include "FBaseWeapon.h"
#include "FBaseClip.h"
#include "FBaseUnit.h"

#include "Classes/Components/SkeletalMeshComponent.h"
#include "Classes/Components/ArrowComponent.h"

AFBaseWeapon::AFBaseWeapon()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	FireArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("FireArrow"));
	FireArrow->AttachTo(RootComponent);
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

void AFBaseWeapon::EquipWeapon(class AFBaseUnit* owner)
{
	WeaponOwner = owner;
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
	if (nullptr != WeaponOwner)
	{
		WeaponOwner->Reload();
	}
}

void AFBaseWeapon::Fire()
{
	
}

bool AFBaseWeapon::CheckFire()
{
	if (nullptr == CurrentClip)
	{
		RequestReload();
		return false;
	}
	else if (CurrentClip->CurrentBulletCount <= 0)
	{
		RequestReload();
		return false;
	}
	--CurrentClip->CurrentBulletCount;
	CurrentCD = MaxCD;
	Fire();
	return true;
}
