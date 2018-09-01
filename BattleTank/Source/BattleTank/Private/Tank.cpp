// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;//Improve efficiency by stopping tick

	//No need to protect pointers as added at construction
	tankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}
void ATank::SetBarrelReference(UTankBarrel* barrelToSet)
{
	tankAimingComponent->SetBarrelReference(barrelToSet);
	Barrel = barrelToSet;
}
void ATank::SetTurretReference(UTankTurret* turretToSet)
{
	tankAimingComponent->SetTurretReference(turretToSet);
}
// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector hitLocation)
{
	if(tankAimingComponent)
		tankAimingComponent->AimAt(hitLocation, LaunchSpeed);
}

void ATank::FireCannon()
{
	if (!Barrel)
		return;

	//Spawn a projectile at the socket location on the barrel
	FVector socketLocation = Barrel->GetSocketLocation("Projectile");
	FRotator socketRotation = Barrel->GetSocketRotation("Projectile");
	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(*ProjectileBlueprint, socketLocation, socketRotation);

	projectile->LaunchProjectile(LaunchSpeed);
}