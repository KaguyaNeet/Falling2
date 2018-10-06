// Fill out your copyright notice in the Description page of Project Settings.

#include "FBag.h"

bool UFBag::AddItem(const FName& item, UINT8 num)
{
	if (Items.Num() < MaxItemNum)
	{
		if (int* it = Items.Find(item))
		{
			*it += num;
		}
		else
		{
			Items.Add(item, num);
		}
		return true;
	}
	else
	{
		return false;
	}
}
