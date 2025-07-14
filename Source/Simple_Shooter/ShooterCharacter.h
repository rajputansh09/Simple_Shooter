// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"


UCLASS()
class SIMPLE_SHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

	UFUNCTION(BlueprintPure)
	bool IsDead() const; // Check if the character is dead

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const; // Get the health percentage of the character
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void Fire();


private:

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void Jump();
	void LookUpAtRate(float Rate);
	void TurnAtRate(float Rate);

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 10.0f; // Speed at which the character moves

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float LookUpRate = 10.0f;

	UPROPERTY(EditAnywhere)
	float RotationRate = 10.0f; // Rate at which the character rotates
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AGun> GunClass; // Class of the gun to be spawned
	
	UPROPERTY()		
	class AGun* Gun; // Instance of the gun actor


	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100.0f; // Maximum health of the gun

	UPROPERTY(VisibleAnywhere)
	float Health; // Current health of the gun


};




