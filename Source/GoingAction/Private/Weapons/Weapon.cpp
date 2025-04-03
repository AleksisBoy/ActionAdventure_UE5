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

bool AWeapon::TrySetData(UWeaponAsset* NewData)
{
	// remake so that new actors dont need to be spawned. reuse one instance
	if (NewData == nullptr)
	{
		// destroy?
		return true;
	}
	if (NewData == Data) return true;

	if (NewData->WeaponActorClass == StaticClass())
	{
		Data = NewData;
	}

	return false;
}

