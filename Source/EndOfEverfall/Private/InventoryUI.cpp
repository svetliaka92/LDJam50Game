// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryUI.h"
#include "InventoryComponent.h"


void UInventoryUI::Init(UInventoryComponent* Inventory)
{
	if (!IsValid(Inventory))
	{
		return;
	}

	Inventory->InventoryChanged().AddUObject(this, &UInventoryUI::OnInventoryChanged);
}


void UInventoryUI::OnInventoryChanged(ECrystalType CrystalType, int32 NewQuantity)
{
	InventoryChangedEvent(CrystalType, NewQuantity);
}
