// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"



void UTankTrack::SetThrottle(float throttle)
{
	auto name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s throttle at %f"), *name, throttle);

	//TODO Clamp actual throttle value so player can't overdrive
}
