// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/LocationData.h"
#include "Actors/WorldLocation.h"

AWorldLocation* ULocationData::GetWorldLocation()
{
    return AWorldLocation::Get(this);
}
