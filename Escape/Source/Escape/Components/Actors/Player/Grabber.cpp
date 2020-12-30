// Copyright - Jakub Michalewicz 2020

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandle();
	SetupInputComponent(); 
}
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
void UGrabber::Grab()
{
	GetFirstPhysicsBodyInReach();
	UE_LOG(LogType, Warning, TEXT("Action: Grab! You pressed: Grab button"));
}
void UGrabber::Drop()
{
	UE_LOG(LogType, Warning, TEXT("Action: Drop! You released: Grab button!"));
}
// Check the Physics Handle component
void UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		//Physcis handle component is found 
	}
	else
	{
		UE_LOG(LogType, Error, TEXT("PhysincsHandle component is not attached to %s!"), *GetOwner()->GetName());
	}
}
// Check the grabber is pressed or released
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Drop);
	}
}
FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FVector PlayerVievPoint_Location;
	FRotator PlayerVievPoint_Rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(
		OUT PlayerVievPoint_Location,
		OUT PlayerVievPoint_Rotation
	);
	FVector LineTraceEnd = PlayerVievPoint_Location + PlayerVievPoint_Rotation.Vector() * Reach;
	FHitResult OutHit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType
	(
		OUT OutHit,
		PlayerVievPoint_Location,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);
	AActor* HittingActor = OutHit.GetActor();
	if (HittingActor)
	{
		UE_LOG(LogType, Error, TEXT("Now You are loking at: %s"), *(HittingActor->GetName()));
	}

	return OutHit;
}