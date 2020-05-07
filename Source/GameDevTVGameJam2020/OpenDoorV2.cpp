// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoorV2.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFrameWork/Actor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoorV2::UOpenDoorV2()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoorV2::BeginPlay()
{
	Super::BeginPlay();

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	OpenTargetYaw += CurrentYaw;
	CloseTargetYaw -= CurrentYaw;

	FindPressurePlate();

	// ...

}

// Called every frame
void UOpenDoorV2::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TotalMassOfActors() > MassToOpenDoor)
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if (GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorClosedDelay)
		{
			CloseDoor(DeltaTime);
		}
	}

	// ...
}

void UOpenDoorV2::FindPressurePlate()
{
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s Component has the OpenDoor Component but no PressPlate set."), *GetOwner()->GetName());
	}
}

void UOpenDoorV2::OpenDoor(float DeltaTime)
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, OpenTargetYaw, DeltaTime, DoorOpenSpeed);
	FRotator OpenDoor = GetOwner()->GetActorRotation();
	OpenDoor.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(OpenDoor);
}

void UOpenDoorV2::CloseDoor(float DeltaTime)
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, CloseTargetYaw, DeltaTime, DoorClosedSpeed);
	FRotator CloseDoor = GetOwner()->GetActorRotation();
	CloseDoor.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(CloseDoor);
}

float UOpenDoorV2::TotalMassOfActors() const
{
	float TotalMass = 0.f;

	// Find All Overlapping Actors
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s is on pressplate"), *Actor->GetName())
	}

	return TotalMass;
}