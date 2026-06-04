#include "Player/MainCharacter.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/MainPlayerController.h"
#include "Weapon/TemplateWeaponBase.h"


AMainCharacter::AMainCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
 	
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = true;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;
	
    
    NormalSpeed = 600.f;
    SprintSpeedMultiplier = 1.5;
    SprintSpeed = NormalSpeed * SprintSpeedMultiplier;
    
    GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
    
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;
    
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); 
    
    //무기
    WeaponSocketName = FName("WeaponSocket");
    
    //조준
    DefaultFOV = 90.f;
    AimFOV = 60.f;
    AimInterpSpeed = 10.f;
    bIsAiming = false;
}

void AMainCharacter::BeginPlay()
{
    Super::BeginPlay();
    
    SpawnAndAttachWeapon();
    
    if (CameraComp)
    {
        CameraComp->SetFieldOfView(DefaultFOV);
    }
}

void AMainCharacter::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    
    if (CameraComp)
    {
        float TargetFOV = bIsAiming ? AimFOV : DefaultFOV;
        float CurrentFOV = CameraComp->FieldOfView;
        float NewFOV = FMath::FInterpTo(CurrentFOV, TargetFOV, DeltaTime, AimInterpSpeed);
        CameraComp->SetFieldOfView(NewFOV);
    }
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        
        if (AMainPlayerController* PlayerController = Cast<AMainPlayerController>(GetController()))
        {
            if (PlayerController->MoveAction)
            {
                EnhancedInput->BindAction(
                    PlayerController->MoveAction,
                    ETriggerEvent::Triggered,
                    this,
                    &AMainCharacter::Move
                );
            }
            
            if (PlayerController->JumpAction)
            {
                EnhancedInput->BindAction(
                    PlayerController->JumpAction,
                    ETriggerEvent::Triggered,
                    this,
                    &AMainCharacter::StartJump
                );
                
                EnhancedInput->BindAction(
                    PlayerController->JumpAction,
                    ETriggerEvent::Completed,
                    this,
                    &AMainCharacter::StopJump
                );
            }
            
            if (PlayerController->LookAction)
            {
                EnhancedInput->BindAction(
                    PlayerController->LookAction,
                    ETriggerEvent::Triggered,
                    this,
                    &AMainCharacter::Look
                );
            }
            
            if (PlayerController->SprintAction)
            {
                
                EnhancedInput->BindAction(
                    PlayerController->SprintAction,
                    ETriggerEvent::Triggered, 
                    this, 
                    &AMainCharacter::StartSprint
                );
                
                EnhancedInput->BindAction(
                    PlayerController->SprintAction, 
                    ETriggerEvent::Completed, 
                    this, 
                    &AMainCharacter::StopSprint
                );
                
         
            }    
            if (PlayerController->FireAction)
            {
                EnhancedInput->BindAction(
                PlayerController->FireAction,
                    ETriggerEvent::Triggered,
                    this,
                    &AMainCharacter::Fire
             );
            }
            
            if (PlayerController->AimAction)
            {
                EnhancedInput->BindAction(
                    PlayerController->AimAction,
                    ETriggerEvent::Started,
                    this,
                    &AMainCharacter::StartAim
 );

                EnhancedInput->BindAction(
                    PlayerController->AimAction,
                    ETriggerEvent::Completed,
                    this,
                    &AMainCharacter::StopAim
                );
            }
        }
    }
}

void AMainCharacter::Move(const FInputActionValue& value)
{
    if (!Controller) return;
    
    //정면 방향 찾기
    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation(0, Rotation.Yaw, 0);
    
    //정면 벡터 가져오기
    const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    //오른쪽 백터 가져오기
    const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
    
    const FVector2D MoveInput = value.Get<FVector2D>();

    if (!FMath::IsNearlyZero(MoveInput.X))
    {
        AddMovementInput(ForwardDirection, MoveInput.X);
    }

    if (!FMath::IsNearlyZero(MoveInput.Y))
    {
        AddMovementInput(RightDirection, MoveInput.Y);
    }
}

void AMainCharacter::StartJump(const FInputActionValue& value)
{
    if (value.Get<bool>())
    {
        Jump();
    }
}

void AMainCharacter::StopJump(const FInputActionValue& value)
{
    if (!value.Get<bool>())
    {
        StopJumping();
    }
}

void AMainCharacter::Look(const FInputActionValue& value)
{
    
    FVector2D LookInput = value.Get<FVector2D>();


    AddControllerYawInput(LookInput.X);
    AddControllerPitchInput(LookInput.Y);
}

void AMainCharacter::StartSprint(const FInputActionValue& value)
{
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
    }
}

void AMainCharacter::StopSprint(const FInputActionValue& value)
{
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
    }
}

void AMainCharacter::Fire(const FInputActionValue& value)
{
    if (CurrentWeapon)
    {
       CurrentWeapon->Fire();
        UE_LOG(LogTemp, Warning, TEXT("Fired"));
    }   
}

void AMainCharacter::StartAim(const FInputActionValue& value)
{
  bIsAiming = true;   
}

void AMainCharacter::StopAim(const FInputActionValue& value)
{
    bIsAiming = false;
}

void AMainCharacter::SpawnAndAttachWeapon()
{
    if (!WeaponClass) return;

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.Instigator = this;
    
    CurrentWeapon = GetWorld()->SpawnActor<ATemplateWeaponBase>(
        WeaponClass,
        FVector::ZeroVector,
        FRotator::ZeroRotator,
        SpawnParams);
    
    if (!CurrentWeapon) return;
    
    FAttachmentTransformRules Rlues(EAttachmentRule::SnapToTarget, true);
    CurrentWeapon->AttachToComponent(GetMesh(), Rlues, WeaponSocketName);
    
    //CurrentWeapon->SetActorRelativeLocation(FVector::ZeroVector);
    //CurrentWeapon->SetActorRelativeRotation(FRotator::ZeroRotator);
    
}
