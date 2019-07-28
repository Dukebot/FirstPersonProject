// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYFIRSTPERSONPROJECT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnyWhere) TMap<FName, float> damageMap;	//mapa<nombreHueso, multiplicadorDaño>
	UPROPERTY(EditAnywhere) float maxLife = 100;
	UPROPERTY(EditAnywhere) float life = maxLife;
	
	UHealthComponent();
	void TakeDamage(float amount, FName boneName);
	void Heal(float amount);
};
