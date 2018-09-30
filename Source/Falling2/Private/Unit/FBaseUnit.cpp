// Fill out your copyright notice in the Description page of Project Settings.

#include "FBaseUnit.h"
#include "FStateMachine.h"
#include "FBaseWeapon.h"

#include "Classes/Components/SkeletalMeshComponent.h"


// Sets default values
AFBaseUnit::AFBaseUnit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	
}

// Called when the game starts or when spawned
void AFBaseUnit::BeginPlay()
{
	Super::BeginPlay();

	StateMachine = NewObject<UFStateMachine>(this, UFStateMachine::StaticClass(), UFStateMachine::StaticClass()->GetFName());
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

void AFBaseUnit::ReleaseStateMachine()
{
	StateMachine->Release();
	StateMachine = nullptr;
}

void AFBaseUnit::ApplyDamage(AFBaseUnit* causer, UINT16 value)
{

}

void AFBaseUnit::Equip(AFBaseWeapon* weapon)
{
	if (nullptr != weapon)
	{
		CurrentWeapon = weapon;
		FAttachmentTransformRules rules(EAttachmentRule::KeepRelative, false);
		weapon->AttachToComponent(GetMesh(), rules, FName("b_RightHandIndex1"));
		weapon->EquipWeapon(this);
	}
}
