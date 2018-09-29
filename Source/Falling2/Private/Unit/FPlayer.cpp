// Fill out your copyright notice in the Description page of Project Settings.

#include "FPlayer.h"
#include "FStateMachine.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Classes/Components/InputComponent.h"
#include "Classes/Components/SkeletalMeshComponent.h"
#include "Classes/Camera/CameraComponent.h"
#include "Classes/GameFramework/SpringArmComponent.h"
#include "Classes/Components/ArrowComponent.h"



AFPlayer::AFPlayer()
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
}

void AFPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (nullptr != StateMachine)
	{
		StateMachine->ChangeState(UFSPlayerBaseMove::StaticClass());
	}

	if (APlayerController* controller = UGameplayStatics::GetPlayerController(this, 0))
	{
		controller->bShowMouseCursor = true;
	}
}

void AFPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}


void AFPlayer::SetupPlayerInputComponent(class UInputComponent* inputComponent)
{
	Super::SetupPlayerInputComponent(inputComponent);

	inputComponent->BindAxis("MoveForward", this, &AFPlayer::MoveForward);
	inputComponent->BindAxis("MoveRight", this, &AFPlayer::MoveRight);
}

void AFPlayer::PlayerBaseAnimUpdate(float DeltaTime)
{
	if (APlayerController* controller = UGameplayStatics::GetPlayerController(this, 0))
	{
		FHitResult hit;
		controller->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, hit) ? lastHit = hit : hit = lastHit;
		FRotator rotation = GetMesh()->GetRelativeTransform().Rotator();
		FVector direction = hit.Location - GetActorLocation();
		FVector directionXY = FVector(direction.X, direction.Y, 0.f);

		float offset = (directionXY.Rotation().Yaw - rotation.Yaw) / 180.f;
		if (FMath::Abs(offset) > 1.f)
		{
			float sign;
			sign = rotation.Yaw >= 0.f ? 1.f : -1.f;
			offset = sign * (360.f - (FMath::Abs(directionXY.Rotation().Yaw) + FMath::Abs(rotation.Yaw))) / 180.f;
			RightTurn = sign > 0.f ? true : false;
		}
		if (!Turn)
		{
			if (FMath::Abs(offset) > 0.48f)
				Turn = true;
		}
		else
		{
			GetMesh()->SetRelativeRotation(UKismetMathLibrary::RLerp(rotation, directionXY.Rotation(), DeltaTime * 5.f, true));
			if (FMath::Abs(offset) <= 0.05f)
				Turn = false;
		}
		CurrentOffset = UKismetMathLibrary::Lerp(CurrentOffset, offset, DeltaTime * 5.f);

		FVector velocity = GetVelocity();
		if (velocity.Size2D() > 0.f)
		{
			float sign;
			velocity.Rotation().Yaw >= 0.f ? sign = 1.f : sign = -1.f;
			float velocityOffset = directionXY.Rotation().Yaw - velocity.Rotation().Yaw;
			VelocityOffset = FMath::Abs(velocityOffset) > 180.f ? (360.f - FMath::Abs(velocityOffset)) * sign : velocityOffset;
		}
		else
		{
			VelocityOffset = 0.f;
		}
	}
}

void AFPlayer::MoveForward(float value)
{
	if (nullptr != StateMachine && StateMachine->CheckState(UFSPlayerBaseMove::StaticClass()))
	{
		AddMovementInput(FVector(1.f, 0.f, 0.f), value);
	}
}

void AFPlayer::MoveRight(float value)
{
	if (nullptr != StateMachine && StateMachine->CheckState(UFSPlayerBaseMove::StaticClass()))
	{
		AddMovementInput(FVector(0.f, 1.f, 0.f), value);
	}
}
