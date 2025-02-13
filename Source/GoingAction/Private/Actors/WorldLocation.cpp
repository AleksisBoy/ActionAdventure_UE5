// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/WorldLocation.h"
#include "Components/BoxComponent.h"

TArray<AWorldLocation*> AWorldLocation::Active;

AWorldLocation::AWorldLocation()
{
	PrimaryActorTick.bCanEverTick = true;

	BoundsBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Location Bounds"));
	RootComponent = BoundsBox;

	BoundsBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoundsBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	BoundsBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoundsBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AWorldLocation::BeginPlay()
{
	Super::BeginPlay();

	Active.AddUnique(this);

	BoundsBox->OnComponentBeginOverlap.AddDynamic(this, &AWorldLocation::OnOverlapBegin);
	BoundsBox->OnComponentEndOverlap.AddDynamic(this, &AWorldLocation::OnOverlapEnd);
}
void AWorldLocation::EndPlay(const EEndPlayReason::Type Reason)
{
	if (Active.Contains(this)) Active.Remove(this);
}
AWorldLocation* AWorldLocation::Get(ULocationData* Data)
{
	for (AWorldLocation* Instance : Active)
	{
		if (Instance->LocationData == Data)
		{
			return Instance;
		}
	}
	return nullptr;
}


void AWorldLocation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWorldLocation::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AWorldLocation::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

