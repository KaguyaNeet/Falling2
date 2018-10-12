// Fill out your copyright notice in the Description page of Project Settings.

#include "FThrowable.h"

#include "Classes/GameFramework/ProjectileMovementComponent.h"

AFThrowable::AFThrowable()
{
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->bShouldBounce = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
}

