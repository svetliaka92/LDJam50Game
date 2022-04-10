// Fill out your copyright notice in the Description page of Project Settings.


#include "LightPillar.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerCharacter.h"


ALightPillar::ALightPillar()
{
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
	
	if (IsValid(LightRange))
	{
		LightRange->OnComponentBeginOverlap.AddDynamic(this, &ALightPillar::OnSphereEntered);
		LightRange->OnComponentEndOverlap.AddDynamic(this, &ALightPillar::OnSphereExited);
	}

	bCanBeDrained = LightAmount > 0;
	OnCanDrainChanged();
}


void ALightPillar::DrainLightAmount(float Value)
{
	LightAmount = FMath::Max(0.0f, LightAmount - Value);
	OnLightAmountChanged();

	if (LightAmount <= 0)
	{
		bCanBeDrained = false;
		OnCanDrainChanged();
	}
}


void ALightPillar::OnSphereEntered(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	APlayerCharacter* PlayerInRange = Cast<APlayerCharacter>(OtherActor);
	if (IsValid(PlayerInRange))
	{
		PlayerInRange->AddPillar(this);
	}
}


void ALightPillar::OnSphereExited(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	APlayerCharacter* PlayerInRange = Cast<APlayerCharacter>(OtherActor);
	if (IsValid(PlayerInRange))
	{
		PlayerInRange->RemovePillar(this);
	}
}
