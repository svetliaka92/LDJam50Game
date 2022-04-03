// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CrystalType.h"
#include "InventoryUI.generated.h"

class UInventoryComponent;

UCLASS()
class ENDOFEVERFALL_API UInventoryUI : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init(UInventoryComponent* Inventory);

protected:
	void OnInventoryChanged(ECrystalType CrystalType, int32 NewQuantity);

	UFUNCTION(BlueprintImplementableEvent)
	void InventoryChangedEvent(ECrystalType CrystalType, int32 NewQuantity);
};
