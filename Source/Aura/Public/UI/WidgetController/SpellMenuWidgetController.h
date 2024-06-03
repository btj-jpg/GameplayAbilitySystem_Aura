// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "AuraGameplayTags.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "GameplayTagContainer.h"
#include "SpellMenuWidgetController.generated.h"

struct FAuraGameplayTags;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSpellGlobeSelectedSignature, bool, bSpendPointsButtonEnabled, bool,
                                             bEquipButtonEnabled);

struct FSelectedAbility
{
	FGameplayTag Ability = FGameplayTag();
	FGameplayTag Status = FGameplayTag();
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API USpellMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnPlayerStatChangedSignature SpellPointChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FSpellGlobeSelectedSignature SpellGlobeSelectedDelegate;
	
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UFUNCTION(BlueprintCallable)
	void SpellGlobeSelected(const FGameplayTag& AbilityTag);

	UFUNCTION(BlueprintCallable)
	void SpendPointButtonPressed();

private:

	static void ShouldEnableButtons(const FGameplayTag& AbilityStatus, int32 SpellPoints,
		bool& bshouldEnableSpellPointsButton, bool& bShouldEnableEquipButton);

	FSelectedAbility SelectedAbility = { FAuraGameplayTags::Get().Abilities_None, FAuraGameplayTags::Get().Abilities_Status_locked };
	int32 CurrentSpellPoints = 0;
	
};
