// Fill out your copyright notice in the Description page of Project Settings.

#include "FBullet.h"
#include "FBaseUnit.h"

#include "Classes/GameFramework/ProjectileMovementComponent.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Classes/Components/BoxComponent.h"
// Sets default values
AFBullet::AFBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BulletMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BulletMovement"));

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	BulletMesh->SetupAttachment(RootComponent);
	BulletMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	BulletTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BulletTrigger"));
	BulletTrigger->SetupAttachment(BulletMesh);
	BulletTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BulletTrigger->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);
	BulletTrigger->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BulletTrigger->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Overlap);
	BulletTrigger->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
}

// Called when the game starts or when spawned
void AFBullet::BeginPlay()
{
	Super::BeginPlay();

	BulletTrigger->OnComponentBeginOverlap.AddDynamic(this, &AFBullet::BulletHit);
}

// Called every frame
void AFBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (LifeTime > 0.f)
	{
		LifeTime -= DeltaTime;
	}
	else
	{
		DestroyBullet();
	}
	
}

void AFBullet::Initialize(AFBaseUnit* owner, EWeaponType weaponType, EBulletElement element, UINT level, UINT baseDamage, float Speed, float Range, UINT piercing)
{
	BulletMovement->Velocity = FVector(Speed, 0.f, 0.f);
	BulletOwner = owner;
	BaseDamage = baseDamage;
	LifeTime = Range / Speed;
	Element = element;
	Piercing = piercing;
}

void AFBullet::DestroyBullet()
{
	BulletTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AFBullet::BulletHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (AFBaseUnit* unit = Cast<AFBaseUnit>(OtherActor))
	{
		//unit->ApplyDamage(BulletOwner, Element, BaseDamage, Piercing);
		//if (!isPenetrating)
		//{
		//	DestroyBullet();
		//}
	}
}

