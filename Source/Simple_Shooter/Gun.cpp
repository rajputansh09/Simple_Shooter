// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/Actor.h"
#include "Engine/DamageEvents.h"




// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the root component
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = Root;		

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	GunMesh->SetupAttachment(RootComponent); // Attach the gun mesh to the root component		
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, GunMesh, TEXT("MuzzleFlashSocket")); // Spawn the muzzle flash effect at the gun's muzzle socket
	
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, GunMesh, TEXT("MuzzleFlashSocket")); // Play the muzzle sound at the gun's muzzle socket

	FHitResult Hit; // Create a hit result to store the result of the line trace
	FVector FireDirection; // Create a vector to store the fire direction
	
	bool bSuccess = GunTrace(Hit, FireDirection); // Perform a line trace to check if the gun hits anything, storing the result in Hit and the fire direction in FireDirection

	if (bSuccess)
	{		

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, FireDirection.Rotation()); // Spawn the impact effect at the hit location with the fire direction rotation		
		
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.Location); // Play the impact sound at the hit location	

		AActor* HitActor = Hit.GetActor(); // Get the actor that was hit by the line trace
		
		if (HitActor != nullptr) // Check if the hit actor is valid
		{
			FPointDamageEvent DamageEvent(Damage, Hit, FireDirection, nullptr); // Create a point damage event with the damage amount, hit result, fire direction, and damage type
			AController* OwnerController = GetOwnerController(); // Get the controller that owns this gun
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this); // Apply damage to the hit actor
		}
	}
}


bool AGun::GunTrace(FHitResult& Hit, FVector& FireDirection)
{
	AController* OwnerController = GetOwnerController(); // Get the controller that owns this gun
	if (OwnerController == nullptr)
	{
		return false; // If the owner controller is not valid, exit the function
	}
	
	FVector Location;
	FRotator Rotation;
	
	OwnerController->GetPlayerViewPoint(Location, Rotation); // Get the player's view point location and rotation
	
	FireDirection = -Rotation.Vector(); // Get the fire direction as the negative of the rotation vector
	// This is because the line trace is in the opposite direction of the player's view point

	FVector End = Location + Rotation.Vector() * MaxRange; // Calculate the end point of the line trace, extending
	// the line trace from the player's view point in the direction they are looking, up to the maximum range

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner()); // Ignore the owner pawn in the line trace
	CollisionParams.AddIgnoredActor(this); // Ignore this gun actor in the line trace

	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, CollisionParams); // Perform the line trace and store the result in Hit
	
}

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
	{
		return nullptr; // If the owner is not a pawn, return nullptr
	}
	return OwnerPawn->GetController(); // Return the controller that owns this gun
	
}