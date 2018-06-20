// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "Engine/World.h"


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

	FVector hitLocation;//Out parameter
	bool didHit = GetSightRayHitLocation(hitLocation);
	if (didHit == true)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *hitLocation.ToString());
		//TODO Tell controlled tank to aim at this point
	}

}
//bool ATankPlayerController::GetSightRayHitLocation(FVector &outHitLocation) const
//{
//	//Linetrace out
//	FHitResult hit;
//	//Get world location of linetrace through crosshair
//	FVector start;
//	FVector end;
//	ECollisionChannel collisionChannel = ECollisionChannel::ECC_EngineTraceChannel1;
//	bool didHit = GetWorld()->LineTraceSingleByChannel(hit, start, end, collisionChannel);
//	//Return true if it hits something, and assign the hit point
//	if (didHit == true)//If it hits the landscape
//	{
//		outHitLocation = FVector(1.0);
//		//outHitLocation = hit.ImpactPoint;
//		return true;
//	}
//	//False if not
//	outHitLocation = FVector(-1.0);
//	return false;
//}
bool ATankPlayerController::GetSightRayHitLocation(FVector &outHitLocation) const
{
	//Find the crosshair position
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);
	FVector2D ScreenLocation = FVector2D(viewportSizeX * CrossHairXLocation, viewportSizeY * CrossHairYLocation);
	//UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString());

	//De-project the screen position of the crosshair to a world direction
	//Line trace along that look direction and see what we hit (up to a max range)


	return true;
}