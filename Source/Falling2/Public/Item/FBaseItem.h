// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FBaseItem.generated.h"

UCLASS()
class FALLING2_API AFBaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFBaseItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Invisible(bool newState){ }
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnGround();
	void PickedUp(class AFBaseUnit* owner);

public:
	class AFBaseUnit* ItemOwner = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class USphereComponent* Trigger;
};
