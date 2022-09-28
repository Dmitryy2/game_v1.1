// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickUp.h"
#include "Components/StaticMeshComponent.h"
#include "../Pawns/PawnPlayerTank.h"
#include "Kismet/GameplayStatics.h"

// Устанавливает значения по умолчанию
AHealthPickUp::AHealthPickUp()
{
 	// Установите этого актера для вызова Tick() в каждом кадре.
	PrimaryActorTick.bCanEverTick = true;

	HealthPickUpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Health PickUp Mesh"));
	HealthPickUpMesh->OnComponentHit.AddDynamic(this, &AHealthPickUp::OnHit);
	RootComponent = HealthPickUpMesh;
}

// Вызывается при запуске игры или при появлении
void AHealthPickUp::BeginPlay()
{
	Super::BeginPlay();
	PlayerTank = Cast<APawnPlayerTank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
}

// Вызывал каждый кадр
void AHealthPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(FRotator(0.0f, GetWorld()->DeltaTimeSeconds * RotationSpeed, 0.0f));

}

void AHealthPickUp::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor == PlayerTank)
	{
		PlayerTank->RegainHealth(HealthValue);
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		Destroy();
	}
	else
	{
		return;
	}
}

