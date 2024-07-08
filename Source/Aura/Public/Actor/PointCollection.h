// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PointCollection.generated.h"

UCLASS()
class AURA_API APointCollection : public AActor
{
	GENERATED_BODY()
	
public:	
	APointCollection();

	UFUNCTION(BlueprintPure)
	TArray<USceneComponent*> GetGroundPoint(const FVector& GrandLocation, int32 NumPoints, float YawOverride = 0.f);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<USceneComponent*> ImmutablePts;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess="true"))
	TObjectPtr<USceneComponent> PT_0;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess="true"))
	TObjectPtr<USceneComponent> PT_1;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess="true"))
	TObjectPtr<USceneComponent> PT_2;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess="true"))
	TObjectPtr<USceneComponent> PT_3;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess="true"))
	TObjectPtr<USceneComponent> PT_4;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess="true"))
	TObjectPtr<USceneComponent> PT_5;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess="true"))
	TObjectPtr<USceneComponent> PT_6;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess="true"))
	TObjectPtr<USceneComponent> PT_7;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess="true"))
	TObjectPtr<USceneComponent> PT_8;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess="true"))
	TObjectPtr<USceneComponent> PT_9;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess="true"))
	TObjectPtr<USceneComponent> PT_10;

};
