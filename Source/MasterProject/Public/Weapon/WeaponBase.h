#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class UPickUpComponent;
class AMasterProjectCharacter;

UCLASS()
class MASTERPROJECT_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AWeaponBase();


protected:
	
	virtual void BeginPlay() override;
	

public:	
	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> Root;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UArrowComponent> FirePoint;
	
	UFUNCTION(BlueprintCallable)
	virtual void Fire();
	
protected:
	//소모되는 탄약 수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AmmoPerFire;
	
	//남은 탄약 수
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	int32 CurrentAmmo;

	//탄약 보유량
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxAmmo;
	
	//연사 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RoF;
	
	//유효 사거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Range;
	
	//데미지
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamagePerHit;
	
	//발사 가능 여부
	UPROPERTY(BlueprintReadWrite)
	bool bCanFire;
	
	//연사 속도 제어를 위한 핸들
	UPROPERTY(BlueprintReadWrite)
	FTimerHandle TimerFireDelay;
	
	UFUNCTION()
	void HandleFireDelay();
	
};
