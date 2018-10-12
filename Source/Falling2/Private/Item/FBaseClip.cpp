// Fill out your copyright notice in the Description page of Project Settings.

#include "FBaseClip.h"

AFBaseClip::AFBaseClip()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
}


void AFBaseClip::InitilizeClip(const FClipListBP& ClipProperty)
{
	MaxBulletCount = ClipProperty.MaxBulletCount;
	CurrentBulletCount = MaxBulletCount;
	BulletElement = ClipProperty.BulletElement;
	WeaponType = ClipProperty.WeaponType;
	BulletDamage = ClipProperty.BulletDamage;
}

