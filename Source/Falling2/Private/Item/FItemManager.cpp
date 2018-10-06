// Fill out your copyright notice in the Description page of Project Settings.

#include "FItemManager.h"
#include "FGameInstance.h"
#include "FBaseWeapon.h"

#include "Public/UObject/ConstructorHelpers.h"

// Sets default values
AFItemManager::AFItemManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UDataTable> WeaponData(TEXT(""));
	if (WeaponData.Succeeded())
	{
		WeaponTable = WeaponData.Object;
		TArray<FWeaponListBP*> weaponLists;
		WeaponTable->GetAllRows<FWeaponListBP>(TEXT(""), weaponLists);
		for (int i = 0; i < weaponLists.Num(); i++)
		{
			ItemProps.Add(weaponLists[i]->ItemProperty.ItemInternalName, weaponLists[i]->ItemProperty);
		}
	}

}

AFBaseItem * AFItemManager::CreateItem(AActor* caller, FName itemName)
{
	if (AFItemManager* itemManager = GetItemManager(caller))
	{
		if (FItemProperty* itemProp = itemManager->ItemProps.Find(itemName))
		{
			switch (itemProp->ItemType)
			{
				case EItemType::EWeapon:break;
			}
			return nullptr;
		}
		else
		{
			return nullptr;
		}
		//else
		//{
		//	UWorld* world = itemManager->GetWorld();
		//	FWeaponList* weapon = itemManager->WeaponTable->FindRow<FWeaponList>(itemName, TEXT(""));
		//	if (nullptr != weapon)
		//	{
		//		AFBaseItem* item = nullptr;
		//		switch (weapon->WeaponType)
		//		{
		//			case EWeaponType::ERifle:item = world->SpawnActor<AFRifle>(FVector::ZeroVector, FRotator::ZeroRotator); break;
		//			case EWeaponType::EShotgun:item = world->SpawnActor<AFShotgun>(FVector::ZeroVector, FRotator::ZeroRotator); break;
		//			case EWeaponType::ESniper:item = world->SpawnActor<AFSniper>(FVector::ZeroVector, FRotator::ZeroRotator); break;
		//			case EWeaponType::EGrenade:item = world->SpawnActor<AFSpawner>(FVector::ZeroVector, FRotator::ZeroRotator); break;
		//			case EWeaponType::ELaser:item = world->SpawnActor<AFSpawner>(FVector::ZeroVector, FRotator::ZeroRotator); break;
		//			case EWeaponType::ERocket:item = world->SpawnActor<AFSpawner>(FVector::ZeroVector, FRotator::ZeroRotator); break;
		//			default:item = world->SpawnActor<AFRifle>(FVector::ZeroVector, FRotator::ZeroRotator); break;
		//		}
		//		return item;
		//	}
		//}
	}
	return nullptr;
}

FItemProperty * AFItemManager::GetItemProperty(AActor* caller, const FName & name)
{
	if (AFItemManager* manager = GetItemManager(caller))
	{
		return manager->ItemProps.Find(name);
	}
	return nullptr;
}

// Called when the game starts or when spawned
void AFItemManager::BeginPlay()
{
	Super::BeginPlay();
	
}

AFItemManager * AFItemManager::GetItemManager(AActor* caller)
{
	AFItemManager* itemManager = nullptr;
	if (UFGameInstance* gameInstance = Cast<UFGameInstance>(caller->GetGameInstance()))
	{
		itemManager = gameInstance->GetItemManager();
	}
	return itemManager;
}

// Called every frame
void AFItemManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

