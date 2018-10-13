// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine/DataTable.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FBaseItem.generated.h"


UENUM(BlueprintType)
enum class EItemType : uint8
{
	EWeapon UMETA(DisplayName = "Weapon"),
	EThrowable UMETA(DisplayName = "Throwable"),
	EClip UMETA(DisplayName = "Clip"),
};

UENUM(BlueprintType)
enum class EItemQuality : uint8
{
	ENormal = 1 UMETA(DisplayName = "Normal"),
};

USTRUCT()
struct FItemProperty : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
public:
	//Internal name of this item, Developer use.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FName ItemInternalName;
	//Name of this item, Player see.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FName ItemName;
	//Description of this item, Player see.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString ItemDescription;
	//Icon of this item, Show on UI.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UTexture2D* Icon;
	//Type of this item.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		EItemType ItemType = EItemType::EWeapon;
	//The maximum number of stacks of this item in the bag.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int MaxStackingNum = 1;
	//Quality of this item.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		EItemQuality ItemQuality = EItemQuality::ENormal;

};

USTRUCT()
struct FUMGItemProperty : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
		FItemProperty ItemProperty;
	UPROPERTY(BlueprintReadOnly)
		int Count = 1;
};

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

	void InitializeItem(const FItemProperty& itemProperty);

	UFUNCTION(BlueprintCallable)
		virtual void OnUse(){ }

public:
	class AFBaseUnit* ItemOwner = nullptr;
	bool isPicked = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class USphereComponent* Trigger;

	UPROPERTY(EditAnywhere, Category = "ItemProperty")
		int MaxStackingNum = 10;

	UPROPERTY(BlueprintReadOnly)
		FItemProperty ItemProperty;
};
