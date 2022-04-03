// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCrystal.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"


ABaseCrystal::ABaseCrystal()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(BoxComponent);
}
