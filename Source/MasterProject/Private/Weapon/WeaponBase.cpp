#include "Weapon/WeaponBase.h"

#include "PickUpComponent.h"
#include "Components/ArrowComponent.h"
#include "MasterProject/MasterProjectCharacter.h"


AWeaponBase::AWeaponBase()
{
 	
	PrimaryActorTick.bCanEverTick = false;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	
	FirePoint = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePoint"));
	FirePoint->SetupAttachment(RootComponent);
	
	AmmoPerFire = 1;
	CurrentAmmo = 0;
	MaxAmmo = 12;
	RoF = 1.f;
	bCanFire = true;
	Range = 1000.f;
	DamagePerHit = 100.f;

}


void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
		
	CurrentAmmo = MaxAmmo;
}


void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::Fire()
{
	bCanFire = false;
	
	GetWorld()->GetTimerManager().SetTimer(TimerFireDelay, this, &AWeaponBase::HandleFireDelay, 1.f/RoF, false);
}

void AWeaponBase::HandleFireDelay()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerFireDelay);
	bCanFire = true;
}

