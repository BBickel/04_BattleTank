// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
//#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;//TODO Should this really tick?

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* barrelToSet)
{
	barrel = barrelToSet;
}
void UTankAimingComponent::AimAt(FVector aimLocation, float launchSpeed)
{
	if (!barrel)
		return;

	FVector outLaunchVelocity = FVector(0.0f);
	FVector startLocation = barrel->GetSocketLocation(FName("Projectile"));

	bool didCalc = UGameplayStatics::SuggestProjectileVelocity(
		this, 
		outLaunchVelocity,
		startLocation, 
		aimLocation, 
		launchSpeed,
		false,//Default
		0,//Default
		0,//Default
		ESuggestProjVelocityTraceOption::DoNotTrace//Default (NOTE: Unreal bug present; requires this parameter despite being default)
	);

	if (didCalc == true)
	{
		auto aimDirection = outLaunchVelocity.GetSafeNormal();
		auto tankName = GetOwner()->GetName();
		//UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s"), *tankName, *aimDirection.ToString());
		MoveBarrelTowards(aimDirection);

		auto time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Aim Solution Found"), time);
	}
	else
	{
		auto time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: No Aim Solution Found"), time);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	//Work out the diff between current barrel rotation and aimDirection
	auto barrelRotator = barrel->GetForwardVector().Rotation();
	auto aimAsRotator = aimDirection.Rotation();
	auto deltaRotator = aimAsRotator - barrelRotator;

	barrel->Elevate(deltaRotator.Pitch);
}
