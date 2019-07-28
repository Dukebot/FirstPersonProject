// Fill out your copyright notice in the Description page of Project Settings.

#include "ShootComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Damageable.h"
//#include "Healeable.h"
#include "Pared.h"

/*
	Shoot:
		amount = amount of shoots (1 for normal, multuple for shootgun)
		shake = amount of lose in accuracy (0 = accurate shoot at center of the camera)
*/
void UShootComponent::Shoot(float amount, float shake)
{
	if (ammo <= 0) {
		UE_LOG(LogTemp, Warning, TEXT("No ammo"));
		return;
	}
	ammo--;
	UE_LOG(LogTemp, Warning, TEXT("Shooting"));

	//GetWorld()->SpawnActor<AActor>(bulletBP.Get(), GetComponentLocation(), GetComponentRotation());

	for (int i = 0; i < amount; i++) {
		SingleShoot(shake);
	}
}

void UShootComponent::SingleShoot(float shake)
{
	TArray<FHitResult> hits = MultiLineTracing(GetComponentLocation(), 1000000/*cm*/, shake);
	TArray<AActor*> hittedActors;
	float currentDamage = baseDamage;

	for (int i = 0; i < hits.Num(); i++) {
		FHitResult hitInfo = hits[i];
		AActor* hittedActor = hitInfo.GetActor();
		ApplyHit(hittedActor, hittedActors, currentDamage, hitInfo);
	}
}

TArray<FHitResult> UShootComponent::MultiLineTracing(FVector initialPoint, float distance, float shake)
{
	FVector shakeVector = FVector(FMath::RandRange(-shake, shake), FMath::RandRange(-shake, shake), FMath::RandRange(-shake, shake));
	FVector endPoint = initialPoint + GetForwardVector() * distance + shakeVector;

	TArray<FHitResult> hits;
	GetWorld()->LineTraceMultiByChannel(/*OUT*/hits, initialPoint, endPoint, ECC_GameTraceChannel3);
	DrawDebugLine(GetWorld(), initialPoint, endPoint, FColor::Red, false, 3);
	return hits;
}

void UShootComponent::ApplyHit(AActor * &hittedActor, TArray<AActor *> &hittedActors, float &currentDamage, FHitResult &hitInfo)
{
	if (hittedActor && !hittedActors.Contains(hittedActor)) {
		hittedActors.Add(hittedActor);

		IDamageable* damageable = Cast<IDamageable>(hittedActor);
		if (damageable) {
			damageable->Damage(currentDamage, hitInfo.BoneName);
		}

		APared* pared = Cast<APared>(hittedActor);
		if (pared) {
			currentDamage -= pared->danioAAbsorber;
		}
	}
}