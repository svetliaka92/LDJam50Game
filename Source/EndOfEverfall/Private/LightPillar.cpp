// Fill out your copyright notice in the Description page of Project Settings.


#include "LightPillar.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"


ALightPillar::ALightPillar()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;

	LightRange = CreateDefaultSubobject<USphereComponent>(TEXT("LightRange"));
	LightRange->SetupAttachment(BoxComponent);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(BoxComponent);
}


void ALightPillar::BeginPlay()
{
	Super::BeginPlay();
	
}


void ALightPillar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// cast for player from the light range
	// if player in radius drain light from pillar and give to player
}

