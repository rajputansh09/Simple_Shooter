// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShooterGameModeBase.h"





// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth; // Initialize the character's health to the maximum health value

	
	// Initialize the gun actor and attach it to the character's mesh
	Gun = GetWorld()->SpawnActor<AGun>(GunClass); // Spawn the gun actor from the specified class
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None); // Hide the bone named "weapon_r" on the character's mesh to prevent visual artifact
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket")); // Attach the gun to the character's mesh at the specified socket
	Gun->SetOwner(this); // Set the owner of the gun to this character
		
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward); // Bind the movement axes to the character's movement methods
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight); // Bind the movement axes to the character's movement methods
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AShooterCharacter::Turn);// Bind the movement axes to the character's movement methods
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AShooterCharacter::LookUp); // Bind the movement axes to the character's movement methods
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump); // Bind the Jump action to the character's Jump method
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpAtRate); // Bind the LookUpRate axis to the character's LookUpAtRate method
	PlayerInputComponent->BindAxis(TEXT("TurnRate"), this, &AShooterCharacter::TurnAtRate); // Bind the TurnRate axis to the character's TurnAtRate method	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AShooterCharacter::Fire); // Bind the Fire action to the character's Fire method}
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AShooterCharacter::Fire); // Bind the Fire action to the character's Fire method
}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
		
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply); // Ensure that the damage applied does not exceed the current health
	Health -= DamageToApply; // Reduce the character's health by the amount of damage applied
	UE_LOG(LogTemp, Warning, TEXT("Health Left: %f"), Health); // Log the remaining health to the console
	
	if (IsDead())
	{
		ASimpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>(); // Get the game mode instance from the world				
		if (GameMode != nullptr) // Check if the game mode instance is valid
		{
			GameMode->PawnKilled(this); // Call the PawnKilled method on the game mode to handle the character's death
		}
		
		DetachFromControllerPendingDestroy(); // Detach the character from the controller if it is dead
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision); // Disable	
	}
	return DamageToApply; // Return the amount of damage applied	
}


void AShooterCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value * MoveSpeed); // AddMovementInput is a method that applies movement input to the character
	}
}


void AShooterCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value * MoveSpeed); // AddMovementInput is a method that applies movement input to the character
	}
}


void AShooterCharacter::Turn(float Value)
{
	if (Value != 0.0f)
	{
		AddControllerYawInput(Value * TurnRate * GetWorld()->GetDeltaSeconds()); // AddControllerYawInput is a method that applies yaw input to the character
	}
}


void AShooterCharacter::LookUp(float Value)
{
	if (Value != 0.0f)
	{
		AddControllerPitchInput(Value * LookUpRate * GetWorld()->GetDeltaSeconds()); // AddControllerPitchInput is a method that applies pitch input to the character
	}
}


void AShooterCharacter::Jump()
{
	Super::Jump(); // Call the base class Jump method to handle jumping
}


void AShooterCharacter::LookUpAtRate(float Rate)
{
	// Calculate the new pitch based on the rate and the delta time
	AddControllerPitchInput(Rate * LookUpRate * GetWorld()->GetDeltaSeconds());
}


void AShooterCharacter::TurnAtRate(float Rate)
{
	// Calculate the new yaw based on the rate and the delta time
	AddControllerYawInput(Rate * TurnRate * GetWorld()->GetDeltaSeconds());
}


void AShooterCharacter::Fire()
{
	Gun->PullTrigger(); // Call the PullTrigger method on the gun instance to handle firing logic
}


bool AShooterCharacter::IsDead() const
{
	return Health <= 0.0f; // Check if the character's health is less than or equal to zero
}

float AShooterCharacter::GetHealthPercent() const
{
	return Health / MaxHealth; // Calculate the health percentage by dividing current health by maximum health
}
