// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	//ATank* thisTank = GetControlledTank();
	//if (!thisTank)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("AI Tank Is NULL"));
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("AIController Tank: %s"), *(thisTank->GetName()));
	//}
	ATank* playerTank = GetPlayerTank();
	if (!playerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Tank did not find Player"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Found Player Target Tank: %s"), *(playerTank->GetName()));
	}
}
//void ATankAIController::Tick(float deltaTime)
//{
//
//}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
ATank* ATankAIController::GetPlayerTank() const
{
	//return Cast<ATank>(GetWorld()->GetFirstPlayerController());

	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn)
		return nullptr;
	return Cast<ATank>(PlayerPawn);
}

//void ATankAIController::AimAtPlayer()
//{
//
//}