#include "Character/AuraCharacter.h"
#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{
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

void AAuraCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    // Init AbilityActorInfo on Server
    SetupAbilityActorInfo();
}

void AAuraCharacter::SetupAbilityActorInfo()
{
    const auto AuraPlayerState = GetPlayerState<AAuraPlayerState>();
    check(AuraPlayerState);
    AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponentFast();
    AbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState, this);
    AttributeSet = AuraPlayerState->GetAttributeSet();
    if (const auto PlayerController = Cast<APlayerController>(GetController()))
    {
        if (const auto HUD = Cast<AAuraHUD>(PlayerController->GetHUD()))
        {
            HUD->InitOverlay(PlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
        }
    }
}

void AAuraCharacter::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();

    // Init AbilityActorInfo on Client
    SetupAbilityActorInfo();
}
