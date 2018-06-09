// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));

	ATank* thisTank = GetControlledTank();
	//if (&thisTank == NULL)
	if (!thisTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Tank Is NULL"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play: %s"), *(thisTank->GetName()));
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}