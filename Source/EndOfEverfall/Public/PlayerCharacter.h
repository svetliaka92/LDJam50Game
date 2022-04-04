// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CrystalType.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ULightMeterComponent;
class UPlayerLightMeter;
class UInventoryComponent;
class UInventoryUI;
class UHelperUI;
class ALightPillar;

UCLASS()
class ENDOFEVERFALL_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerCharacter();

	void AddPillar(ALightPillar* PillarToAdd);
	void RemovePillar(ALightPillar* PillarToRemove);

protected:
	virtual void Tick(float DeltaTime) override;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light meter", meta = (AllowPrivateAccess = "true"))
	ULightMeterComponent* LightMeter = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Light meter", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UPlayerLightMeter> LightMeterUIClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	UInventoryComponent* Inventory = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TSubclassOf<UInventoryUI> InventoryUIClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interacting")
	TSubclassOf<UHelperUI> HelperUIClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate = 45.0f;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate = 45.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Reach")
	float Reach = 3.0f;

	UPlayerLightMeter* LightMeterUI = nullptr;
	UInventoryUI* InventoryUI = nullptr;
	UHelperUI* HelperUI = nullptr;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	void UseSmallCrystal();
	void UseMediumCrystal();
	void UseLargeCrystal();

	UFUNCTION()
	void UseCrystal(ECrystalType CrystalType);

	UFUNCTION()
	void TakeCrystal();

	void OnCrystalUsed(ECrystalType CrystalType);

	bool CheckForCrystal();

private:
	FHitResult GetFirstCrystalInReach() const;
	FVector GetPlayerWorldPosition() const;
	FVector GetPlayerReach() const;

	TArray<ALightPillar*> LightPillars;

	void ProcessPillarsInRange(float DeltaTime);

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

};
