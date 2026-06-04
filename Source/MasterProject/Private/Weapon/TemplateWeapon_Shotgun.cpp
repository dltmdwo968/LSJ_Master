#include "Weapon/TemplateWeapon_Shotgun.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"

ATemplateWeapon_Shotgun::ATemplateWeapon_Shotgun()
{
	Pellet = 8;
	SpreadAngle = 20.f;
	AmmoPerFire = 1;
	MaxAmmo = 6;
	RoF = 2.f;
	DamagePerHit = 20.f;
}

void ATemplateWeapon_Shotgun::ProcessFiring()
{
	FVector StartLocation = FirePoint->GetComponentLocation();
	FRotator BaseRotation = FirePoint->GetComponentRotation();
	
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	ActorsToIgnore.Add(GetOwner());
	
	
	
	for (int32 i = 0; i<Pellet; i++)
	{
		FRotator SpreadRotation = FRotator(FMath::RandRange(-SpreadAngle, SpreadAngle), FMath::RandRange(-SpreadAngle, SpreadAngle), 0.f);
		
		FRotator FinalRotation = BaseRotation + SpreadRotation;
		FVector FireDirection = FinalRotation.Vector();
		FVector EndLocation = StartLocation + FireDirection * Range;
		
		FHitResult HitResult;
		
		bool bHit = UKismetSystemLibrary::LineTraceSingle(
			GetWorld(),
			StartLocation,
			EndLocation,
			UEngineTypes::ConvertToTraceType(ECC_Visibility),
			false,
			ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		HitResult,
		true,
		FLinearColor::Green,
		FLinearColor::Red,
		5.f
		);
	}
}

void ATemplateWeapon_Shotgun::PlayEffects()
{
	UE_LOG(LogTemp, Warning, TEXT("이펙트"));
	
	if (FireEffects)
	{
		UGameplayStatics::SpawnEmitterAttached(
			FireEffects,
			FirePoint,
			NAME_None,
			FVector::ZeroVector,
			FRotator::ZeroRotator,
			EAttachLocation::SnapToTarget);
	}
	
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this, 
			FireSound,
			FirePoint->GetComponentLocation());
	}
}
