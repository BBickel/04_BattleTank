// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//#include "Tank.h"

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;//Forward Declaration

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

	ATank* GetControlledTank() const;
	ATank* GetPlayerTank() const;
	void AimAtPlayer();
	virtual void Tick(float) override;

public:
	void BeginPlay() override;

	
};
