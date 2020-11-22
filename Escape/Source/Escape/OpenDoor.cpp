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

	float MyFloat = 90.f;
	FString DoorRotation = GetOwner()->GetActorRotation().ToString();
	UE_LOG(LogType, Warning, TEXT("Rotation of door is: %s"), *DoorRotation);

	FRotator CurrentY_DoorRotation = GetOwner()->GetActorRotation();
	FRotator CurrentY_DoorRotation{ 0.f,90.f,0.f };
	FRotator* Y_Door = &CurrentY_DoorRotation;
	Y_Door-> ToString();
	UE_LOG(LogType, Warning, TEXT("+1 Current rotation of door is: %s"), **Y_Door);

}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

