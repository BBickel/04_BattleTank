// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Tank.h"//This is actually not a good thing; should include in cpp instead, and use forward declarations

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"//Must be the LAST include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333f;
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.0f;//10km or 1 million centimeters


public:
	virtual void BeginPlay() override;//Leading 'virtual' keyword says if we derive a class from this one, we can override this method again
	virtual void Tick(float deltaTime) override;//parameter name here is optional

private:
	void AimTowardCrosshair();//Start the tank moving the barrel so the shot will hit the cross hair intersects the world
	ATank* GetControlledTank() const;
	bool GetSightRayHitLocation(FVector &outHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& outLookDirection) const;
	bool GetLookVectorHitLocation(FVector lookDirection, FVector& outHitLocation) const;
};
