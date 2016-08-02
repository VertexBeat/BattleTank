// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent * BarrelToSet)
{
	BarrelMesh = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation,float LaunchSpeed)
{
	if (!BarrelMesh) { return; };

	FVector OutLaunchVelocity;
	FVector StartLocation = BarrelMesh->GetSocketLocation(FName("Projectile"));

	// Calculate the OutLaunchVelocity

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto OurTankName = GetOwner()->GetName();
		MoveBarrelTowards(AimDirection);
	}
	
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Work-Out difference between current barrel-rotation and AimDirection

	auto BarrelRotator = BarrelMesh->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator %s"), *AimDirection.ToString());
	// Move the barrel the right amount this frame
	// Given a max elevation speed and the frame time
}

