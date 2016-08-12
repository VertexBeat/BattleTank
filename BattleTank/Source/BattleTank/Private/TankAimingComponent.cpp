// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	// So that first fire is after initial reload
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if ((FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	// TODO Handle aiming and locked states
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	BarrelMesh = BarrelToSet;
	TurretMesh = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(BarrelMesh)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = BarrelMesh->GetSocketLocation(FName("Projectile"));

	// Calculate the OutLaunchVelocity

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam,
		TArray<AActor*>(),
		false // DebugDraw
	);

	if (bHaveAimSolution)
	{
		UE_LOG(LogTemp, Warning, TEXT("DEBUG AimAt"))
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto OurTankName = GetOwner()->GetName();
		MoveBarrelTowards(AimDirection);
		RotateTurret(AimDirection);
	}
	else
	{
		float Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: No aim solve found"), Time);
		MoveBarrelTowards(FVector(0));
		RotateTurret(FVector(0));
	}
	
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// if Barrel is not set or Turret is not set, throw an assertion
	if (!ensure(BarrelMesh) || !ensure(TurretMesh)) { return; }

	// Work-Out difference between current barrel-rotation and AimDirection

	auto BarrelRotator = BarrelMesh->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	BarrelMesh->Elevate(DeltaRotator.Pitch); // TODO remove magic number
}

void UTankAimingComponent::RotateTurret(FVector AimDirection)
{
	auto TurretRotator = TurretMesh->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - TurretRotator;
	TurretMesh->RotateTurret(DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
{

	if (FiringState != EFiringState::Reloading)
	{
		// throw assert when BarrelMesh and ProjectileBlueprint not set

		if (!ensure(BarrelMesh) && !ensure(ProjectileBlueprint)) { return; }
		// Spawn a projectile
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			BarrelMesh->GetSocketLocation(FName("Projectile")),
			BarrelMesh->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}





