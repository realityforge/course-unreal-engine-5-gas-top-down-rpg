#include "Character/AuraEnemy.h"
#include "Logging/StructuredLog.h"

void AAuraEnemy::HighlightActor()
{
    bHighlighted = true;
    UE_LOGFMT(LogTemp, Display, "AuraEnemy {ActorName} highligheted", GetActorNameOrLabel());
}

void AAuraEnemy::UnHighlightActor()
{
    bHighlighted = false;
    UE_LOGFMT(LogTemp, Display, "AuraEnemy {ActorName} un-highligheted", GetActorNameOrLabel());
}
