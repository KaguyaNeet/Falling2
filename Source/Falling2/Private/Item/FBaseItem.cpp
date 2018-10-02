// Fill out your copyright notice in the Description page of Project Settings.

#include "FBaseItem.h"
#include "FBaseUnit.h"
#include "Classes/Components/SphereComponent.h"

// Sets default values
AFBaseItem::AFBaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	Trigger->AttachTo(RootComponent);
	Trigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Trigger->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Trigger->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

// Called when the game starts or when spawned
void AFBaseItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFBaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFBaseItem::OnGround()
{
	Trigger->SetActive(true);
	ItemOwner = nullptr;
	Invisible(false);
	SetActorScale3D(FVector(0.5f, 0.5f, 0.5f));
}

void AFBaseItem::PickedUp(AFBaseUnit * owner)
{
	if (nullptr != owner)
	{
		Trigger->SetActive(false);
		ItemOwner = owner;
		Invisible(true);
		SetActorScale3D(FVector(1.f, 1.f, 1.f));
	}
}

