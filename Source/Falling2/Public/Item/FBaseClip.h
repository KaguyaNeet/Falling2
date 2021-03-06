// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "FBaseWeapon.h"

#include "CoreMinimal.h"
#include "Item/FBaseItem.h"
#include "FBaseClip.generated.h"

/**
 * 
 */
UCLASS()
class FALLING2_API AFBaseClip : public AFBaseItem
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
		int MaxBulletCount = 5;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Property")
		int CurrentBulletCount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Property")
		EBulletElement BulletElement = EBulletElement::ENormal;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Property")
		EWeaponType WeaponType = EWeaponType::ERifle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Property")
		int BulletDamage = 1;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* StaticMesh;

public:
	AFBaseClip();

	void InitilizeClip(const FClipListBP& ClipProperty);
};