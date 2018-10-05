// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FBag.generated.h"

/**
 * 
 */
UCLASS()
class FALLING2_API UFBag : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BagProperty")
		int MaxItemNum = 20;
//	UPROPERTY(BlueprintReadOnly)
//		TMultiMap<class AFBaseItem*, int> Items;
//
//public:
//	bool AddItem(class AFBaseItem* item, UINT8 num);
	
	
};
