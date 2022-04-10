#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShadePatrolRoute.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ENDOFEVERFALL_API UShadePatrolRoute : public UActorComponent
{
	GENERATED_BODY()

public:	
	UShadePatrolRoute();

	FORCEINLINE TArray<AActor*> GetPatrolPath() { return PatrolPath; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Path")
	TArray<AActor*> PatrolPath;
};
