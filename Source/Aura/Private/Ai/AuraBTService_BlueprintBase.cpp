// Copyright Druid Mechanics


#include "Ai/AuraBTService_BlueprintBase.h"

#include "AIController.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"


void UAuraBTService_BlueprintBase::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* OwningPawn = AIOwner->GetPawn();

	const FName TargetTag =  OwningPawn->ActorHasTag(FName("Player")) ? FName("Enemy") : FName("Player");

	TArray<AActor*> ActorWithTag;
	UGameplayStatics::GetAllActorsWithTag(OwningPawn, TargetTag, ActorWithTag);

	// float の中の最大値を表す TNumericLimits<float>::Max();
	float ClosestDistance = TNumericLimits<float>::Max();
	AActor* ClosestActor = nullptr;

	// 一番近い敵をターゲットにする
	for (AActor* Actor : ActorWithTag)
	{
		if (IsValid(Actor) && IsValid(OwningPawn))
		{
			const float Distance = OwningPawn->GetDistanceTo(Actor);
			if (Distance < ClosestDistance)
			{
				ClosestDistance = Distance;
				ClosestActor = Actor;
			}
		}
	}

	//UBTFunctionLibrary::SetBlackboardValueAsObject(this, TargetFollowSelector, ClosestActor);
	//UBTFunctionLibrary::SetBlackboardValueAsObject(this, DistanceToTargetSelector, ClosestDistance);
}