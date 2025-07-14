// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"



UCLASS()
class SIMPLE_SHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties

	AGun();

	void PullTrigger(); // Method to handle pulling the trigger of the gun


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* GunMesh; // Mesh component for the gun

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Root; // Root component for the gun actor

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash; // Particle system for the muzzle flash effect

	UPROPERTY(EditAnywhere, Category = "Gun")
	float MaxRange = 1000.0f; // Range of the gun's fire

	UPROPERTY(EditAnywhere, Category = "Gun")
	UParticleSystem* ImpactEffect; // Particle system for the impact effect

	UPROPERTY(EditAnywhere, Category = "Gun")	
	float Damage = 10.0f; // Damage dealt by the gun

	bool GunTrace(FHitResult& Hit, FVector& FireDirection); // Method to perform a line trace for the gun

	AController* GetOwnerController() const; // Method to get the controller that owns this gun

	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound; // Sound played when the gun is fired

	UPROPERTY(EditAnywhere)
	USoundBase* ImpactSound; // Sound played when the gun hits something


};
