// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()


public:

	// WidgetControllerがプレイヤーの状態などすべてのデータを取得する
	
	// BluePrintで使用できる関数
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:

	// BluePrintで設定できる関数
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
	
};
