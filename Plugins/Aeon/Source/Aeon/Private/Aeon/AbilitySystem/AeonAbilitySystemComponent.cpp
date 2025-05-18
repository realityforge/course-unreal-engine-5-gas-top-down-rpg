/*
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "Aeon/AbilitySystem/AeonAbilitySystemComponent.h"
#include "Aeon/AbilitySystem/AeonAbilityTagRelationshipMapping.h"
#include "Aeon/Logging.h"
#include "Logging/StructuredLog.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AeonAbilitySystemComponent)

#pragma region AbilityTagRelationship Support

// --------------------------------------------------- //
// AbilityTagRelationship Support
// --------------------------------------------------- //

void UAeonAbilitySystemComponent::SetTagRelationshipMapping(
    UAeonAbilityTagRelationshipMapping* InTagRelationshipMapping)
{
    UE_LOGFMT(AeonTagRelationship,
              Log,
              "TagRelationshipMapping changed to {Mapping} for AeonAbilitySystemComponent {OwnerActor}",
              GetNameSafe(InTagRelationshipMapping),
              GetNameSafe(GetOwnerActor()));
    TagRelationshipMapping = InTagRelationshipMapping;
}

static FString ToTagDeltaDiffString(const FGameplayTagContainer& AllTags, const FGameplayTagContainer& OriginalTags)
{
    FGameplayTagContainer Tags(AllTags);
    Tags.RemoveTags(OriginalTags);
    return Tags.ToString();
}

void UAeonAbilitySystemComponent::ApplyAbilityBlockAndCancelTags(const FGameplayTagContainer& AbilityTags,
                                                                 UGameplayAbility* RequestingAbility,
                                                                 const bool bEnableBlockTags,
                                                                 const FGameplayTagContainer& BlockTags,
                                                                 const bool bExecuteCancelTags,
                                                                 const FGameplayTagContainer& CancelTags)
{
    if (TagRelationshipMapping)
    {
        FGameplayTagContainer AllBlockTags = BlockTags;
        FGameplayTagContainer AllCancelTags = CancelTags;
        TagRelationshipMapping->GetAbilityTagsToBlockAndCancel(AbilityTags, AllBlockTags, AllCancelTags);

        UE_LOGFMT(AeonTagRelationship,
                  Verbose,
                  "ApplyAbilityBlockAndCancelTags for ability defined "
                  "by tags {Tags} added {BlockTags} block tags and {CancelTags} cancel tags for actor '{OwnerActor}'",
                  AbilityTags.ToString(),
                  ToTagDeltaDiffString(AllBlockTags, BlockTags),
                  ToTagDeltaDiffString(AllCancelTags, CancelTags),
                  GetNameSafe(GetOwnerActor()));

        Super::ApplyAbilityBlockAndCancelTags(AbilityTags,
                                              RequestingAbility,
                                              bEnableBlockTags,
                                              AllBlockTags,
                                              bExecuteCancelTags,
                                              AllCancelTags);
    }
    else
    {
        Super::ApplyAbilityBlockAndCancelTags(AbilityTags,
                                              RequestingAbility,
                                              bEnableBlockTags,
                                              BlockTags,
                                              bExecuteCancelTags,
                                              CancelTags);
    }
}

void UAeonAbilitySystemComponent::GetAdditionalTagRequirements(const FGameplayTagContainer& AbilityTags,
                                                               FGameplayTagContainer& OutActivationRequiredTags,
                                                               FGameplayTagContainer& OutActivationBlockedTags,
                                                               FGameplayTagContainer& OutSourceRequiredTags,
                                                               FGameplayTagContainer& OutSourceBlockedTags,
                                                               FGameplayTagContainer& OutTargetRequiredTags,
                                                               FGameplayTagContainer& OutTargetBlockedTags) const
{
    if (TagRelationshipMapping)
    {
        TagRelationshipMapping->GetAdditionalTagRequirements(AbilityTags,
                                                             OutActivationRequiredTags,
                                                             OutActivationBlockedTags,
                                                             OutSourceRequiredTags,
                                                             OutSourceBlockedTags,
                                                             OutTargetRequiredTags,
                                                             OutTargetBlockedTags);
        UE_LOGFMT(AeonTagRelationship,
                  Verbose,
                  "GetAdditionalTagRequirements for ability defined by tags {AbilityTags} for actor '{OwnerActor}': "
                  "ActivationRequiredTags={ActivationRequiredTags} "
                  "ActivationBlockedTags={ActivationBlockedTags} "
                  "SourceRequiredTags={SourceRequiredTags} "
                  "SourceBlockedTags={SourceBlockedTags} "
                  "TargetRequiredTags={TargetRequiredTags} "
                  "TargetBlockedTags={TargetBlockedTags}",
                  AbilityTags,
                  GetNameSafe(GetOwnerActor()),
                  OutActivationRequiredTags,
                  OutActivationBlockedTags,
                  OutSourceRequiredTags,
                  OutSourceBlockedTags,
                  OutTargetRequiredTags,
                  OutTargetBlockedTags);
    }
}

// --------------------------------------------------- //
#pragma endregion
