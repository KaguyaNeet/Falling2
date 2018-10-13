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
	//Cameraboom of this player.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class USpringArmComponent* SpringArm;
	//Main camera of this game.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UCameraComponent* Camera;
	//The arrow help for repairing the mesh direction.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UArrowComponent* CorrectionArrow;
	//The offset between the cursor direction and the direction of the mesh.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerProperty")
		float CurrentOffset = 0.f;
	//The offset between the velocity direction and the direction of the mesh.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerProperty")
		float VelocityOffset = 0.f;
	//Whether the player is turning around.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerProperty")
		bool Turn = false;
	//Whether the turing is right turning.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerProperty")
		bool RightTurn = false;

	//The distance of the rolling
	UPROPERTY(EditAnywhere, Category = "PlayerProperty")
		float RollingDistance = 1000.f;
	//The time of the rolling
	UPROPERTY(EditAnywhere, Category = "PlayerProperty")
		float LifeTime = 1.f;
	
	//The bag of the player.
	UPROPERTY(BlueprintReadOnly)
		class AFBag* Bag;

	//The current main weapon that the player choose
	UPROPERTY(BlueprintReadOnly)
		AFBaseWeapon* CurrentMainWeapon = nullptr;
	//The current secondary weapon that the player choose.
	UPROPERTY(BlueprintReadOnly)
		AFBaseWeapon* CurrentSecondaryWeapon = nullptr;

	//The current cursor direction.
	FVector CursorDirection = FVector::ZeroVector;
private:
	//The last cursor hit with the ground.
	FHitResult lastHit;
	
	//Items currently overlapping with the player character.
	TArray<class AFBaseItem*> TriggerItems;
	//The newest item that currently overlapping with the player character.
	class AFBaseItem* CurrentChooseItem = nullptr;

public:
	AFPlayer();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* inputComponent) override;

	//This function will called by state machine to update the base animation of player.
	void PlayerBaseAnimUpdate(float DeltaTime);

	//This function will called when the capsule component begin overlap.
	UFUNCTION(BlueprintCallable)
		void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//This function will called when the capsule component end overlap.
	UFUNCTION()
		void OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	//These functions are attaching with the input event.
	void MoveForward(float value);
	void MoveRight(float value);
	void LeftMouseButtonDown();
	void LeftMouseButtonUp();
	void RightMouseButtonDown();
	void RightMouseButtonUp();
	void TriggerRolling();

	//This function will called by capsule begin overlap delegate for adding the overlapping item to the TriggerItems array.
	void AddTriggerItem(class AFBaseItem* item);
	//This function will called by capsule end overlap delegate for removing the end overlaping item from the TriggerItems array.
	void RemoveTriggerItem(class AFBaseItem* item);

	//Making sure that the last begin overlapping item is the CurrentChooseItem.
	void UpdateTriggerItemInfo();

	//This function are attaching with the input event.it will add the CurrentChooseItem to player's bag.
	void PickUp();

	//Player reload
	virtual void Reload() override;
};
