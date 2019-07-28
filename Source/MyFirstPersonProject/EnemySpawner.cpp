// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemySpawner.h"
#include "Engine/World.h"

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	for (int i = 0; i < spawnPoints.Num(); i++) {
		AActor* spawnPoint = spawnPoints[i];

		int blueprintIndex = FMath::RandRange(0, blueprintsToSpawn.Num() - 1);
		TSubclassOf<AActor> blueprintToSpawn = blueprintsToSpawn[blueprintIndex];
		
		GetWorld()->SpawnActor<AActor>(blueprintToSpawn.Get(), spawnPoint->GetTransform());
	}
}

