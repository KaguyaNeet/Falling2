// Fill out your copyright notice in the Description page of Project Settings.

#include "FDoor.h"


UENUM(BlueprintType)
enum class ERoomType : uint8
{

};

// Sets default values
AFDoor::AFDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

