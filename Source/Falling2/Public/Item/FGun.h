// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/FWeapon.h"
#include "FGun.generated.h"

UENUM(BlueprintType)
enum class EGunFireMode : uint8
{
	ESingleMode UMETA(DisplayName = "SingleShotMode"),
	EBurstMode UMETA(DisplayName = "BurstMode"),
};

UENUM(BlueprintType)
enum class EGunType : uint8
{
	ERifle UMETA(DisplayName = "Rifle"),
	EShotgun UMETA(DisplayName = "Shotgun"),
	ESniper UMETA(DisplayName = "Sniper"),
	EGrenade UMETA(DisplayName = "Grenade"),
	ERocket UMETA(DisplayName = "Rocket"),
	ELaser UMETA(DisplayName = "Laser")
};

USTRUCT()
struct FGunAttribute : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// Type of this weapon
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		EGunType GunType = EGunType::ERifle;

	// Skeletal mesh of this weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USkeletalMesh* WeaponMesh = nullptr;

	// Base damage value of this weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int BaseDamageValue = 0;

	// Relative attachment location of this weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FVector AttachLocation = FVector::ZeroVector;

	// Relative attachment rotation of this weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FRotator AttachRotation = FRotator::ZeroRotator;

	// Fire location of this weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FVector FireLocation = FVector::ZeroVector;

public:
	// Muzzle particle of this weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UParticleSystem* MuzzleParticle = nullptr;

	// Trace particle of this weapon, if bullet is a actor, set this property as nullptr.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UParticleSystem* TraceParticle = nullptr;

	// Hit particle of this weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UParticleSystem* HitParticle = nullptr;

public:
	// Bullet's class of this weapon, only set when bullet is a actor.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UClass* Bullet = nullptr;

public:
	// Fire mode of this weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		EGunFireMode FireMode = EGunFireMode::ESingleMode;

	//Is this weapon the main one?
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool IsMainWeapon = true;

	// Is this weapon can equip a secondary weapon?
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool CanEquipSecondaryWeapon = false;

	// Maximum CD of this weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float MaxCD = 1.f;

	// Maximum fire range of this weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float FireRange = 1000.f;

	// Projectile number of this weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int ProjectileNum = 1;

	// Recoil of this weapon, beteween 0 ~ 100.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Recoil = 0.f;

	// Piercing of this weapon
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int Piercing = 0;

public:
	//Maximum scattering angle of thie weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float MaxScatteringAngle = 5.f;

	//Scattering angle's increment of this weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float ScatteringAngleIncrement = 0.1f;

	//Scattering angle's reduction of this weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float ScatteringAngleReduction = 0.1f;

	//ScatteringAngle of the multi bullet.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float ScatteringAngle = 15.f;

	//Starting angle of the sniper, Sniper attribute.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float StartingAngle = 15.f;

	//Aiming time of the sniper, Sniper attribute.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float AimingTime = 1.f;

	//Speed of the actor bullet.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float BulletSpeed = 2000.f;
};



/**
 * 
 */
UCLASS()
class FALLING2_API AFGun : public AFWeapon
{
	GENERATED_BODY()
	
public:
	// The attribute of this gun
	UPROPERTY()
		FGunAttribute GunAttribute;


public:
	// Constructor
	AFGun();

	// Pressed the fire button
	void StartFire();

	// Release the fire button
	void EndFire();

protected:
	// Tick
	virtual void Tick(float DeltaTime) override;

private:
	// Calculation the fire direction
	const TArray<FVector> CalculationDirection();

	// Check and open fire
	void Fire();

	// Spawn the bullet actor
	void SpawnBullet(const TArray<FVector>& directions);

private:
	// Gun state, is shoting
	bool isFire = false;

	// Gun fire timer
	float GunCDTimer = 0.f;

	// Number of bullets
	UINT CurrentBulletNum = 0;

public:
	// Components of this gun

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		class USkeletalMeshComponent* GunMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		class UArrowComponent* FireArrow;
	
};
