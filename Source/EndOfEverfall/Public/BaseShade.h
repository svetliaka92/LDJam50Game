// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseShade.generated.h"

UCLASS()
class ENDOFEVERFALL_API ABaseShade : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseShade();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	class USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Patrol")
	class UShadePatrolRoute* PatrolRouteComponent;

public:	
	/**
	 * The amount of light that will be removed from the player per second
	 * while in the volume of the shade
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shade")
	float LightDecayPerSecond = 2.0f;

private:
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
