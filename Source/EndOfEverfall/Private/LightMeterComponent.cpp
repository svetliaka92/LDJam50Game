// Fill out your copyright notice in the Description page of Project Settings.


#include "LightMeterComponent.h"


ULightMeterComponent::ULightMeterComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void ULightMeterComponent::BeginPlay()
{
	Super::BeginPlay();

	LightAmount = MaxLightAmount;
}


void ULightMeterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsInLight)
	{
		DecayLightAmount(DeltaTime);
		if (LightAmount <= 0)
		{
			// trigger ending
		}
	}
}


void ULightMeterComponent::AddLightAmount(float Value)
{
	LightAmount = FMath::Min(MaxLightAmount, LightAmount + Value);
}


void ULightMeterComponent::DecayLightAmount(float Delta)
{
	LightAmount -= BaseDecayingSpeed * Delta;

	if (OnLightMeterChangedDelegate.IsBound())
	{
		OnLightMeterChangedDelegate.Broadcast(LightAmount);
	}
}
