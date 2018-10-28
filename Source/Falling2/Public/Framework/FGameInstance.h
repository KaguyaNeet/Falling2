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

	class AFUnitManager* UnitManager = nullptr;
	class AFRoomManager* RoomManager = nullptr;

public:
	class AFItemManager* GetItemManager();
	class UFBuffManager* GetBuffManager();
	class AFUnitManager* GetUnitManager();
	class AFRoomManager* GetRoomManager();
	
	
};
