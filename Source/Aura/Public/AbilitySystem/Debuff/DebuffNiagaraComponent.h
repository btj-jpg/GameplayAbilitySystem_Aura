// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "AuraGameplayTags.h"
#include "NiagaraComponent.h"
#include "GameplayTagContainer.h"
#include "DebuffNiagaraComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UDebuffNiagaraComponent : public UNiagaraComponent
{
	GENERATED_BODY()

public:

	UDebuffNiagaraComponent();

	UPROPERTY(VisibleAnywhere)
	FGameplayTag DebuffTag = FAuraGameplayTags::Get().Debuff_Burn;

protected:
	
	virtual void BeginPlay() override;
	void DebuffTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
	
	void OnOwnerDeath(AActor* DeadActor);
};
