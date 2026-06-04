#include "Weapon/TemplateWeaponBase.h"

void ATemplateWeaponBase::Fire()
{
	
	if (!bCanFire) return;
	
	if (CheckAmmo())
	{
		PlayEffects();
		ProcessFiring();
		UpdateAmmo();
		
		Super::Fire();
		return;
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
