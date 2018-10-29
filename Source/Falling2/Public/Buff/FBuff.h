// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FBuff.generated.h"

using BuffFunc = void(*)(class AFBaseUnit* owner, class AFBaseUnit* adder, class UFBuff* buff, UINT lifetime, UINT level);

UENUM(BlueprintType)
enum class EBuffType : uint8
{
	ENormal UMETA(DisplayName = "Normal"),
	EInfinite = 1 UMETA(DisplayName = "Infinite"),
	EUnvisible = 1 << 1 UMETA(DisplayName = "Unvisible"),
};

struct BuffAttribute
{
	// Buff name
	FName Name;

	// Buff type bitmask flag
	UINT BuffType = (uint8)EBuffType::ENormal;

	// Buff life time
	UINT LifeTime = 1;

	// Buff level
	UINT Level = 1;

	// Can this buff overlap
	bool CanOverlap = false;

	// Buff owner
	class AFBaseUnit* owner = nullptr;

	// Buff adder
	class AFBaseUnit* adder = nullptr;

	// Buff enable function
	BuffFunc EnableFunc = nullptr;

	// Buff tick function
	BuffFunc TickFunc = nullptr;

	// Buff disable function
	BuffFunc DisableFunc = nullptr;
};

/**
 * 
 */
UCLASS()
class FALLING2_API UFBuff : public UObject
{
	GENERATED_BODY()
	
private:
	// Attribute of this buff
	BuffAttribute Attribute;

	// Active state of this buff
	bool IsActive = true;


public:
	// Tick this buff
	void TickBuff();

	// Start this buff
	void StartBuff();

	// Enable this buff
	void EnableBuff();

	// Disable this buff
	void DisableBuff();

	// End this buff
	void EndBuff();

	// Initialzie this buff
	void Initialize(const BuffAttribute& attribute);

	// Reset this buff's lifetime
	void ResetBuff(UINT time);
	
	
};
