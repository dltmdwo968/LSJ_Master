#include "Weapon/TemplateWeaponBase.h"

ATemplateWeaponBase::ATemplateWeaponBase()
{
	RecoilPitch = -3.0f;
	RecoilRecoverySpeed = 5.f;
	CurrentRecoilPitch = 0.f;
	
	PrimaryActorTick.bCanEverTick = true;
}

void ATemplateWeaponBase::Fire()
{
	
	if (!bCanFire) return;
	
	if (CheckAmmo())
	{
		PlayEffects();
		ProcessFiring();
		UpdateAmmo();
		ApplyRecoil();
		
		Super::Fire();
		return;
	}
}

void ATemplateWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!FMath::IsNearlyZero(CurrentRecoilPitch, 0.01f))
	{
		float RecoveryDelta = FMath::FInterpTo(CurrentRecoilPitch, 0.f, DeltaTime, RecoilRecoverySpeed);
		
		float DeltaPitch = RecoveryDelta - CurrentRecoilPitch;
		CurrentRecoilPitch = RecoveryDelta;
		
		if (APlayerController * PC = GetOwner() ? Cast<APlayerController>(GetOwner()->GetInstigatorController()) : nullptr)
		{
			PC->AddPitchInput(DeltaPitch);
		}
	}

	
}

void ATemplateWeaponBase::Reload_Implementation()
{
	CurrentAmmo = MaxAmmo;
}

bool ATemplateWeaponBase::CheckAmmo()
{
	return AmmoPerFire <= CurrentAmmo;
}

void ATemplateWeaponBase::UpdateAmmo()
{
	CurrentAmmo -= AmmoPerFire;
}

void ATemplateWeaponBase::ProcessFiring()
{
	
}

void ATemplateWeaponBase::PlayEffects()
{
	
}

void ATemplateWeaponBase::ApplyRecoil()
{
	if (APlayerController* PC = GetOwner() ? Cast<APlayerController>(GetOwner()->GetInstigatorController()) : nullptr)
	{
		PC->AddPitchInput(RecoilPitch);
		CurrentRecoilPitch += RecoilPitch;
	}
}
