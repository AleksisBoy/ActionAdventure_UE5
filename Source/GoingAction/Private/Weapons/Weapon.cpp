// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Weapon.h"	
#include "Components/BoxComponent.h"
#include "Data/WeaponAsset.h"
#include "Interfaces/Health.h"

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


void AWeapon::BeginPlay()
{
	if (!BoxComp->OnComponentBeginOverlap.IsAlreadyBound(this, &AWeapon::OnBoxBeginOverlap))
	{
		BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnBoxBeginOverlap);
	}

	if (!BoxComp->OnComponentEndOverlap.IsAlreadyBound(this, &AWeapon::OnBoxEndOverlap))
	{
		BoxComp->OnComponentEndOverlap.AddDynamic(this, &AWeapon::OnBoxEndOverlap);
	}
}

void AWeapon::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == Wielder || ActorsHit.Contains(OtherActor)) return;

	UE_LOG(LogTemp, Warning, TEXT("Begin Overlap with %s"), *OtherActor->GetName());
	ActorsHit.Add(OtherActor);

	if (IHealth* LivingEntity = Cast<IHealth>(OtherActor))
	{
		float DamageDealt = FMath::RandRange(Data->DamageRange.X, Data->DamageRange.Y);
		LivingEntity->GetHit(DamageDealt, SweepResult.Location);
	}
}

void AWeapon::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!ActorsHit.Contains(OtherActor)) return;

	UE_LOG(LogTemp, Log, TEXT("End Overlap with %s"), *OtherActor->GetName());
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::OnAttackStart()
{
	BoxComp->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	ActorsHit.Empty();
}

void AWeapon::OnAttackFinish()
{
	BoxComp->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
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

