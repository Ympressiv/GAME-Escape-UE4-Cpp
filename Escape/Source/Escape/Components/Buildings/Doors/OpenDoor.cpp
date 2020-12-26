// Copyright - Jakub Michalewicz 2020

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialValue();
	SecurePressurePlate();
	ObjectThatOpenDoor = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CurrentTime = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Display, TEXT("Current time in game is: %f"), CurrentTime);

	PressurePlate_OpenClose_Door(DeltaTime);
}

void UOpenDoor::OpenTheDoor(float FPSLimit)
{
	CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	OpenDoorYaw = FMath::Lerp(CurrentYaw, OpenDoor_Angle, FPSLimit * DoorOpenSpeed);
	FRotator OpenDoor(0.f, OpenDoorYaw, 0.f);
	GetOwner()->SetActorRotation(OpenDoor);
}
void UOpenDoor::CloseTheDoor(float FPSLimit)
{
	CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	CloseDoorYaw = FMath::Lerp(CurrentYaw, InitialYaw, FPSLimit * DoorCloseSpeed);
	FRotator CloseDoor(0.f, CloseDoorYaw, 0.f);
	GetOwner()->SetActorRotation(CloseDoor);
}
void UOpenDoor::InitialValue()
{
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	OpenDoor_Angle += InitialYaw;
}
void UOpenDoor::SecurePressurePlate()
{
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has OpenDoor component on it but no pressureplate set!"), *GetOwner()->GetName());
	}
}
void UOpenDoor::PressurePlate_OpenClose_Door(float FPSLimit)
{
	if (PressurePlate && PressurePlate->IsOverlappingActor(ObjectThatOpenDoor))
	{
		OpenTheDoor(FPSLimit);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if (CurrentTime >= DoorLastOpened + DoorCloseDelay)
		{
			CloseTheDoor(FPSLimit);
		}
	}
}