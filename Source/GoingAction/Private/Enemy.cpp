// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

TArray<AEnemy*> AEnemy::Active;

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	Active.AddUnique(this);
}

void AEnemy::EndPlay(const EEndPlayReason::Type Reason)
{
	if (Active.Contains(this)) Active.Remove(this);
}

void AEnemy::GetHit_Implementation(float Damage, FVector HitLocation)
{
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


