// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Damageable.h"
#include "Healeable.h"
#include "MyEnemy.generated.h"

UCLASS()
class MYFIRSTPERSONPROJECT_API AMyEnemy : public ACharacter, public IDamageable, public IHealeable
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) class UHealthComponent* healthComponent;

	AMyEnemy();
	void Damage(float amount, FName boneName) override;
	void Heal(float amount) override;
};
