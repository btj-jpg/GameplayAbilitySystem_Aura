// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AuraGameModeBase.generated.h"

class UAbilityInfo;
class UCharacterClassInfo;
class UDebuffInfo;
/**
 * 
 */
UCLASS()
class AURA_API AAuraGameModeBase : public AGameModeBase
{
	GENERATED_BODY()


public:
	
	UPROPERTY(EditDefaultsOnly, Category= "Character Class Default")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;

	UPROPERTY(EditAnywhere, Category="Character Class Default")
	TObjectPtr<UAbilityInfo> AbilityInfo;

	UPROPERTY(EditAnywhere, Category="Character Class Default")
	TObjectPtr<UDebuffInfo> DebuffInfo;
};
