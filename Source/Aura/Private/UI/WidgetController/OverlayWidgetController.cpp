// Copyright Druid Mechanics


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "Player/AuraPlayerState.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());

	if (UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent))
	{
		if ( AuraASC -> bStartupAbilitiesGiven )
		{
			OnInitializeStartupAbilities (AuraASC);
		}
	}
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{

	// 関数にバインド
	AAuraPlayerState* AuraPlayerState = CastChecked<AAuraPlayerState>(PlayerState);
	AuraPlayerState->OnXPChangedDelegate.AddUObject(this, &UOverlayWidgetController::OnXPChanged);
	
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnManaChanged.Broadcast(Data.NewValue);
			}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxManaChanged.Broadcast(Data.NewValue);
			}
		);

	if (UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent))
	{
		if (AuraASC->bStartupAbilitiesGiven)
		{
			
			OnInitializeStartupAbilities(AuraASC);
		}
		else
		{
			AuraASC->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::OnInitializeStartupAbilities);
		}

		AuraASC->EffectAssetTags.AddLambda(
			[this](const FGameplayTagContainer& AssetTags)
			{
				for (const FGameplayTag& Tag : AssetTags)
				{
					// For example, say that Tag = Message.HealthPotion
					// "Message.HealthPotion".MatchesTag("Message") will return True, "Message".MatchesTag("Message.HealthPotion") will return False
					FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
					if (Tag.MatchesTag(MessageTag))
					{
						const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
						MessageWidgetRowDelegate.Broadcast(*Row);
					}
				}
			}
		);
	}
	
}

void UOverlayWidgetController::OnInitializeStartupAbilities(UAuraAbilitySystemComponent* AuraAbilitySystemComponent)
{
	//TODO Get information about all given abilities, look up their Ability Info, and broadcast it to widgets.
	if (!AuraAbilitySystemComponent->bStartupAbilitiesGiven) return;
	UE_LOG(LogTemp, Warning, TEXT("aaa[%s]"), *AuraAbilitySystemComponent->GetOwnerActor()->GetActorNameOrLabel());
	FForEachAbility BroadcastDelegate;
	BroadcastDelegate.BindLambda([this, AuraAbilitySystemComponent](const FGameplayAbilitySpec& AbilitySpec)
	{
		//TODO need a way to figure out the ability tag for a given ability spec.
		FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AuraAbilitySystemComponent->GetAbilityTagFromSpec(AbilitySpec));
		Info.InputTag = AuraAbilitySystemComponent->GetInputTagFromSpec(AbilitySpec);
		AbilityInfoDelegate.Broadcast(Info);
	});
	AuraAbilitySystemComponent->ForEachAbility(BroadcastDelegate);
}

void UOverlayWidgetController::OnXPChanged(int32 InXP) const
{
	const AAuraPlayerState* AuraPlayerState = CastChecked<AAuraPlayerState>(PlayerState);
	const ULevelUpInfo* LevelUpInfo = AuraPlayerState->LevelUpInfo;
	checkf(LevelUpInfo, TEXT("AuraPlayerStateにLevelUpInfoが設定されていません"));

	const int32 Level = LevelUpInfo->FindLevelForXp(InXP);
	const int32 MaxLevel = LevelUpInfo->LevelUpInformation.Num();
	if (Level <= MaxLevel && Level > 0) {
		
		const int32 LevelUPRequirement = LevelUpInfo->LevelUpInformation[Level].LevelUpRequirement;
		const int32 BeforeLevelUPRequirement = LevelUpInfo->LevelUpInformation[Level - 1].LevelUpRequirement;

		const int32 CalcRequirement = LevelUPRequirement - BeforeLevelUPRequirement;
		const int32 CalcXP = InXP - BeforeLevelUPRequirement;
	
		const float XPBarPercent = static_cast<float>(CalcXP) / static_cast<float>(CalcRequirement);

		OnXPPercentChangeDelegate.Broadcast(XPBarPercent);
	}
}
