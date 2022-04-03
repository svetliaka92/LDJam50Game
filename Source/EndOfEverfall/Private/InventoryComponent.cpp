// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"


void UInventoryComponent::Init()
{
	Crystals.Empty();
	Crystals.Add(ECrystalType::Small, 0);
	Crystals.Add(ECrystalType::Medium, 0);
	Crystals.Add(ECrystalType::Large, 0);
}


void UInventoryComponent::AddCrystal(ECrystalType CrystalType, int32 Quantity)
{
	if (!Crystals.Contains(CrystalType))
	{
		return;
	}

	Crystals[CrystalType] += Quantity;

	if (OnInventoryChanged.IsBound())
	{
		OnInventoryChanged.Broadcast(CrystalType, Crystals[CrystalType]);
	}
}


void UInventoryComponent::UseCrystal(ECrystalType CrystalType)
{
	if (!Crystals.Contains(CrystalType))
	{
		return;
	}

	if (Crystals[CrystalType] <= 0)
	{
		return;
	}

	Crystals[CrystalType]--;

	if (OnCrystalUsed.IsBound())
	{
		OnCrystalUsed.Broadcast(CrystalType);
	}

	if (OnInventoryChanged.IsBound())
	{
		OnInventoryChanged.Broadcast(CrystalType, Crystals[CrystalType]);
	}
}
