// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"

void UTankTurret::RotateTurret(float RotationSpeed)
{
	auto CurrentRotation = RelativeRotation.Yaw;
	auto Rotation = RotationSpeed * DegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + Rotation;

	float Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: RotationYaw -> %f"), Time, RawNewRotation);

	SetRelativeRotation(FRotator(0.f, RawNewRotation, 0.f));

}




