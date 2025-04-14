#include "Player/AuraPlayerState.h"

AAuraPlayerState::AAuraPlayerState()
{
    // This is quite a high update frequency. Perhaps we should lower it in a the final gream
    SetNetUpdateFrequency(100.f);
}
