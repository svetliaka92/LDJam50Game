// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightPillar.generated.h"

class USphereComponent;
class UBoxComponent;
class UStaticMeshComponent;
class APlayerCharacter;

UCLASS()
class ENDOFEVERFALL_API ALightPillar : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightPillar();

	FORCEINLINE float GetDrainRate() { return LightDrainRate; }
	FORCEINLINE bool CanBeDrained() { return bCanBeDrained; }
	
	void DrainLightAmount(float Value);

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pillar")
	float MaxLightAmount = 5000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pillar")
	float LightDrainRate = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pillar")
	bool bCanBeDrained = true;

	UFUNCTION(BlueprintImplementableEvent)
	void OnCanDrainChanged();

	UFUNCTION(BlueprintImplementableEvent)
	void OnLightAmountChanged();

	UFUNCTION()
	void OnSphereEntered(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnSphereExited(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
};
