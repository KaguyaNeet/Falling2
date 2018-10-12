// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/FBaseItem.h"
#include "FThrowable.generated.h"

UENUM(BlueprintType)
enum class EThrowableType : uint8
{
	EExplosive UMETA(DisplayName = "Explosive"),
};

USTRUCT()
struct FThrowableProperty : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		EThrowableType ThrowableType = EThrowableType::EExplosive;
};

/**
 * 
 */
UCLASS()
class FALLING2_API AFThrowable : public AFBaseItem
{
	GENERATED_BODY()

public:
	AFThrowable();

	void InitializeThrowable(const FThrowableProperty& weaponProperty);

	void Throw(const FVector& direction);

	virtual void Explosion(){ }
	
public:
	class UProjectileMovementComponent* ProjectileMovement;
	class UStaticMeshComponent* StaticMesh;

public:
	UPROPERTY(BlueprintReadOnly)
		FThrowableProperty WeaponProperty;
	
	
};
