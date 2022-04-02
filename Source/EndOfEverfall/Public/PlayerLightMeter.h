// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerLightMeter.generated.h"

class ULightMeterComponent;
class UProgressBar;

UCLASS()
class ENDOFEVERFALL_API UPlayerLightMeter : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Init(ULightMeterComponent* LightMeter);
	void UpdateLightMeterUI(float Value);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidgetOptional))
	UProgressBar* LightBar = nullptr;

	float MaxLight = 0.0f;
};
