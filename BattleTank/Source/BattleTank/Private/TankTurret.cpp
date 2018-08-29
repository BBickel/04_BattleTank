// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"


void UTankTurret::Rotate(float RelativeSpeed)
{
	//Move barrel the right amount this frame
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto TurnChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewYaw = RelativeRotation.Yaw + TurnChange;
	/*if (RawNewYaw > 180)
		RawNewYaw -= 180;
	else if (RawNewYaw <= -180)
		RawNewYaw += 180;*/
	SetRelativeRotation(FRotator(0, RawNewYaw, 0));
}
