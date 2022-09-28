// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"

class APawnTank;
class UTankMovementComponent;
class UAimingComponent;

/**
 * 
 */

UCLASS()
class TOONTANKS_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
	
public:

	//Вызывал каждый кадр
	virtual void Tick(float DeltaTime) override;
	
	void SetPlayerEnabledState(bool SetPlayerEnabled);



protected:
	//Вызывается, когда начинается игра
	virtual void BeginPlay() override;

private:


	APawnTank* PlayerTank;
	float ForwardMovementDirection = 0.0f;
	float RotationMovementDirection = 0.0f;

	void CalculateMoveInput(float Value);
	void CalculateRotationInput(float Value);
	void Fire();

	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HealthScreenClass;

	UTankMovementComponent* PawnMovementComponent;
	UAimingComponent* AimingComponent;
};
