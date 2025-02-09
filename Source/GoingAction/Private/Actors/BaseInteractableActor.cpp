// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseInteractableActor.h"
#include "Components/BoxComponent.h"
#include "GoingAction/GoingActionCharacter.h"

TArray<ABaseInteractableActor*> ABaseInteractableActor::Overlapping;

ABaseInteractableActor::ABaseInteractableActor()
{
	PrimaryActorTick.bCanEverTick = true;

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Box"));
	RootComponent = InteractionBox;

	InteractionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	InteractionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	InteractionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABaseInteractableActor::Interact_Implementation(AGoingActionCharacter* Character)
{
	UE_LOG(LogTemp, Warning, TEXT("Interacted with %s"), *GetName());
}

void ABaseInteractableActor::BeginPlay()
{
	Super::BeginPlay();

	InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseInteractableActor::OnOverlapBegin);
	InteractionBox->OnComponentEndOverlap.AddDynamic(this, &ABaseInteractableActor::OnOverlapEnd);
}

void ABaseInteractableActor::EndPlay(const EEndPlayReason::Type Reason)
{
	if (Overlapping.Contains(this))
	{
		Overlapping.Remove(this);
	}
}

void ABaseInteractableActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Overlapping.AddUnique(this);
	UE_LOG(LogTemp, Warning, TEXT("OVERLAP: %s"), *OtherActor->GetName())
}

void ABaseInteractableActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Overlapping.Contains(this)) Overlapping.Remove(this);
}


