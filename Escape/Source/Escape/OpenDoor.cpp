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
	UE_LOG(LogType, Warning, TEXT("Current rotation of door is: %s"), *DoorRotation);
	float NewX_DoorRotation = CurrentY_DoorRotation.Yaw +90;
	FString NewY_DoorRotation = GetOwner()->GetActorRotation().ToString();
	FRotator New1Y_DoorRotation = GetOwner()->GetActorRotation();
	GetOwner()->SetActorRotation(New1Y_DoorRotation);
	UE_LOG(LogType, Warning, TEXT("+1 Current rotation of door is: %s"), *NewY_DoorRotation);

}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

