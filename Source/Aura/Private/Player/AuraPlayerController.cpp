#include "Player/AuraPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Interaction/EnemyInterface.h"
#include "Misc/DataValidation.h"
#include "Player/AuraPlayerState.h"

AAuraPlayerController::AAuraPlayerController()
{
    bReplicates = true;
}

void AAuraPlayerController::PlayerTick(const float DeltaTime)
{
    Super::PlayerTick(DeltaTime);

    CursorTrace();
}

EDataValidationResult AAuraPlayerController::IsDataValid(FDataValidationContext& Context) const
{
    auto Result = CombineDataValidationResults(Super::IsDataValid(Context), EDataValidationResult::Valid);

    if (!GetClass()->HasAnyClassFlags(CLASS_Abstract))
    {
        if (!IsValid(InputMappingContext))
        {
            const auto String = FString::Printf(TEXT("Object %s is not an abstract class but has not specified "
                                                     "the property InputMappingContext"),
                                                *GetActorNameOrLabel());
            Context.AddError(FText::FromString(String));
            Result = EDataValidationResult::Invalid;
        }
        if (!IsValid(MoveAction))
        {
            const auto String = FString::Printf(TEXT("Object %s is not an abstract class but has not specified "
                                                     "the property MoveAction"),
                                                *GetActorNameOrLabel());
            Context.AddError(FText::FromString(String));
            Result = EDataValidationResult::Invalid;
        }
    }

    return Result;
}

FWidgetControllerParams AAuraPlayerController::CreateWidgetControllerParams()
{
    const auto AuraPlayerState = GetPlayerState<AAuraPlayerState>();
    check(AuraPlayerState);
    const auto AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
    const auto AttributeSet = AuraPlayerState->GetAttributeSet();
    return FWidgetControllerParams(this, AuraPlayerState, AbilitySystemComponent, AttributeSet);
}

void AAuraPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    const auto EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

    check(MoveAction);

    EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
}

void AAuraPlayerController::BeginPlay()
{
    Super::BeginPlay();
    checkf(InputMappingContext, TEXT("InputMappingContext not specified"));

    if (const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(InputMappingContext, 0);
    }

    bShowMouseCursor = true;
    DefaultMouseCursor = EMouseCursor::Default;
    FInputModeGameAndUI InputModeData;
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    InputModeData.SetHideCursorDuringCapture(false);
    SetInputMode(InputModeData);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
    const auto InputAxisVector = InputActionValue.Get<FVector2D>();

    const FRotator Rotation = GetControlRotation();
    const FRotator YawRotation{ 0.f, Rotation.Yaw, 0 };

    const FRotationMatrix RotationMatrix(YawRotation);

    const FVector ForwardDirection{ RotationMatrix.GetUnitAxis(EAxis::X) };
    const FVector RightDirection{ RotationMatrix.GetUnitAxis(EAxis::Y) };

    if (const auto ControlledPawn = GetPawn<APawn>())
    {
        ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
        ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
    }
}

void AAuraPlayerController::CursorTrace()
{
    FHitResult CursorHit;
    GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
    if (CursorHit.bBlockingHit)
    {
        LastActorUnderCursor = CurrentActorUnderCursor;
        CurrentActorUnderCursor = CursorHit.GetActor();

        if (LastActorUnderCursor)
        {
            if (CurrentActorUnderCursor != LastActorUnderCursor)
            {
                // Last actor set, and does not match current actor => Unhighlight last
                LastActorUnderCursor->UnHighlightActor();

                if (CurrentActorUnderCursor)
                {
                    // Last actor set, Current actor set and actors do not match => Highlight current
                    CurrentActorUnderCursor->HighlightActor();
                }
            }
        }
        else if (CurrentActorUnderCursor)
        {
            // Current actor set, no last actor set => Highlight current
            CurrentActorUnderCursor->HighlightActor();
        }
    }
}
