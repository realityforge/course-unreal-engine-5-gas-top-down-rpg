#include "Player/AuraPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Misc/DataValidation.h"

AAuraPlayerController::AAuraPlayerController()
{
    bReplicates = true;
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

void AAuraPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    auto EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

    check(MoveAction);

    EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
}

void AAuraPlayerController::BeginPlay()
{
    Super::BeginPlay();
    checkf(InputMappingContext, TEXT("InputMappingContext not specified"));

    auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    checkf(Subsystem, TEXT("EnhancedInputLocalPlayerSubsystem not enabled for project"));

    Subsystem->AddMappingContext(InputMappingContext, 0);

    bShowMouseCursor = true;
    DefaultMouseCursor = EMouseCursor::Default;
    FInputModeGameAndUI InputModeData;
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    InputModeData.SetHideCursorDuringCapture(false);
    SetInputMode(InputModeData);
}

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
