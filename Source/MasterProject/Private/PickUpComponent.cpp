// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpComponent.h"
#include "MasterProject/MasterProjectCharacter.h"

UPickUpComponent::UPickUpComponent()
{
	
}

void UPickUpComponent::BeginPlay()
{
	Super::BeginPlay();
	OnComponentBeginOverlap.AddDynamic(this, &ThisClass::HandleOnComponentBeginOverlap);
}

void UPickUpComponent::HandleOnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMasterProjectCharacter* OverlappedCharacter = Cast<AMasterProjectCharacter>(OtherActor);
	if (IsValid(OverlappedCharacter) == true)
	{
		OnPickUp.Broadcast(OverlappedCharacter);

		OnComponentBeginOverlap.RemoveAll(this);
	}
}
