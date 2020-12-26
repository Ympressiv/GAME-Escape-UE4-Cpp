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

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
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


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(
		OUT PlayerVievPoint_Location,
		OUT PlayerVievPoint_Rotation
	);
	FVector LineTraceEnd = PlayerVievPoint_Location + PlayerVievPoint_Rotation.Vector() * Reach;
	DrawDebugLine
	(
		GetWorld(),
		PlayerVievPoint_Location,
		LineTraceEnd,
		FColor (0,255,0),
		false,
		0.f,
		0.f,
		5.f
	);
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
			UE_LOG(LogTemp, Error, TEXT("Now You are loking at: %s"), *(HittingActor->GetName()));
		}
}

