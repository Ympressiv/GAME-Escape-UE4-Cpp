// Copyright - Jakub Michalewicz 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenTheDoor(float FPSLimit);
	void CloseTheDoor(float FPSLimit);
	void InitialValue();
	void SecurePressurePlate();
	void PressurePlate_OpenClose_Door(float FPSLimit);

private:
	float CurrentYaw;
	float InitialYaw;
	float OpenDoorYaw;
	float CloseDoorYaw;
	float CurrentTime = 0.f;
	float DoorLastOpened = 0.f;

	UPROPERTY(EditAnywhere)
	float OpenDoor_Angle = 74.f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 5.f;

	UPROPERTY(EditAnywhere)
	float DoorOpenSpeed = 0.5f;

	UPROPERTY(EditAnywhere)
	float DoorCloseSpeed = 0.5f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
	AActor* ObjectThatOpenDoor;
};
