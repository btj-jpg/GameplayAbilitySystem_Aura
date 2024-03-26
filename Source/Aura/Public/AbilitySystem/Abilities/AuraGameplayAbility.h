// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AuraGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	// どのボタンを押したらアクティブ化するかを決めるタグ
	UPROPERTY(EditDefaultsOnly, Category="Input")
	FGameplayTag StartUpInputTag;
	
};
