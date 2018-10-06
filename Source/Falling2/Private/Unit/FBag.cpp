// Fill out your copyright notice in the Description page of Project Settings.

#include "FBag.h"
#include "FItemManager.h"
#include "FBaseUnit.h"

void UFBag::Initialize(AFBaseUnit * owner)
{
	Owner = owner;
}

bool UFBag::AddItem(const FName& name, UINT8 num)
{
	if (Items.Num() < MaxItemNum)
	{
		if (int* it = Items.Find(name))
		{
			*it += num;
		}
		else
		{
			Items.Add(name, num);
		}
		return true;
	}
	else
	{
		return false;
	}
}

void UFBag::UseItem(const FName & name)
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

void UFBag::RemoveItem(const FName & name)
{
	Items.Remove(name);
}
