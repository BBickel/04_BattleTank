// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* thisTank = GetControlledTank();
	//if (&thisTank == NULL)
	if (!thisTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Tank Is NULL"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController Tank: %s"), *(thisTank->GetName()));
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}