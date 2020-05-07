// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoorV2.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEDEVTVGAMEJAM2020_API UOpenDoorV2 : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoorV2();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float TotalMassOfActors() const;
	void FindPressurePlate();

private:

	float CurrentYaw;
	float InitialYaw;

	UPROPERTY(EditAnywhere)
		float MassToOpenDoor = 50.f;

	UPROPERTY(EditAnywhere)
		float DoorOpenSpeed = 2.5f;

	UPROPERTY(EditAnywhere)
		float DoorClosedSpeed = 4.f;

	UPROPERTY(EditAnywhere)
		float OpenTargetYaw = -160.f;

	UPROPERTY(EditAnywhere)
		float CloseTargetYaw = 0.f;

	UPROPERTY(EditAnywhere)
		float DoorLastOpened = 0.f;

	UPROPERTY(EditAnywhere)
		float DoorClosedDelay = .5f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;
};
