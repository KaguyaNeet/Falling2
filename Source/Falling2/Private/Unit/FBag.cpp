// Fill out your copyright notice in the Description page of Project Settings.

#include "FBag.h"
#include "FItemManager.h"
#include "FBaseUnit.h"

void AFBag::Initialize(AFBaseUnit * owner)
{
	Owner = owner;
}

bool AFBag::AddItem(const FName& name)
{
	if (nullptr != Owner)
	{
		TArray<ItemInfo*> result;
		Items.MultiFindPointer(name, result);
		UINT8 maxNum = AFItemManager::GetMaxStackingNum(Owner, name);
		bool needAdd = true;
		for (int i = 0; i < result.Num(); ++i)
		{
			if (nullptr != result[i] && result[i]->Value < maxNum)
			{
				++(result[i]->Value);
				needAdd = false;
				break;
			}
		}
		if (needAdd)
		{
			if (Items.Num() < MaxItemNum)
			{
				if (FItemProperty* item = AFItemManager::GetItemProperty(this, name))
				{
					ItemInfo iteminfo = ItemInfo(*item, 1);
					Items.Add(name, iteminfo);
					return true;
				}
				return false;
				
			}
			else
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

void AFBag::UseItem(const FName & name)
{
	if (nullptr != Owner)
	{
		if (ItemInfo* item = Items.Find(name))
		{
			if ((--(item->Value)) <= 0)
			{
				RemoveItem(name);
			}
		}
	}
}

void AFBag::RemoveItem(const FName & name)
{
	Items.Remove(name);
}

void AFBag::UpdateUMGItem()
{
	if (nullptr != Owner)
	{
		for (auto it : Items)
		{
			UMGItems.Empty();
			FUMGItemProperty umgItem;
			umgItem.ItemProperty = *AFItemManager::GetItemProperty(Owner, it.Key);
			umgItem.Count = it.Value.Value;
			UMGItems.Add(umgItem);
		}
	}
}

FClipListBP AFBag::GetClip(const FClipListBP & clip)
{
	FClipListBP result = FClipListBP();
	result = clip;
	if (ItemInfo* item = Items.Find(clip.ItemProperty.ItemInternalName))
	{
		result.CurrentBulletCount = clip.MaxBulletCount;
		UseItem(clip.ItemProperty.ItemInternalName);
		return result;
	}
	for (auto it : Items)
	{
		if (EItemType::EClip == it.Value.Key.ItemType)
		{
			if (FClipListBP* list = AFItemManager::GetClipProperty(this, it.Value.Key.ItemInternalName))
			{
				if (clip.WeaponType == list->WeaponType)
				{
					result = *list;
					result.CurrentBulletCount = result.MaxBulletCount;
					UseItem(list->ItemProperty.ItemInternalName);
					return result;
				}
			}

		}
	}
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("No suitable Clip!"));
	return result;
}

