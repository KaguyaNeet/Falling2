// Fill out your copyright notice in the Description page of Project Settings.

#include "FRoomInstance.h"


// Sets default values
AFRoomInstance::AFRoomInstance()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFRoomInstance::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFRoomInstance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

