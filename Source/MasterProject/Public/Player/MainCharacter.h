#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

class ATemplateWeaponBase;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class MASTERPROJECT_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMainCharacter();
	
	UFUNCTION()
	bool IsAiming() const {return bIsAiming;}

protected:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent> SpringArmComp;
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> CameraComp;
	
	UPROPERTY(EditAnywhere, Category="Movement")
	float NormalSpeed;
	UPROPERTY(EditAnywhere, Category="Movement")
	float SprintSpeedMultiplier;
	UPROPERTY(EditAnywhere, Category="Movement")
	float SprintSpeed;
	UPROPERTY(EditAnywhere, Category="Movement | Aim")
	float DefaultFOV;
	UPROPERTY(EditAnywhere, Category="Movement | Aim")
	float AimFOV;
	UPROPERTY(EditAnywhere, Category="Movement | Aim")
	float AimInterpSpeed;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION()
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void StartJump(const FInputActionValue& value);
	UFUNCTION()
	void StopJump(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);
	UFUNCTION()
	void StartSprint(const FInputActionValue& value);
	UFUNCTION()
	void StopSprint(const FInputActionValue& value);
	UFUNCTION()
	void Fire(const FInputActionValue& value);
	UFUNCTION()
	void StartAim(const FInputActionValue& value);
	UFUNCTION()
	void StopAim(const FInputActionValue& value);
	
protected:
	//장착할 총기 클래스
	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<ATemplateWeaponBase> WeaponClass;
	//현재 들고 있는 총기 인스턴스
	UPROPERTY()
	TObjectPtr<ATemplateWeaponBase> CurrentWeapon;
	//총기를 붙일 소켓 이름
	UPROPERTY(EditAnywhere, Category = "Weapon")
	FName WeaponSocketName;
	
	void SpawnAndAttachWeapon();
	
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaTime ) override;
	
private:
	bool bIsAiming;
};
