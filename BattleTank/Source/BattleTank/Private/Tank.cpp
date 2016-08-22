// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
}

float ATank::TakeDamage(float Damage, struct FDamageEvent const & DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	int32 DamagePoints = FPlatformMath::RoundToInt(ActualDamage);
	CurrentHealth -= DamagePoints;
	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
		UE_LOG(LogTemp, Warning, TEXT("%d health left!!!"), CurrentHealth)
	}
	UE_LOG(LogTemp, Warning, TEXT("Is dead!"))

	return ActualDamage;
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}
