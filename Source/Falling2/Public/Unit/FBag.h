// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "FBaseItem.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FBag.generated.h"

/**
 * 
 */
UCLASS()
class FALLING2_API AFBag : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BagProperty")
		int MaxItemNum = 20;

	TMultiMap<FName, int> Items;

	UPROPERTY(BlueprintReadOnly)
		TArray<FUMGItemProperty> UMGItems;

	class AFBaseUnit* Owner = nullptr;

public:
	void Initialize(class AFBaseUnit* owner);

	bool AddItem(const FName& name);
	UFUNCTION(BlueprintCallable)
		void UseItem(const FName& name);
	void RemoveItem(const FName& name);

	void UpdateUMGItem();
	
	
};
