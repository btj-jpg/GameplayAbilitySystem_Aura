// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "AuraBTService_BlueprintBase.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraBTService_BlueprintBase : public UBTService_BlueprintBase
{
	GENERATED_BODY()

	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FBlackboardKeySelector TargetFollowSelector;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FBlackboardKeySelector DistanceToTargetSelector;
};
