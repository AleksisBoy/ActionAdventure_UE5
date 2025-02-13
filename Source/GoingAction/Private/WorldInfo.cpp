// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldInfo.h"


UWorldInfo::UWorldInfo()
{
	LastHour = Time;
}

float UWorldInfo::GetTime()
{
	return Time;
}

void UWorldInfo::Tick(float DeltaTime)
{
	Time += TimePerSec * DeltaTime;
	if (Time > LastHour + 1)
	{
		LastHour = Time;
		OnHourPassed.Broadcast();
	}
	if (Time >= 24.f)
	{
		Time -= 24.f;
	}
}
