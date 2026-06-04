#pragma once

#include "CoreMinimal.h"
#include "Weapon/TemplateWeaponBase.h"
#include "TemplateWeapon_Shotgun.generated.h"

class USoundBase;
class UParticleSystem;

UCLASS()
class MASTERPROJECT_API ATemplateWeapon_Shotgun : public ATemplateWeaponBase
{
	GENERATED_BODY()
	
public:
	ATemplateWeapon_Shotgun();
	
protected:
	
	//한 번에 발사할 펠릿 수 
	UPROPERTY(EditAnywhere)
	int32 Pellet;
	
	//탄착 퍼짐 각도
	UPROPERTY(EditAnywhere)
	float SpreadAngle;
	
	// 발사 이펙트
	UPROPERTY(EditAnywhere, Category = "Effects")
	TObjectPtr<UParticleSystem> FireEffects;

	// 발사 사운드
	UPROPERTY(EditAnywhere, Category = "Effects")
	TObjectPtr<USoundBase> FireSound;
	
	virtual void ProcessFiring() override;
	virtual void PlayEffects() override;
	
};
