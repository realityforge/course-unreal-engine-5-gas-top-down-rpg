#include "Player/AuraPlayerController.h"
#include "Aeon/AbilitySystem/AeonAbilitySystemComponent.h"
#include "Aeon/Input/AeonInputConfig.h"
#include "AuraGameplayTags.h"
#include "Components/SplineComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Interaction/EnemyInterface.h"
#include "Misc/DataValidation.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "Player/AuraPlayerState.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraPlayerController)

AAuraPlayerController::AAuraPlayerController()
{
    bReplicates = true;

    Spline = CreateDefaultSubobject<USplineComponent>("Spline");
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
        if (!IsValid(InputConfig))
        {
            const auto String = FString::Printf(TEXT("Object %s is not an abstract class but has not specified "
                                                     "the property InputConfig"),
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

    checkf(MoveAction, TEXT("MoveAction not specified"));

    EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);

    InputConfig->BindNativeInputAction(EnhancedInputComponent,
                                       AuraGameplayTags::Input_Mouse_LeftButton,
                                       ETriggerEvent::Started,
                                       this,
                                       &ThisClass::Input_LeftMouseButtonInputPressed);
    InputConfig->BindNativeInputAction(EnhancedInputComponent,
                                       AuraGameplayTags::Input_Mouse_LeftButton,
                                       ETriggerEvent::Completed,
                                       this,
                                       &ThisClass::Input_LeftMouseButtonInputReleased);
    InputConfig->BindNativeInputAction(EnhancedInputComponent,
                                       AuraGameplayTags::Input_Mouse_LeftButton,
                                       ETriggerEvent::Triggered,
                                       this,
                                       &ThisClass::Input_LeftMouseButtonInputHeld);

    InputConfig->BindAbilityInputAction(EnhancedInputComponent,
                                        this,
                                        &ThisClass::Input_AbilityInputPressed,
                                        &ThisClass::Input_AbilityInputReleased,
                                        &ThisClass::Input_AbilityInputHeld);
}

void AAuraPlayerController::BeginPlay()
{
    Super::BeginPlay();
    checkf(InputConfig, TEXT("InputConfig not specified"));

    const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    checkf(Subsystem, TEXT("Unable to locate EnhancedInputLocalPlayerSubsystem. Misconfigured project?"));
    Subsystem->AddMappingContext(InputConfig->GetDefaultMappingContext(), 0);

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

UAeonAbilitySystemComponent* AAuraPlayerController::GetAeonAbilitySystemComponent()
{
    if (!IsValid(AeonAbilitySystemComponent))
    {
        const auto PS = GetPlayerState<AAuraPlayerState>();
        check(PS);
        AeonAbilitySystemComponent = CastChecked<UAeonAbilitySystemComponent>(PS->GetAbilitySystemComponent());
    }
    return AeonAbilitySystemComponent;
}

void AAuraPlayerController::Input_LeftMouseButtonInputPressed()
{
    // UE_LOG(LogTemp, Verbose, TEXT("Input_LeftMouseButtonInputPressed"));
    bTargeting = nullptr != CurrentActorUnderCursor;
    bAutoRunning = false;
}

void AAuraPlayerController::Input_LeftMouseButtonInputReleased()
{
    UE_LOG(LogTemp, Verbose, TEXT("Input_LeftMouseButtonInputReleased"));
    if (bTargeting)
    {
        GetAeonAbilitySystemComponent()->OnAbilityInputReleased(AuraGameplayTags::Input_Mouse_LeftButton, false);
    }
    else
    {
        // ReSharper disable once CppTooWideScopeInitStatement
        const auto ControlledPawn = GetPawn();
        if (ControlledPawn && FollowTime <= ShortPressThreshold)
        {
            // We get in this block if the press was short enough, and thus we consider the input to be a request to
            // autorun to a destination.

            const auto Start = ControlledPawn->GetActorLocation();
            const auto& End = CachedDestination;

            if (const auto Path = UNavigationSystemV1::FindPathToLocationSynchronously(this, Start, End))
            {
                // Reset the state of the previous spline path calculated
                Spline->ClearSplinePoints();
                for (const auto& PointPoint : Path->PathPoints)
                {
                    Spline->AddSplinePoint(PointPoint, ESplineCoordinateSpace::World);

                    DrawDebugSphere(GetWorld(), PointPoint, 8.f, 8, FColor::Green, false, 5.f);
                }
                bAutoRunning = true;
            }
            else
            {
                UE_LOG(LogTemp,
                       Warning,
                       TEXT("Input_LeftMouseButtonInputReleased: No path found to destination point"));
            }
        }
        FollowTime = 0.f;
        bTargeting = false;
    }
}

void AAuraPlayerController::Input_LeftMouseButtonInputHeld()
{
    UE_LOG(LogTemp, Verbose, TEXT("Input_LeftMouseButtonInputHeld"));
    if (bTargeting)
    {
        GetAeonAbilitySystemComponent()->OnAbilityInputHeld(AuraGameplayTags::Input_Mouse_LeftButton, false);
    }
    else
    {
        FollowTime += GetWorld()->GetDeltaSeconds();

        if (FHitResult Hit; GetHitResultUnderCursor(ECC_Visibility, false, Hit))
        {
            CachedDestination = Hit.ImpactPoint;
        }

        if (const auto ControlledPawn = GetPawn())
        {
            const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
            ControlledPawn->AddMovementInput(WorldDirection);
        }
    }
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AAuraPlayerController::Input_AbilityInputPressed(const FGameplayTag InGameplayTag)
{
    UE_LOG(LogTemp, Verbose, TEXT("Input_AbilityInputPressed: %s"), *InGameplayTag.ToString());
    GetAeonAbilitySystemComponent()->OnAbilityInputPressed(InGameplayTag);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AAuraPlayerController::Input_AbilityInputReleased(const FGameplayTag InGameplayTag)
{
    UE_LOG(LogTemp, Verbose, TEXT("Input_AbilityInputReleased: %s"), *InGameplayTag.ToString());
    GetAeonAbilitySystemComponent()->OnAbilityInputReleased(InGameplayTag);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AAuraPlayerController::Input_AbilityInputHeld(const FGameplayTag InGameplayTag)
{
    UE_LOG(LogTemp, Verbose, TEXT("Input_AbilityInputHeld: %s"), *InGameplayTag.ToString());
    GetAeonAbilitySystemComponent()->OnAbilityInputHeld(InGameplayTag);
}
