// Fill out your copyright notice in the Description page of Project Settings.

#include "FBaseClip.h"

#include "Classes/Components/StaticMeshComponent.h"
#include "Classes/Components/SphereComponent.h"

AFBaseClip::AFBaseClip()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->AttachTo(Trigger);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMesh->SetRelativeScale3D(FVector(3.f, 3.f, 3.f));
}


void AFBaseClip::InitilizeClip(const FClipListBP& ClipProperty)
{
	MaxBulletCount = ClipProperty.MaxBulletCount;
	CurrentBulletCount = MaxBulletCount;
	BulletElement = ClipProperty.BulletElement;
	WeaponType = ClipProperty.WeaponType;
	BulletDamage = ClipProperty.BulletDamage;
	StaticMesh->SetStaticMesh(ClipProperty.ClipMesh);
}

