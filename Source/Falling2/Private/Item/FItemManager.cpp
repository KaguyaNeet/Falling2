// Fill out your copyright notice in the Description page of Project Settings.

#include "FItemManager.h"
#include "FGameInstance.h"
#include "FBaseWeapon.h"
#include "FBaseClip.h"

#include "Public/UObject/ConstructorHelpers.h"

// Sets default values
AFItemManager::AFItemManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UDataTable> WeaponData(TEXT("DataTable'/Game/Blueprints/DataTable/WeaponDT.WeaponDT'"));
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

	ConstructorHelpers::FObjectFinder<UDataTable> ClipData(TEXT("DataTable'/Game/Blueprints/DataTable/ClipDT.ClipDT'"));
	if (ClipData.Succeeded())
	{
		ClipTable = ClipData.Object;
		TArray<FClipListBP*> clipLists;
		ClipTable->GetAllRows<FClipListBP>(TEXT(""), clipLists);
		for (int i = 0; i < clipLists.Num(); i++)
		{
			ItemProps.Add(clipLists[i]->ItemProperty.ItemInternalName, clipLists[i]->ItemProperty);
		}
	}

}

AFBaseItem * AFItemManager::CreateItem(AActor* caller, FName itemName)
{
	if (AFItemManager* itemManager = GetItemManager(caller))
	{
		if (FItemProperty* itemProp = itemManager->ItemProps.Find(itemName))
		{
			UWorld* world = caller->GetWorld();
			AFBaseItem* item = nullptr;
			switch (itemProp->ItemType)
			{
				case EItemType::EWeapon:
				{
					AFBaseWeapon* weapon = world->SpawnActor<AFBaseWeapon>(caller->GetActorLocation(), caller->GetActorRotation());
					weapon->InitializeItem(*itemProp);
					FWeaponListBP* weaponlist = itemManager->WeaponTable->FindRow<FWeaponListBP>(itemName, TEXT(""));
					weapon->InitializeWeapon(weaponlist->WeaponProperty);
					item = weapon;
					break;
				}
				case EItemType::EClip:
				{
					AFBaseClip* clip = world->SpawnActor<AFBaseClip>(caller->GetActorLocation(), caller->GetActorRotation());
					clip->InitializeItem(*itemProp);
					FClipListBP* cliplist = itemManager->ClipTable->FindRow<FClipListBP>(itemName, TEXT(""));
					clip->InitilizeClip(*cliplist);
					item = clip;
					break;
				}
				default:break;
			}
			return item;
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

TArray<const FItemProperty*> AFItemManager::GetItemsProperty(AActor * caller, TArray<FName*> names)
{
	TArray<const FItemProperty*> result;
	if (AFItemManager* manager = GetItemManager(caller))
	{
		for (int i = 0; i < names.Num(); ++i)
		{
			if (FItemProperty* prop = manager->ItemProps.Find(*names[i]))
			{
				result.Add(prop);
			}
		}
	}
	return result;
}

UINT8 AFItemManager::GetMaxStackingNum(AActor * caller, const FName & name)
{
	UINT8 result = 1;
	if (AFItemManager* manager = GetItemManager(caller))
	{
		if (FItemProperty* prop = manager->ItemProps.Find(name))
		{
			result = prop->MaxStackingNum;
		}
	}
	return result;
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

