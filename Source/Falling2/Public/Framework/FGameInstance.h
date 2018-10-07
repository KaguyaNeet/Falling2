// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FALLING2_API UFGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	class AFItemManager* ItemManager = nullptr;

	UPROPERTY()
		class UFBuffManager* BuffManager = nullptr;

public:
	class AFItemManager* GetItemManager();
	class UFBuffManager* GetBuffManager();
	
	
};
