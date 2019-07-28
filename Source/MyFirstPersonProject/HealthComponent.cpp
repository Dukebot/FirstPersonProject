// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"
#include "GameFramework/Actor.h"

UHealthComponent::UHealthComponent()
{	
}

void UHealthComponent::TakeDamage(float amount, FName boneName)
{
	if (damageMap.Contains(boneName)) {
		float damagePercetage = damageMap[boneName];
		UE_LOG(LogTemp, Warning, TEXT("Bone name %s"), *boneName.ToString());
		UE_LOG(LogTemp, Warning, TEXT("Damage %f"), damagePercetage);

		float totalDamage = amount * damagePercetage;
		life -= totalDamage;
		UE_LOG(LogTemp, Warning, TEXT("Enemy life %f"), life);

		if (life <= 0) { GetOwner()->Destroy(); }
	}
}

void UHealthComponent::Heal(float amount)
{
	life += amount;
	if (life > maxLife) life = maxLife;
}
