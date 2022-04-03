// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightPillar.generated.h"

class USphereComponent;
class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class ENDOFEVERFALL_API ALightPillar : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightPillar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* LightRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pillar")
	float LightAmount = 5000.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
