// Fill out your copyright notice in the Description page of Project Settings.

#include "MyEnemy.h"
#include "HealthComponent.h"

AMyEnemy::AMyEnemy()
{
	healthComponent = CreateDefaultSubobject<UHealthComponent>("HeathComponent");
}

void AMyEnemy::Damage(float amount, FName boneName)
{
	healthComponent->TakeDamage(amount, boneName);
}

void AMyEnemy::Heal(float amount)
{
	healthComponent->Heal(amount);
}
