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
		GetControlledTank()->AimAt(hitLocation);
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
	FVector lookDirection;
	if (GetLookDirection(ScreenLocation, lookDirection))
	{
		//Line trace along that look direction and see what we hit (up to a max range)
		//UE_LOG(LogTemp, Warning, TEXT("Cam Direction: %s"), *lookDirection.ToString());
		bool didHit = GetLookVectorHitLocation(lookDirection, outHitLocation);

		//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *outHitLocation.ToString());
		return didHit;
	}

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& outLookDirection) const
{
	FVector cameraLocation;//Not needed
	//GetWorld()->GetFirstPlayerController()->DeprojectScreenPositionToWorld();//Don't get the First player controller here as we already are a TankPlayerController
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, cameraLocation, outLookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector lookDirection, FVector& outHitLocation) const
{
	FHitResult lineTraceHitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (lookDirection * LineTraceRange);
	bool didHit = GetWorld()->LineTraceSingleByChannel(
		lineTraceHitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility
	);

	if (didHit)
		outHitLocation = lineTraceHitResult.Location;
	else
		outHitLocation = FVector(0);//Safe value on false hit

	return didHit;
}
//My Attempt:
//bool ATankPlayerController::GetLookVectorHitLocation(FVector& outHitLocation) const
//{
//	FCollisionQueryParams lineCastQueryParams(FName(TEXT("")), false, GetOwner());
//	FHitResult lineTraceHitResult;
//	bool didHit = GetWorld()->LineTraceSingleByChannel(
//		lineTraceHitResult, 
//		GetReachLineStart(),
//		GetReachLineEnd(),
//		ECollisionChannel::ECC_Visibility, 
//		lineCastQueryParams,
//		FCollisionResponseParams(ECollisionResponse::ECR_Block));
//
//	outHitLocation = lineTraceHitResult.ImpactPoint;
//	
//	return didHit;
//}
//FVector ATankPlayerController::GetReachLineStart() const
//{
//	FVector playerViewPointLocation;
//	FRotator playerViewPointRotation;
//	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
//		OUT playerViewPointLocation,
//		OUT playerViewPointRotation
//	);
//
//	return playerViewPointLocation;
//}
//FVector ATankPlayerController::GetReachLineEnd() const
//{
//	FVector playerViewPointLocation;
//	FRotator playerViewPointRotation;
//	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
//		OUT playerViewPointLocation,
//		OUT playerViewPointRotation
//	);
//
//	FVector lineTraceEnd = playerViewPointLocation + playerViewPointRotation.Vector() * LineTraceRange;
//
//	return lineTraceEnd;
//}