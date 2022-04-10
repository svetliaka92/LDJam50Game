#include "BaseShade.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerCharacter.h"
#include "ShadePatrolRoute.h"


ABaseShade::ABaseShade()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Darkness Radius"));
	SphereComponent->SetupAttachment(RootComponent);

	PatrolRouteComponent = CreateDefaultSubobject<UShadePatrolRoute>(TEXT("Patrol Path"));
}


void ABaseShade::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(SphereComponent))
	{
		SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseShade::OnSphereEntered);
		SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ABaseShade::OnSphereExited);
	}
}


void ABaseShade::OnSphereEntered(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	APlayerCharacter* PlayerInRange = Cast<APlayerCharacter>(OtherActor);
	if (IsValid(PlayerInRange))
	{
		PlayerInRange->AddShade(this);
	}
}


void ABaseShade::OnSphereExited(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	APlayerCharacter* PlayerInRange = Cast<APlayerCharacter>(OtherActor);
	if (IsValid(PlayerInRange))
	{
		PlayerInRange->RemoveShade(this);
	}
}
