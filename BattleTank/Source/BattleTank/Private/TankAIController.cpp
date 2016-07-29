// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController not possessing a tank!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController possessing: %s"), *ControlledTank->GetName());
	}

	auto TargetTank = GetPlayerControlledTank();
	if (!TargetTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Target not found!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Target: %s"), *TargetTank->GetName());
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerControlledTank() const
{
	ATank* Target = nullptr;
	Target = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!Target) { return nullptr; };
	return Target;
}


