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
	class AFBuffManager* BuffManager = nullptr;

public:
	class AFBuffManager* GetBuffManager();
	
	
};
