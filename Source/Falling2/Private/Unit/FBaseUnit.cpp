// Fill out your copyright notice in the Description page of Project Settings.

#include "FBaseUnit.h"
#include "FStateMachine.h"


// Sets default values
AFBaseUnit::AFBaseUnit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	StateMachine = NewObject<UFStateMachine>(this, UFStateMachine::StaticClass());
}

// Called when the game starts or when spawned
void AFBaseUnit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFBaseUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	StateMachine->UpdateStateMachine(DeltaTime);
}

// Called to bind functionality to input
void AFBaseUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

