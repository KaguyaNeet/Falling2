// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "FBaseClip.h"
#include "FBaseWeapon.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FBullet.generated.h"

UCLASS()
class FALLING2_API AFBullet : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		class UProjectileMovementComponent* BulletMovement;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		class UStaticMeshComponent* BulletMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		class UBoxComponent* BulletTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Property")
		bool isPenetrating = false;

private:
	EBulletElement Element = EBulletElement::ENormal;
	class AFBaseUnit* BulletOwner = nullptr;
	UINT BaseDamage = 0;
	float LifeTime = 10.f;
	UINT Piercing = 0;
	
public:	
	// Sets default values for this actor's properties
	AFBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Initialize(class AFBaseUnit* owner, EBulletElement element, UINT baseDamage, float Speed, float Range, UINT piercing);
	virtual void DestroyBullet();
	
	UFUNCTION()
		virtual void BulletHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
