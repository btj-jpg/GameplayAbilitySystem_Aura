// Copyright Druid Mechanics


#include "UI/HUD/AuraHUD.h"

#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerclass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);

		return OverlayWidgetController;
		
	}
	return OverlayWidgetController;
}

void AAuraHUD::Initoverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("オーバーレイウィジェットクラスが設定されてません AuraHUD"));
	checkf(OverlayWidgetControllerclass, TEXT("オーバーレイウィジェットコントローラークラスが設定されてません AuraHUD"));
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);

	// オーバーレイウィジェットコントローラーに４つのパラメーターをセットする
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	// オーバーレイウィジェットにウィジェットコントローラーをセットする。
	OverlayWidget->SetWidgetController(WidgetController);

	
	Widget->AddToViewport();
}