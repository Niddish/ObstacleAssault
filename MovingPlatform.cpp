// Fill out your copyright notice in the Description page of Project Settings.
#include <stddef.h>

#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
StartPosition = GetActorLocation();
	
	// UE_LOG(LogTemp, Display, TEXT("Configured Moved Distance: %f"), DistanceTraveled);

	FString Name = GetName();

	UE_LOG(LogTemp, Display, TEXT("BeginPlay: %s"), *Name);

}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);

}

void AMovingPlatform::RotatePlatform(float DeltaTime){
	UE_LOG(LogTemp, Display, TEXT("%s Rotating..."), *GetName());
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	if (ShouldPlatformReturn())
	{
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartPosition = StartPosition + MoveDirection * MovedDistance;
		SetActorLocation(StartPosition);
		PlatformVelocity = -PlatformVelocity;
	}
	else
	{
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
		SetActorLocation(CurrentLocation);
	}
}



bool AMovingPlatform::ShouldPlatformReturn(){
	return GetDistanceMoved() > MovedDistance;
}

float AMovingPlatform::GetDistanceMoved(){
	return FVector::Dist(StartPosition, GetActorLocation());
}




