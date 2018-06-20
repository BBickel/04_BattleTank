// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Tank.h"

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

public:
	virtual void BeginPlay() override;//Leading 'virtual' keyword says if we derive a class from this one, we can override this method again
	virtual void Tick(float deltaTime) override;//parameter name here is optional

private:
	void AimTowardCrosshair();//Start the tank moving the barrel so the shot will hit the cross hair intersects the world
	ATank* GetControlledTank() const;
};
