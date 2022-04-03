// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CrystalType.h"
#include "BaseCrystal.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class ENDOFEVERFALL_API ABaseCrystal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseCrystal();

	FORCEINLINE ECrystalType GetCrystalType() const { return CrystalType; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBoxComponent* BoxComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Crystal)
	ECrystalType CrystalType = ECrystalType::Small;

};
