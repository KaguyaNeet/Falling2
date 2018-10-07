// Fill out your copyright notice in the Description page of Project Settings.

#include "FPlayer.h"
#include "FStateMachine.h"
#include "FBaseWeapon.h"
#include "FBag.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Classes/Components/InputComponent.h"
#include "Classes/Components/SkeletalMeshComponent.h"
#include "Classes/Camera/CameraComponent.h"
#include "Classes/GameFramework/SpringArmComponent.h"
#include "Classes/Components/ArrowComponent.h"
#include "Classes/Components/CapsuleComponent.h"


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
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GetMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel3);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Block);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);
}

void AFPlayer::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AFPlayer::OnCapsuleBeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AFPlayer::OnCapsuleEndOverlap);
	
	if (nullptr != StateMachine)
	{
		StateMachine->ChangeState(UFSPlayerBaseMove::StaticClass());
	}

	if (APlayerController* controller = UGameplayStatics::GetPlayerController(this, 0))
	{
		controller->bShowMouseCursor = true;
	}

	if (UWorld* world = GetWorld())
	{
		Bag = world->SpawnActor<AFBag>(FVector::ZeroVector, FRotator::ZeroRotator);
		Bag->Initialize(this);
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

	inputComponent->BindAction("MainFire", IE_Pressed, this, &AFPlayer::LeftMouseButtonDown);
	inputComponent->BindAction("MainFire", IE_Released, this, &AFPlayer::LeftMouseButtonUp);
	inputComponent->BindAction("SecondaryFire", IE_Pressed, this, &AFPlayer::RightMouseButtonDown);
	inputComponent->BindAction("SecondaryFire", IE_Released, this, &AFPlayer::RightMouseButtonUp);
	inputComponent->BindAction("Rolling", IE_Pressed, this, &AFPlayer::TriggerRolling);
	inputComponent->BindAction("Pick", IE_Pressed, this, &AFPlayer::PickUp);
}

void AFPlayer::PlayerBaseAnimUpdate(float DeltaTime)
{
	if (APlayerController* controller = UGameplayStatics::GetPlayerController(this, 0))
	{
		FHitResult hit;
		controller->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, hit) ? lastHit = hit : hit = lastHit;
		FRotator rotation = GetMesh()->GetRelativeTransform().Rotator();
		FVector direction = hit.Location - GetActorLocation();
		Direction = direction;
		FVector directionXY = FVector(direction.X, direction.Y, 0.f);

		

		FVector velocity = GetVelocity();
		if (velocity.Size2D() > 0.f)
		{
			float sign;
			velocity.Rotation().Yaw >= 0.f ? sign = 1.f : sign = -1.f;
			float velocityOffset = directionXY.Rotation().Yaw - velocity.Rotation().Yaw;
			VelocityOffset = FMath::Abs(velocityOffset) > 180.f ? (360.f - FMath::Abs(velocityOffset)) * sign : velocityOffset;
			GetMesh()->SetRelativeRotation(UKismetMathLibrary::RLerp(rotation, directionXY.Rotation(), DeltaTime * 5.f, true));
		}
		else
		{
			VelocityOffset = 0.f;
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
				if (FMath::Abs(offset) > 0.35f)
					Turn = true;
			}
			else
			{
				GetMesh()->SetRelativeRotation(UKismetMathLibrary::RLerp(rotation, directionXY.Rotation(), DeltaTime * 5.f, true));
				if (FMath::Abs(offset) <= 0.05f)
					Turn = false;
			}
			CurrentOffset = UKismetMathLibrary::Lerp(CurrentOffset, offset, DeltaTime * 5.f);
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

void AFPlayer::LeftMouseButtonDown()
{
	if (nullptr != CurrentWeapon && StateMachine->CheckState(UFSPlayerBaseMove::StaticClass()))
	{
		CurrentWeapon->StartFire();
	}
}

void AFPlayer::LeftMouseButtonUp()
{
	if (nullptr != CurrentWeapon)
	{
		CurrentWeapon->EndFire();
	}
}

void AFPlayer::RightMouseButtonDown()
{
}

void AFPlayer::RightMouseButtonUp()
{
}

void AFPlayer::TriggerRolling()
{
	if (nullptr != StateMachine && StateMachine->CheckState(UFSPlayerBaseMove::StaticClass()))
	{
		if (nullptr != CurrentWeapon)
		{
			CurrentWeapon->EndFire();
		}
		FVector direction = GetVelocity().Size() <= 0.f ? Direction : GetVelocity();
		Rolling(LifeTime, RollingDistance, direction);
	}
}

void AFPlayer::AddTriggerItem(AFBaseItem * item)
{
	TriggerItems.AddUnique(item);
	UpdateTriggerItemInfo();
}

void AFPlayer::RemoveTriggerItem(AFBaseItem * item)
{
	TriggerItems.Remove(item);
	UpdateTriggerItemInfo();
}

void AFPlayer::UpdateTriggerItemInfo()
{
	CurrentChooseItem = nullptr;
	for (int i = 0; i < TriggerItems.Num(); ++i)
	{
		if (nullptr != TriggerItems[i])
		{
			CurrentChooseItem = TriggerItems[i];
			break;
		}
	}
	//Display the Item info.
}

void AFPlayer::PickUp()
{
	if (nullptr != CurrentChooseItem)
	{
		if (AFBaseWeapon* weapon = Cast<AFBaseWeapon>(CurrentChooseItem))
		{
			if (nullptr == CurrentMainWeapon && weapon->IsMainWeapon)
			{
				CurrentChooseItem->PickedUp(this);
				CurrentMainWeapon = weapon;
				Equip(weapon);
				CurrentMainWeapon->EquipWeapon(this);
				return;
			}
			if (nullptr == CurrentSecondaryWeapon && !weapon->IsMainWeapon)
			{
				CurrentChooseItem->PickedUp(this);
				CurrentSecondaryWeapon = weapon;
				return;
			}
		}
		if (nullptr != Bag)
		{
			if (Bag->AddItem(CurrentChooseItem->ItemProperty.ItemInternalName))
			{
				CurrentChooseItem->PickedUp(this);
				CurrentChooseItem->Destroy();
			}
		}
	}
}

void AFPlayer::OnCapsuleBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
	if (AFBaseItem* item = Cast<AFBaseItem>(OtherActor))
	{
		if (!item->isPicked)
			AddTriggerItem(item);
	}
}

void AFPlayer::OnCapsuleEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (AFBaseItem* item = Cast<AFBaseItem>(OtherActor))
	{
		RemoveTriggerItem(item);
	}
}
