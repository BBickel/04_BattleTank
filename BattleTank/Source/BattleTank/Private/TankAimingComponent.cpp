// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
//#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* barrelToSet)
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
		launchSpeed
		//false,//Default
		//0,//Default
		//0,//Default
		//ESuggestProjVelocityTraceOption::DoNotTrace//Default
	);

	if (didCalc == true)
	{
		auto aimDirection = outLaunchVelocity.GetSafeNormal();
		auto tankName = GetOwner()->GetName();
		//UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s"), *tankName, *aimDirection.ToString());
		MoveBarrelTowards(aimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	//Work out the diff between current barrel rotation and aimDirection
	auto barrelRotator = barrel->GetForwardVector().Rotation();
	auto aimAsRotator = aimDirection.Rotation();
	auto deltaRotator = aimAsRotator - barrelRotator;

	UE_LOG(LogTemp, Warning, TEXT("Aim Rotator: %s"), *aimAsRotator.ToString());

	//Move barrel the right amount this frame
	//Given a max elevation speed, and the frame time
}
