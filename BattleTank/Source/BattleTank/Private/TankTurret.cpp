// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"

void UTankTurret::RotateTurret(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);
	auto CurrentRotation = RelativeRotation.Yaw;
	auto Rotation = RelativeSpeed * DegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + Rotation;

	SetRelativeRotation(FRotator(0.f, RawNewRotation, 0.f));

}




