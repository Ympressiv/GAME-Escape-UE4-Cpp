// Copyright - Jakub Michalewicz 2020

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Check the Physics Handle component
void UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
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
FVector UGrabber::GetPlayerWorldLocation() const
{
	FVector PlayerVievPoint_Location;
	FRotator PlayerVievPoint_Rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(
		OUT PlayerVievPoint_Location,
		OUT PlayerVievPoint_Rotation
	);
	return PlayerVievPoint_Location;
}
FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FHitResult OutHit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType
	(
		OUT OutHit,
		GetPlayerWorldLocation(),
		PlayerVievPoint_Stats(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);
	return OutHit;
}
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandle();
	SetupInputComponent(); 
}

// If actor is hit, then attached Physics Handle
FVector UGrabber::PlayerVievPoint_Stats() const
{
	FVector PlayerVievPoint_Location;
	FRotator PlayerVievPoint_Rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(
		OUT PlayerVievPoint_Location,
		OUT PlayerVievPoint_Rotation
	);
	return PlayerVievPoint_Location + PlayerVievPoint_Rotation.Vector() * Reach;
}
void UGrabber::Grab()
{
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	AActor* ActorThatWasHitted = HitResult.GetActor();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	if (ActorThatWasHitted)
	{	
		if (!PhysicsHandle) {return;}
		PhysicsHandle->GrabComponentAtLocation
		(
			ComponentToGrab,
			NAME_None,
			PlayerVievPoint_Stats()
		);
	}
}
void UGrabber::Drop()
{
	if (!PhysicsHandle) { return; }
	PhysicsHandle->ReleaseComponent();
}

// If Physics Handle is attached then do grab or release action
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!PhysicsHandle) { return; }
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(PlayerVievPoint_Stats());
	}
}

