// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FItemCreater.generated.h"

UCLASS()
class FALLING2_API AFItemCreater : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFItemCreater();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(VisibleAnywhere)
		class UTextRenderComponent* Text;
	UPROPERTY(VisibleAnywhere)
		class UArrowComponent* Arrow;
	
};
