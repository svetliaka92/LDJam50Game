// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerLightMeter.h"
#include "LightMeterComponent.h"
#include "Components/ProgressBar.h"


void UPlayerLightMeter::Init(ULightMeterComponent* LightMeter)
{
	if (!IsValid(LightMeter))
	{
		return;
	}

	LightMeter->LightMeterChanged().AddUObject(this, &UPlayerLightMeter::UpdateLightMeterUI);
	MaxLight = LightMeter->GetMaxLightAmount();
}


void UPlayerLightMeter::UpdateLightMeterUI(float Value)
{
	if (!IsValid(LightBar))
	{
		return;
	}

	LightBar->SetPercent(Value / MaxLight);
}
