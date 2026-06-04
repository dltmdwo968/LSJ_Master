#pragma once

#include "CoreMinimal.h"
#include "Weapon/WeaponBase.h"
#include "TemplateWeaponBase.generated.h"


UCLASS()
class MASTERPROJECT_API ATemplateWeaponBase : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	ATemplateWeaponBase();
	
	virtual void Fire() override;
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Reload();
	
protected:
	//반동 세기
	UPROPERTY(EditAnywhere, Category = "Recoil")
	float RecoilPitch;
	//반동 복귀 속도
	UPROPERTY(EditAnywhere, Category = "Recoil")
	float RecoilRecoverySpeed;
	
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
	
private:
	float CurrentRecoilPitch;
	
	void ApplyRecoil();
};
