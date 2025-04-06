// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldInfoSubsystem.h"


UWorldInfoSubsystem::UWorldInfoSubsystem()
{
	LastHour = Time;
}

float UWorldInfoSubsystem::GetTime()
{
	return Time;
}

void UWorldInfoSubsystem::Tick(float DeltaTime)
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
