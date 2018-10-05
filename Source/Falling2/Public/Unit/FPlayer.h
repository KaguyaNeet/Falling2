// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Unit/FCharacter.h"
#include "FPlayer.generated.h"

/**
 * 
 */
UCLASS()
class FALLING2_API AFPlayer : public AFCharacter
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UArrowComponent* CorrectionArrow;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerProperty")
		float CurrentOffset = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerProperty")
		float VelocityOffset = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerProperty")
		bool Turn = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerProperty")
		bool RightTurn = false;

	UPROPERTY(EditAnywhere, Category = "PlayerProperty")
		float RollingDistance = 1000.f;
	UPROPERTY(EditAnywhere, Category = "PlayerProperty")
		float LifeTime = 1.f;

	UPROPERTY(BlueprintReadOnly)
		AFBaseWeapon* CurrentMainWeapon = nullptr;
	UPROPERTY(BlueprintReadOnly)
		AFBaseWeapon* CurrentSecondaryWeapon = nullptr;

	FVector Direction = FVector::ZeroVector;
private:
	FHitResult lastHit;
	
	TArray<class AFBaseItem*> TriggerItems;
	class AFBaseItem* CurrentChooseItem = nullptr;

public:
	AFPlayer();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* inputComponent) override;

	void PlayerBaseAnimUpdate(float DeltaTime);

	UFUNCTION(BlueprintCallable)
		void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	void MoveForward(float value);
	void MoveRight(float value);

	void LeftMouseButtonDown();
	void LeftMouseButtonUp();
	void RightMouseButtonDown();
	void RightMouseButtonUp();

	void TriggerRolling();

	void AddTriggerItem(class AFBaseItem* item);
	void RemoveTriggerItem(class AFBaseItem* item);

	void UpdateTriggerItemInfo();
	void PickUp();

};
