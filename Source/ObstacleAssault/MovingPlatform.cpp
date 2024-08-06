// Fill out your copyright notice in the Description page of Project Settings.


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

	_startLocation = GetActorLocation();

	_name = GetName();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float deltaTime)
{
	FVector location = GetActorLocation();
	location += _movement * deltaTime;
	SetActorLocation(location);

	float distance = FVector::Distance(_startLocation, location);

	if (distance >= _maxDistance)
	{
		float overshoot = distance -_maxDistance;
		UE_LOG(LogTemp, Display, TEXT("%s has overshot by %f"), *_name, overshoot);

		FVector normalMovement = _movement.GetSafeNormal();
		_startLocation += normalMovement * _maxDistance;
		SetActorLocation(_startLocation);

		_movement*= -1;
	}
}
