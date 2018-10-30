// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/FBaseItem.h"
#include "FWeapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponElemental : uint8
{
	ENormal UMETA(DisplayName = "Normal"),
	EFire UMETA(DisplayName = "Fire"),
	EIce UMETA(DisplayName = "Ice"),
	EThunder UMETA(DisplayName = "Thunder"),
};

/**
 * 
 */
UCLASS()
class FALLING2_API AFWeapon : public AFBaseItem
{
	GENERATED_BODY()
	
	
	
	
};
