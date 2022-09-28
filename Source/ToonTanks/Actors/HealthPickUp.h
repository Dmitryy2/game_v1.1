// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthPickUp.generated.h"

class UStaticMeshComponent;
class APawnPlayerTank;

UCLASS()
class TOONTANKS_API AHealthPickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Устанавливает значения по умолчанию для свойств этого субъекта
	AHealthPickUp();
	// Вызывал каждый кадр
	virtual void Tick(float DeltaTime) override;

protected:
	// Вызывается при запуске игры или при появлении
	virtual void BeginPlay() override;


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* HealthPickUpMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = true))
	float HealthValue = 50.0f;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* HitSound;

	float RotationSpeed = 100.0f;

	APawnPlayerTank* PlayerTank;

};
