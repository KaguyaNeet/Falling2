// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/FBaseItem.h"
#include "FBaseWeapon.generated.h"


UENUM(BlueprintType)
enum class EFireMode : uint8
{
	ESingleMode UMETA(DisplayName = "SingleShotMode"),
	EBurstMode UMETA(DisplayName = "BurstMode")
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	EBegin = 0,

	ERifle = 1      UMETA(DisplayName = "Rifle"),
	EShotgun = 1 << 1 UMETA(DisplayName = "Shotgun"),
	ESniper = 1 << 2 UMETA(DisplayName = "Sniper"),
	EGrenade = 1 << 3 UMETA(DisplayName = "Grenade"),
	ERocket = 1 << 4 UMETA(DisplayName = "Rocket"),
	ELaser = 1 << 5 UMETA(DisplayName = "Laser"),

	EMax = MAX_uint8,
};

UENUM(BlueprintType)
enum class EBulletElement : uint8
{
	EBegin = 0,

	ENormal UMETA(DisplayName = "Normal"),
	EIncendiary UMETA(DisplayName = "Incendiary"),
	EFrozen UMETA(DisplayName = "Frozen"),
	ECorrosive UMETA(DisplayName = "Corrosive"),
	EExplosive UMETA(DisplayName = "Explosive"),
	EBlackhole UMETA(DisplayName = "Blackhole"),

	EMax = MAX_uint8,
};

USTRUCT()
struct FWeaponProperty : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	//Type of this weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		EWeaponType WeaponType = EWeaponType::ERifle;
	//Base damage value of this weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int BaseDamageValue = 0;
	//Skeletal mesh of this weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USkeletalMesh* WeaponMesh = nullptr;
	//Relative attachment location of this weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FVector AttachLocation = FVector::ZeroVector;
	//Relative attachment rotation of this weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FRotator AttachRotation = FRotator::ZeroRotator;
	//Fire location of this weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FVector FireLocation = FVector::ZeroVector;

	//Muzzle particle of this weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UParticleSystem* MuzzleParticle = nullptr;
	//Trace particle of this weapon, if bullet is a actor, set this property as nullptr.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UParticleSystem* TraceParticle = nullptr;
	//Hit particle of this weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UParticleSystem* HitParticle = nullptr;

	//Bullet's class of this weapon, only set when bullet is a actor.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UClass* Bullet = nullptr;

	//Fire mode of this weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		EFireMode FireMode = EFireMode::ESingleMode;
	//Is this weapon the main one?
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool IsMainWeapon = true;
	//Is this weapon can equip a secondary weapon?
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool CanEquipSecondaryWeapon = false;
	//Maximum CD of this weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float MaxCD = 1.f;
	//Maximum fire range of this weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float FireRange = 1000.f;
	//Projectile number of this weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int ProjectileNum = 1;
	//Recoil of this weapon, beteween 0 ~ 100.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Recoil = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int Piercing = 0;

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

USTRUCT()
struct FWeaponListBP : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	//Base property of this weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FItemProperty ItemProperty;
	//Property of this weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FWeaponProperty WeaponProperty;
};
/**
 * 
 */
UCLASS()
class FALLING2_API AFBaseWeapon : public AFBaseItem
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		class USkeletalMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		class UArrowComponent* FireArrow;

public:
	class AFBaseClip* CurrentClip = nullptr;
	AFBaseWeapon* SecondaryWeapon = nullptr;

	UPROPERTY(BlueprintReadOnly)
		FWeaponProperty WeaponProperty;

private:
	float CurrentCD = 0.f;
	bool isFire = false;
	float CurrentScatteringAngle = 0.f;
	EBulletElement CurrentBulletElement = EBulletElement::ENormal;
	UINT8 CurrentBulletDamage = 0;

public:
	AFBaseWeapon();

	void InitializeWeapon(const FWeaponProperty& weaponProperty);

	virtual void Tick(float DeltaTime) override;
	virtual void Invisible(bool newState) override;

	void EquipWeapon(class AFBaseUnit* owner);
	void Reload(class AFBaseClip* clip);

	void StartFire();
	void EndFire();

	void RequestReload();

protected:
	bool CheckFire();

	TArray<FVector> CalculationDirection();
	void SpawnFire(const TArray<FVector>& directions);

private:
	void SpawnActorBullet(FVector direction);
	void SpawnTraceBullet(FVector direction);
	
};
