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
	BulletMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	BulletMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	BulletTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BulletTrigger"));
	BulletTrigger->AttachToComponent(BulletMesh, FAttachmentTransformRules::KeepRelativeTransform);
	BulletTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BulletTrigger->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);
	BulletTrigger->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BulletTrigger->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Block);
	BulletTrigger->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
}

// Called when the game starts or when spawned
void AFBullet::BeginPlay()
{
	Super::BeginPlay();
	
	BulletTrigger->OnComponentHit.AddDynamic(this, &AFBullet::BulletHit);
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

void AFBullet::Initialize(AFBaseUnit* owner, EBulletElement element, UINT baseDamage, float Speed, float Range, UINT piercing)
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

void AFBullet::BulletHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	if (AFBaseUnit* unit = Cast<AFBaseUnit>(OtherActor))
	{
		unit->ApplyDamage(BulletOwner, Element, BaseDamage, Piercing);
		if (!isPenetrating)
		{
			DestroyBullet();
		}
	}
}

