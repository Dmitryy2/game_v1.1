// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "../GameModes/TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Устанавливает значения по умолчанию для свойств этого компонента
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

float UHealthComponent::CalculateHealthPercetage() const
{
	return Health/DefaultHealth;
}

void UHealthComponent::RegainHealth(float HealthValue)
{
	Health = FMath::Clamp(Health + HealthValue, Health, DefaultHealth);
}


// Вызывается, когда начинается игра
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = DefaultHealth;

	GameModeRef = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);

}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage == 0 || Health <= 0)
	{
		return;
	}

	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);

	if (Health <= 0)
	{
		if(GameModeRef)
		{
			GameModeRef->ActorDied(GetOwner());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Health Component has no reference to the GameMode"));
		}
	}
}

