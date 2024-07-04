// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "DebuffInfo.generated.h"

class UGameplayEffect;

USTRUCT(BlueprintType)
struct FDebuffInfomation
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "GameplayEffects")
	TSubclassOf<UGameplayEffect> DebuffEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();
	
};


/**
 * 
 */
UCLASS()
class AURA_API UDebuffInfo : public UDataAsset
{
	GENERATED_BODY()
public:

	FDebuffInfomation FindDebuffEffectForTag(const FGameplayTag& AttributeTag);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FDebuffInfomation> DebuffInfos;
	
};
