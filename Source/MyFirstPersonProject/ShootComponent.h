// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ShootComponent.generated.h"

/*
	Important notes:
	This component must be attached to the object whose position will be the starting point of the shoot
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYFIRSTPERSONPROJECT_API UShootComponent : public USceneComponent
{
	GENERATED_BODY()

private:
	void SingleShoot(float shake);
	TArray<FHitResult> MultiLineTracing(FVector initialPoint, float distance, float shake);
	void ApplyHit(AActor * &hittedActor, TArray<AActor *> &hittedActors, float &currentDamage, FHitResult &hitInfo);

public:	
	UPROPERTY(EditAnywhere) int   ammo       = 10;
	UPROPERTY(EditAnyWhere) float baseDamage = 100;	
	//UPROPERTY(EditAnywhere) TSubclassOf<class AActor> bulletBP;

	void Shoot(float amount, float shake);

};
