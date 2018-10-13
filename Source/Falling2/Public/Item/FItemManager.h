// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "FBaseItem.h"
#include "FBaseClip.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FItemManager.generated.h"

UCLASS()
class FALLING2_API AFItemManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFItemManager();

	static class AFBaseItem* CreateItem(AActor* caller, FName itemName);
	static FItemProperty* GetItemProperty(AActor* caller, const FName& name);
	static TArray<const FItemProperty*> GetItemsProperty(AActor* caller, TArray<FName*> names);
	static UINT8 GetMaxStackingNum(AActor* caller, const FName& name);
	static FClipListBP* GetClipProperty(AActor* caller, const FName& name);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	static AFItemManager* GetItemManager(AActor* caller);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	TMap<FName, FItemProperty> ItemProps;
	class UDataTable* WeaponTable = nullptr;
	class UDataTable* ClipTable = nullptr;
	
};
