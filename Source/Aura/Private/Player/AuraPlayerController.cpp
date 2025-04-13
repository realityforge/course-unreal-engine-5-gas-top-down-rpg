#include "Player/AuraPlayerController.h"
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

    if (!GetClass()->HasAnyClassFlags(CLASS_Abstract) && !IsValid(InputMappingContext))
    {
        const auto String = FString::Printf(TEXT("Object %s is not an abstract class but has not specified "
                                                 "the property InputMappingContext"),
                                            *GetActorNameOrLabel());
        Context.AddError(FText::FromString(String));
        Result = EDataValidationResult::Invalid;
    }

    return Result;
}

void AAuraPlayerController::BeginPlay()
{
    Super::BeginPlay();
    checkf(InputMappingContext, TEXT("InputMappingContext not specified"));

    auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    checkf(Subsystem, TEXT("EnhancedInputLocalPlayerSubsystem not enabled for project"));

    Subsystem->AddMappingContext(InputMappingContext, 0);
}
