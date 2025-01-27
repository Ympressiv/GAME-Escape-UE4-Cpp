// Copyright - Jakub Michalewicz 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Grab();
	void Drop();
	void FindPhysicsHandle();
	void SetupInputComponent();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:
	float Reach = 100.f;
	FHitResult GetFirstPhysicsBodyInReach() const;
	FVector PlayerVievPoint_Stats() const;
	FVector GetPlayerWorldLocation() const;

	UPROPERTY()
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UPROPERTY()
	UInputComponent* InputComponent = nullptr;
};
