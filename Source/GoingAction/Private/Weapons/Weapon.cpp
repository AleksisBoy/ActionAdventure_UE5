// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Weapon.h"	
#include "Components/BoxComponent.h"
#include "Data/WeaponAsset.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	HandleComp = CreateDefaultSubobject<USceneComponent>(TEXT("Handle"));
	RootComponent = HandleComp;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxComp->SetupAttachment(RootComponent);
}


void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::Equip()
{
	SetActorRelativeRotation(BaseRotation);
}

void AWeapon::Dequip()
{
	SetActorRelativeRotation(ScabbardRotation);
}

