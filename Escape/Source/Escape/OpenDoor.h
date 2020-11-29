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

private:
	float CurrentYaw;
	float InitialYaw;
	float OpenDoorYaw;
	float CloseDoorYaw;

	UPROPERTY(EditAnywhere)
	float TargetYaw = 74.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
	AActor* ObjectThatOpenDoor;
		
};
