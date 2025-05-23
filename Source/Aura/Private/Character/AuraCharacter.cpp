#include "Character/AuraCharacter.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"

AAuraCharacter::AAuraCharacter()
{
    SetOwnerPolicy(EAbilitySystemComponentOwnerPolicy::PlayerStateOwned);
    SetSetupPolicy(EAbilitySystemComponentSetupPolicy::OnPossess);

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->TargetArmLength = 750.0f;
    SpringArmComponent->bEnableCameraLag = true;

    // Look down at the player character as it is a Top Down RPG
    SpringArmComponent->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));

    // We want to the camera to be fixed
    SpringArmComponent->bInheritPitch = false;
    SpringArmComponent->bInheritYaw = false;
    SpringArmComponent->bInheritRoll = false;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
    CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);
    GetCharacterMovement()->bConstrainToPlane = true;
    GetCharacterMovement()->bSnapToPlaneAtStart = true;

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;
}

void AAuraCharacter::InitAbilityActorInfo()
{
    Super::InitAbilityActorInfo();

    const auto AuraPlayerState = GetPlayerState<AAuraPlayerState>();
    check(AuraPlayerState);
    AttributeSet = AuraPlayerState->GetAttributeSet();
    if (const auto PlayerController = Cast<AAuraPlayerController>(GetController()))
    {
        if (const auto HUD = Cast<AAuraHUD>(PlayerController->GetHUD()))
        {
            HUD->CreateOverlayWidget()->AddToViewport();
        }
    }
    if (IsLocallyControlled())
    {
        InitializeDefaultAttributes();
    }
    if (const auto AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(GetAbilitySystemComponentFast()))
    {
        AuraAbilitySystemComponent->AbilityActorInfoSet();
    }
}

int32 AAuraCharacter::GetPlayerLevel()
{
    const auto AuraPlayerState = GetPlayerState<AAuraPlayerState>();
    check(AuraPlayerState);
    return AuraPlayerState->GetPlayerLevel();
}
