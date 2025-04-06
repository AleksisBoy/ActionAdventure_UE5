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

void AWeapon::Sheathe()
{
	if (!Data || bSheathed) return;

	bSheathed = true;
	UpdateLocationAndRotation();
}

void AWeapon::UnSheathe()
{
	if (!Data || !bSheathed) return;

	bSheathed = false;
	UpdateLocationAndRotation();
}

void AWeapon::UpdateLocationAndRotation()
{
	if (bSheathed)
	{
		SetActorRelativeLocation(Data->HandOffset);
		SetActorRelativeRotation(Data->HandRotation);
	}
	else
	{
		SetActorRelativeLocation(Data->ScabbardOffset);
		SetActorRelativeRotation(Data->ScabbardRotation);
	}
}

void AWeapon::SetData(UWeaponAsset* NewData)
{
	if (!NewData)
	{
		Data = nullptr;
		Mesh->SetStaticMesh(nullptr);
		return;
	}
	else if (Data == NewData) return;

	Data = NewData;
	Mesh->SetStaticMesh(Data->StaticMesh);
	Mesh->SetRelativeLocation(Data->MeshOffset);
	BoxComp->SetRelativeLocation(Data->BoxCompOffset);
	BoxComp->SetBoxExtent(Data->BoxCompExtent);
	UpdateLocationAndRotation();
}

