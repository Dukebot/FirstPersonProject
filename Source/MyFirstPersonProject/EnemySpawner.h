// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class MYFIRSTPERSONPROJECT_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere) TArray<AActor*> spawnPoints;
	UPROPERTY(EditAnywhere) TArray<TSubclassOf<AActor>> blueprintsToSpawn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
