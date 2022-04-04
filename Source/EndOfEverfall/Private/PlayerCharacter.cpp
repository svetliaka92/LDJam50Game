// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "LightMeterComponent.h"
#include "PlayerLightMeter.h"
#include "InventoryComponent.h"
#include "InventoryUI.h"
#include "BaseCrystal.h"
#include "HelperUI.h"
#include "LightPillar.h"


APlayerCharacter::APlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 0.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	LightMeter = CreateDefaultSubobject<ULightMeterComponent>(TEXT("Light meter"));
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
}


void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(LightMeterUIClass))
	{
		LightMeterUI = CreateWidget<UPlayerLightMeter>(GetWorld(), LightMeterUIClass);
		if (IsValid(LightMeterUI))
		{
			LightMeterUI->Init(LightMeter);
			LightMeterUI->AddToViewport();
		}
	}

	if (IsValid(Inventory))
	{
		Inventory->Init();
		Inventory->CrystalUsed().AddUObject(this, &APlayerCharacter::OnCrystalUsed);
	}
	
	if (IsValid(InventoryUIClass))
	{
		InventoryUI = CreateWidget<UInventoryUI>(GetWorld(), InventoryUIClass);
		if (IsValid(InventoryUI))
		{
			InventoryUI->Init(Inventory);
			InventoryUI->AddToViewport();
		}
	}

	if (IsValid(HelperUIClass))
	{
		HelperUI = CreateWidget<UHelperUI>(GetWorld(), HelperUIClass);
		if (HelperUI)
		{
			HelperUI->AddToViewport();
		}
	}
}


void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// enable help UI
	if (IsValid(HelperUI))
	{
		HelperUI->SetClickHelperVisible(CheckForCrystal());
	}

	ProcessPillarsInRange(DeltaTime);
}


void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (!IsValid(PlayerInputComponent))
	{
		return;
	}

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("UseSmallCrystal", IE_Pressed, this, &APlayerCharacter::UseSmallCrystal);
	PlayerInputComponent->BindAction("UseMediumCrystal", IE_Pressed, this, &APlayerCharacter::UseMediumCrystal);
	PlayerInputComponent->BindAction("UseLargeCrystal", IE_Pressed, this, &APlayerCharacter::UseLargeCrystal);

	PlayerInputComponent->BindAction("LeftClick", IE_Pressed, this, &APlayerCharacter::TakeCrystal);
}


void APlayerCharacter::AddPillar(ALightPillar* PillarToAdd)
{
	LightPillars.Add(PillarToAdd);
}


void APlayerCharacter::RemovePillar(ALightPillar* PillarToRemove)
{
	if (LightPillars.Contains(PillarToRemove))
	{
		LightPillars.Remove(PillarToRemove);
	}
}


void APlayerCharacter::ProcessPillarsInRange(float DeltaTime)
{
	int32 LightPillarsNum = LightPillars.Num();

	if (IsValid(LightMeter))
	{
		LightMeter->SetIsInLight(LightPillarsNum > 0);
	}

	if (LightPillarsNum == 0)
	{
		return;
	}

	for (ALightPillar* Pillar : LightPillars)
	{
		if (!Pillar->CanBeDrained())
		{
			continue;
		}

		float DrainAmount = Pillar->GetDrainRate() * DeltaTime;
		Pillar->DrainLightAmount(DrainAmount);
		if (IsValid(LightMeter))
		{
			LightMeter->AddLightAmount(DrainAmount);
		}
	}
}


void APlayerCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}


void APlayerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}


void APlayerCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}


void APlayerCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}


void APlayerCharacter::UseSmallCrystal()
{
	UseCrystal(ECrystalType::Small);
}


void APlayerCharacter::UseMediumCrystal()
{
	UseCrystal(ECrystalType::Medium);
}


void APlayerCharacter::UseLargeCrystal()
{
	UseCrystal(ECrystalType::Large);
}


void APlayerCharacter::UseCrystal(ECrystalType CrystalType)
{
	if (!IsValid(Inventory))
	{
		return;
	}

	Inventory->UseCrystal(CrystalType);
}


void APlayerCharacter::OnCrystalUsed(ECrystalType CrystalType)
{
	if (!IsValid(LightMeter))
	{
		return;
	}

	int32 LightAmount = 0;
	switch (CrystalType)
	{
	case ECrystalType::Small:
		LightAmount = 15;
		break;
	case ECrystalType::Medium:
		LightAmount = 30;
		break;
	case ECrystalType::Large:
		LightAmount = 50;
		break;
	}

	LightMeter->AddLightAmount(LightAmount);
}


bool APlayerCharacter::CheckForCrystal()
{
	return IsValid(GetFirstCrystalInReach().GetActor());
}


void APlayerCharacter::TakeCrystal()
{
	ABaseCrystal* Crystal = Cast<ABaseCrystal>(GetFirstCrystalInReach().GetActor());
	if (IsValid(Crystal))
	{
		Inventory->AddCrystal(Crystal->GetCrystalType(), 1);
		Crystal->ConditionalBeginDestroy();
	}
}


FHitResult APlayerCharacter::GetFirstCrystalInReach() const
{
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		return Hit;
	}

	World->LineTraceSingleByChannel(
		Hit,
		GetPlayerWorldPosition(),
		GetPlayerReach(),
		ECollisionChannel::ECC_GameTraceChannel1,
		TraceParams
	);

	return Hit;
}


FVector APlayerCharacter::GetPlayerWorldPosition() const
{
	FVector PlayerrViewPointLocation = GetOwner()->GetActorLocation();
	FRotator PlayerViewPointRotation = GetOwner()->GetActorRotation();

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerrViewPointLocation,
		PlayerViewPointRotation
	);

	return PlayerrViewPointLocation;
}


FVector APlayerCharacter::GetPlayerReach() const
{
	FVector PlayerViewPointLocation = GetOwner()->GetActorLocation();
	FRotator PlayerViewPointRotation = GetOwner()->GetActorRotation();

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerViewPointLocation,
		PlayerViewPointRotation
	);

	return PlayerViewPointLocation + Reach * PlayerViewPointRotation.Vector();
}
