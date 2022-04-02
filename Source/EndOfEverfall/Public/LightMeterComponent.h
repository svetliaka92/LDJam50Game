// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LightMeterComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ENDOFEVERFALL_API ULightMeterComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULightMeterComponent();

	FORCEINLINE float GetLightAmount() { return LightAmount; }
	FORCEINLINE float GetMaxLightAmount() { return MaxLightAmount; }

	void AddLightAmount(float Value);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LightComponent")
		float BaseDecayingSpeed = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LightComponent")
		float StartLightAmount = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LightComponent")
		float MaxLightAmount = 100.0f;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnLightMeterChanged, float);
	FOnLightMeterChanged& LightMeterChanged() { return OnLightMeterChangedDelegate; }

private:
	FOnLightMeterChanged OnLightMeterChangedDelegate;
	void DecayLightAmount(float Delta);

	float LightAmount = 0.0f;
	bool bIsInLight = false;
	
};
