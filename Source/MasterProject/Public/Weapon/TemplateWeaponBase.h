#pragma once

#include "CoreMinimal.h"
#include "Weapon/WeaponBase.h"
#include "TemplateWeaponBase.generated.h"


UCLASS()
class MASTERPROJECT_API ATemplateWeaponBase : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	virtual void Fire() override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Reload();
	
protected:
	UFUNCTION()
	bool CheckAmmo();
	
	//총을 어떻게 쏠지
	UFUNCTION()
	virtual void ProcessFiring();
	
	//이펙트 실행
	UFUNCTION()
	virtual void PlayEffects();
	
	//총알 업데이트
	UFUNCTION()
	void UpdateAmmo();
};
