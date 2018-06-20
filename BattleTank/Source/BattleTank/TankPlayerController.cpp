// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* thisTank = GetControlledTank();
	//if (&thisTank == NULL)
	if (!thisTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Tank Is NULL"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Tank: %s"), *(thisTank->GetName()));
	}
}
void ATankPlayerController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	AimTowardCrosshair();
}
ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardCrosshair()
{
	if (!GetControlledTank())
		return;

	//Get world location if linetrace through crosshair
	//If it hits the landscape
	//	Tell controlled tank to aim at this point
}