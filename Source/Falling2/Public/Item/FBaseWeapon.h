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
	ERifle UMETA(DisplayName = "Rifle")
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
	class AFBaseUnit* WeaponOwner = nullptr;
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

	void EquipWeapon(class AFBaseUnit* owner);
	void Reload(class AFBaseClip* clip);

	void StartFire();
	void EndFire();

	void RequestReload();
	
	

protected:
	virtual bool CheckFire();
	virtual void Fire();
};
