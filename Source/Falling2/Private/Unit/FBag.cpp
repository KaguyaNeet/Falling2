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
		TArray<int*> result;
		Items.MultiFindPointer(name, result);
		UINT8 maxNum = AFItemManager::GetMaxStackingNum(Owner, name);
		bool needAdd = true;
		for (int i = 0; i < result.Num(); ++i)
		{
			if (nullptr != result[i] && *result[i] < maxNum)
			{
				++(result[i]);
				needAdd = false;
				break;
			}
		}
		if (needAdd)
		{
			if (Items.Num() < MaxItemNum)
			{
				Items.Add(name, 1);
				return true;
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
		if (int* itemNum = Items.Find(name))
		{
			if (AFBaseItem* item = AFItemManager::CreateItem(Owner, name))
			{
				item->OnUse();
				if ((--(*itemNum)) <= 0)
				{
					RemoveItem(name);
				}
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
			umgItem.Count = it.Value;
			UMGItems.Add(umgItem);
		}
	}
}

