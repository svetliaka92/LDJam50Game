// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CrystalType.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ENDOFEVERFALL_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	void Init();

	void AddCrystal(ECrystalType CrystalType, int32 Quantity);
	void UseCrystal(ECrystalType CrystalType);

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInventoryChanged, ECrystalType, int32);
	FOnInventoryChanged& InventoryChanged() { return OnInventoryChanged; }

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnCrystalUsed, ECrystalType);
	FOnCrystalUsed& CrystalUsed() { return OnCrystalUsed; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TMap<ECrystalType, int32> Crystals;

	FOnInventoryChanged OnInventoryChanged;
	FOnCrystalUsed OnCrystalUsed;
};
