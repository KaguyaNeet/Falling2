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
	ERifle UMETA(DisplayName = "Rifle"),
	EShotgun UMETA(DisplayName = "Shotgun"),
	ESniper UMETA(DisplayName = "Sniper"),
	EGrenade UMETA(DisplayName = "Grenade"),
	ERocket UMETA(DisplayName = "Rocket"),
	ELaser UMETA(DisplayName = "Laser")
};


USTRUCT()
struct FWeaponList : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	//Base property of this weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FItemProperty ItemProperty;

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

	//Maximum scattering angle of thie weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float MaxScatteringAngle = 5.f;
	//Scattering angle's increment of this weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float ScatteringAngleIncrement = 0.1f;

	//ScatteringAngle of the shotgun, Shotgun attribute.
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponDescription")
		FName WeaponName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponDescription")
		FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponDescription")
		UParticleSystem* MuzzleParticle = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponDescription")
		UParticleSystem* TraceParticle = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponDescription")
		UParticleSystem* HitParticle = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponTransform")
		FVector WeaponLocation = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponTransform")
		FRotator WeaponRotator = FRotator::ZeroRotator;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponProperty")
		EFireMode FireMode = EFireMode::ESingleMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponProperty")
		EWeaponType WeaponType = EWeaponType::ERifle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponProperty")
		bool IsMainWeapon = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponProperty")
		bool CanEquipSecondaryWeapon = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponProperty")
		float MaxCD = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponProperty")
		float FireRange = 1000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponProperty")
		int DamageValue = 10;


private:
	float CurrentCD = 0.f;
	bool isFire = false;


public:
	AFBaseWeapon();

	virtual void Tick(float DeltaTime) override;
	virtual void Invisible(bool newState) override;

	void EquipWeapon(class AFBaseUnit* owner);
	void Reload(class AFBaseClip* clip);

	void StartFire();
	void EndFire();

	void RequestReload();

protected:
	bool CheckFire();
	//Test use.
	void Fire();
	TArray<FRotator> CalculationDirection();
	void SpawnFire(const TArray<FRotator>& directions);
	
};
