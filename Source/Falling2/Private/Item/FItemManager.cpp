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
					FWeaponListBP list = FWeaponListBP();
					if (FWeaponListBP* weaponlist = itemManager->WeaponTable->FindRow<FWeaponListBP>(itemName, TEXT("")))
					{
						list = *weaponlist;
					}
					weapon->InitializeWeapon(list.WeaponProperty);
					item = weapon;
					break;
				}
				case EItemType::EClip:
				{
					AFBaseClip* clip = world->SpawnActor<AFBaseClip>(caller->GetActorLocation(), caller->GetActorRotation());
					clip->InitializeItem(*itemProp);
					FClipListBP list = FClipListBP();
					if (FClipListBP* cliplist = itemManager->ClipTable->FindRow<FClipListBP>(itemName, TEXT("")))
					{
						list = *cliplist;
					}
					clip->InitilizeClip(list);
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

FClipListBP * AFItemManager::GetClipProperty(AActor * caller, const FName & name)
{
	FClipListBP* result = nullptr;
	if (AFItemManager* manager = GetItemManager(caller))
	{
		result = manager->ClipTable->FindRow<FClipListBP>(name, TEXT(""));
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

