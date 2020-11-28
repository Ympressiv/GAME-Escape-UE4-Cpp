// Copyright - Jakub Michalewicz 2020


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
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	OpenTheDoor(DeltaTime);
}
void UOpenDoor::OpenTheDoor(float FPSLimit)
{
	CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	OpenDoorYaw = FMath::Lerp(CurrentYaw, TargetYaw, FPSLimit * 0.5f);
	FRotator OpenDoor(0.f, OpenDoorYaw, 0.f);
	UE_LOG(LogTemp, Display, TEXT("%f"), OpenDoorYaw);
	GetOwner()->SetActorRotation(OpenDoor);

}
void UOpenDoor::InitialValue()
{
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	TargetYaw += InitialYaw;
}