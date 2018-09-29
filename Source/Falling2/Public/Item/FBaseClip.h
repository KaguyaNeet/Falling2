// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/FBaseItem.h"
#include "FBaseClip.generated.h"

/**
 * 
 */
UCLASS()
class FALLING2_API AFBaseClip : public AFBaseItem
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
		int MaxBulletCount = 5;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Property")
		int CurrentBulletCount = 0;
	
};