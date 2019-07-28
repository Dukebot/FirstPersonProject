// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"

//#include "MyEnemy.h"
//#include "Damageable.h"
//#include "Pared.h"
#include "healeable.h"

//Componentes
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "HealthComponent.h"
#include "ShootComponent.h"

//#include <string>

//Constructor

AMyCharacter::AMyCharacter()
{
	//Creating and initializing components
	{
		camera = CreateDefaultSubobject<UCameraComponent>("Camera"); 
		camera->bUsePawnControlRotation = true;			//Enable camera rotation at Z axis with mouse
		camera->SetupAttachment(GetRootComponent());
		
		arms = CreateDefaultSubobject<USkeletalMeshComponent>("Arms");
		arms->SetupAttachment(camera);				
		
		weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
		weapon->SetupAttachment(arms, "GripPoint");
		
		healthComponent = CreateDefaultSubobject<UHealthComponent>("HeathComponent");
		
		shootComponent = CreateDefaultSubobject<UShootComponent>("ShootComponent");
		shootComponent->SetupAttachment(camera);

		UE_LOG(LogTemp, Warning, TEXT("Parent name of camera %s"), *camera->GetAttachParent()->GetName());
		UE_LOG(LogTemp, Warning, TEXT("Parent name of shoot component %s"), *shootComponent->GetAttachParent()->GetName());
	}
}

//Bindeamos las funcionalidades al input

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::RotateYaw);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyCharacter::RotatePitch);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AMyCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &AMyCharacter::StopJump);

	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &AMyCharacter::StartShoot);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, this, &AMyCharacter::StopShoot);

	PlayerInputComponent->BindAction("AltFire", EInputEvent::IE_Pressed, this, &AMyCharacter::StartAltShoot);
	PlayerInputComponent->BindAction("AltFire", EInputEvent::IE_Released, this, &AMyCharacter::StopAltShoot);
}

//Movimiento

void AMyCharacter::MoveForward(float value) 
{
	AddMovementInput(GetActorForwardVector(), value);
}

void AMyCharacter::MoveRight(float value) 
{
	AddMovementInput(GetActorRightVector(), value);
}

//Mirar alrededor

void AMyCharacter::RotateYaw(float value) 
{
	AddControllerYawInput(value * rotationSpeed * GetWorld()->GetDeltaSeconds());
}

void AMyCharacter::RotatePitch(float value) 
{
	// Para que funcione hay que tildar en Unreal "Use camera pawn rotation"
	AddControllerPitchInput(value * rotationSpeed* GetWorld()->GetDeltaSeconds());
}

//Saltar

void AMyCharacter::StartJump() 
{ 
	Jump(); 
}

void AMyCharacter::StopJump() 
{ 
	StopJumping(); 
}

//Disparo primario

void AMyCharacter::StartShoot()
{
	shootComponent->Shoot(1, 0);
	GetWorldTimerManager().SetTimer(shootTimer, this, &AMyCharacter::ShootTimer,0.267f /*Lo que dura la animación*/, true);
}

void AMyCharacter::StopShoot()
{
	GetWorldTimerManager().ClearTimer(shootTimer);
}

void AMyCharacter::ShootTimer()
{
	shootComponent->Shoot(1, 0);
}

//Disparo secundario

void AMyCharacter::StartAltShoot()
{
	GetWorldTimerManager().SetTimer(altShootTimer, this, &AMyCharacter::AltShootTimer, 0.267f /*Lo que dura la animación*/, true);
}

void AMyCharacter::StopAltShoot()
{
	GetWorldTimerManager().ClearTimer(altShootTimer);
}

void AMyCharacter::AltShootTimer()
{
	Heal();
}

//curar

void AMyCharacter::Heal()
{
	//UE_LOG(LogTemp, Warning, TEXT("Healing disabled"));
	UE_LOG(LogTemp, Warning, TEXT("Healing"));

	float distance = 1000000; //cm
	FVector initialPoint = camera->GetComponentLocation();
	FVector endPoint = camera->GetComponentLocation() + camera->GetForwardVector() * distance;

	//Line tracing
	FHitResult hitInfo;
	GetWorld()->LineTraceSingleByChannel(hitInfo, initialPoint, endPoint, ECC_GameTraceChannel3);
	DrawDebugLine(GetWorld(), initialPoint, endPoint, FColor::Green, false, 3);

	AActor* hittedActor = hitInfo.GetActor();
	if (hittedActor) {
		IHealeable* healeable = Cast<IHealeable>(hittedActor);
		if (healeable) { healeable->Heal(30); }
	}
}