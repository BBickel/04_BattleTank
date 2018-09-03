// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}
void ATankAIController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	auto playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (playerTank)
	{
		ATank* controlledTank = Cast<ATank>(GetPawn());
		//TODO Move towards the player

		//Aim towards the player
		controlledTank->AimAt(playerTank->GetActorLocation());

		controlledTank->FireCannon();
	}
}