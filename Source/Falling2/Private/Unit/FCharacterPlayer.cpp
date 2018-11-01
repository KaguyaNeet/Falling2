// Fill out your copyright notice in the Description page of Project Settings.

#include "FCharacterPlayer.h"

#include "Classes/Components/InputComponent.h"
#include "Classes/Components/SkeletalMeshComponent.h"
#include "Classes/Camera/CameraComponent.h"
#include "Classes/GameFramework/SpringArmComponent.h"
#include "Classes/Components/ArrowComponent.h"
#include "Classes/Components/CapsuleComponent.h"


AFCharacterPlayer::AFCharacterPlayer()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->AttachTo(RootComponent);
	SpringArm->TargetArmLength = 700.f;
	SpringArm->SetRelativeRotation(FRotator(0.f, -40.f, 0.f));
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bUsePawnControlRotation = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachTo(SpringArm);

	CorrectionArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("CorrectionArrow"));
	CorrectionArrow->AttachTo(RootComponent);
	CorrectionArrow->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	GetMesh()->AttachTo(CorrectionArrow);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GetMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel3);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel4, ECollisionResponse::ECR_Block);


	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel4, ECollisionResponse::ECR_Ignore);
}


void AFCharacterPlayer::SetupPlayerInputComponent(UInputComponent* inputComponent)
{
	Super::SetupPlayerInputComponent(inputComponent);

	inputComponent->BindAxis("MoveForward", this, &AFCharacterPlayer::MoveForward);
	inputComponent->BindAxis("MoveRight", this, &AFCharacterPlayer::MoveRight);

	inputComponent->BindAction("MainFire", IE_Pressed, this, &AFCharacterPlayer::LeftMouseButtonDown);
	inputComponent->BindAction("MainFire", IE_Released, this, &AFCharacterPlayer::LeftMouseButtonUp);
	inputComponent->BindAction("SecondaryFire", IE_Pressed, this, &AFCharacterPlayer::RightMouseButtonDown);
	inputComponent->BindAction("SecondaryFire", IE_Released, this, &AFCharacterPlayer::RightMouseButtonUp);
	inputComponent->BindAction("Rolling", IE_Pressed, this, &AFCharacterPlayer::TriggerRolling);
	inputComponent->BindAction("Pick", IE_Pressed, this, &AFCharacterPlayer::PickUp);
}

void AFCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();


}

void AFCharacterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFCharacterPlayer::MoveForward(float value)
{
}

void AFCharacterPlayer::MoveRight(float value)
{
}

void AFCharacterPlayer::LeftMouseButtonDown()
{
}

void AFCharacterPlayer::LeftMouseButtonUp()
{
}

void AFCharacterPlayer::RightMouseButtonDown()
{
}

void AFCharacterPlayer::RightMouseButtonUp()
{
}

void AFCharacterPlayer::TriggerRolling()
{
}

void AFCharacterPlayer::PickUp()
{
}
