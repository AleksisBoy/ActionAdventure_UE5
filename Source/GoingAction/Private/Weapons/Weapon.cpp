// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Weapon.h"	
#include "Components/BoxComponent.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
}


void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::Equip()
{
}

void AWeapon::Dequip()
{
}

