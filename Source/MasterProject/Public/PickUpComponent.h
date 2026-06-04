// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "PickUpComponent.generated.h"


class AMasterProjectCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPickUp, AMasterProjectCharacter*, InPickUpCharacter);

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MASTERPROJECT_API UPickUpComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UPickUpComponent();
	
	UPROPERTY(BlueprintAssignable)
	FOnPickUp OnPickUp;
	
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void HandleOnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
