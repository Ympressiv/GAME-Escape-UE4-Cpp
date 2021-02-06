// Copyright - Jakub Michalewicz 2020

#include "OpenDoor.h"
#include "Components/AudioComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

#define OUT

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
	SecureAudioComponent();
}
void UOpenDoor::SecurePressurePlate()
{
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has OpenDoor component on it but no pressureplate set!"), *GetOwner()->GetName());
	}
}
void UOpenDoor::SecureAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (!AudioComponent)
	{
		UE_LOG(LogType, Error, TEXT("SC_OpenDoor audio component is not attached to %s."), *GetOwner()->GetName());
	}
}

// Initial value of yaw door rotation to known where was starting point
void UOpenDoor::InitialValue()
{
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	OpenDoor_Angle += InitialYaw;
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!PressurePlate) {return;}
	PressurePlate_OpenClose_Door(DeltaTime);
	CurrentTime = GetWorld()->GetTimeSeconds();
}
void UOpenDoor::PressurePlate_OpenClose_Door(float FPSLimit)
{
	if (!PressurePlate) {return;}
	if (PressurePlate && TotalMassOfActors() > MassToOpenDoor)
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
float UOpenDoor::TotalMassOfActors() const
{
	float TotalMass = 0.f;
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) {return TotalMass;}
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	for (AActor* MassOfActors:OverlappingActors)
	{
		TotalMass += MassOfActors->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}
void UOpenDoor::OpenTheDoor(float FPSLimit)
{
	CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	OpenDoorYaw = FMath::Lerp(CurrentYaw, OpenDoor_Angle, FPSLimit * DoorOpenSpeed);
	FRotator OpenDoor(0.f, OpenDoorYaw, 0.f);
	GetOwner()->SetActorRotation(OpenDoor); 
	bCloseDoorSound = false;
	if (!AudioComponent) {return;}
	if (!bOpenDoorSound)
	{
		AudioComponent->Play();
		bOpenDoorSound = true;
	}
}
void UOpenDoor::CloseTheDoor(float FPSLimit)
{
	CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	CloseDoorYaw = FMath::Lerp(CurrentYaw, InitialYaw, FPSLimit * DoorCloseSpeed);
	FRotator CloseDoor(0.f, CloseDoorYaw, 0.f);
	GetOwner()->SetActorRotation(CloseDoor);
	bOpenDoorSound = false;
	if (!AudioComponent) {return;}
	if (!bCloseDoorSound)
	{
		AudioComponent->Play();
		bCloseDoorSound = true;
	}
}