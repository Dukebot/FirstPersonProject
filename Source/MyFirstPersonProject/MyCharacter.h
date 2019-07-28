#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

/* EXAMPLE CLASS for player of a first person game */

UCLASS()
class MYFIRSTPERSONPROJECT_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	//moving
	void MoveForward(float value);		
	void MoveRight  (float value);
	
	//looking
	void RotateYaw  (float value);		
	void RotatePitch(float value);
	
	//jumping
	void StartJump();					
	void StopJump ();
	
	//shooting
	FTimerHandle shootTimer;			
	void ShootTimer();
	void StartShoot();					
	void StopShoot ();
	
	FTimerHandle altShootTimer;			
	void AltShootTimer();
	void StartAltShoot();				
	void StopAltShoot ();
	
	void Heal(); //quitar del jugador

public:	

	//Componets
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) class UCameraComponent*		 camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) class USkeletalMeshComponent* arms;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) class USkeletalMeshComponent* weapon;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) class UHealthComponent*		 healthComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) class UShootComponent*		 shootComponent;

	UPROPERTY(EditAnywhere)	float rotationSpeed = 45; //Velocidad de rotación de la cámara
	
	//Constructor
	AMyCharacter(); 

	//Para bindear funcionalidades al input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
