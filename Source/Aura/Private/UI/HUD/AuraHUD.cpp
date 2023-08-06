// Copyright Norse Game Studio


#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/Widgets/AuraUserWidget.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetControllerClass == NULL) {

		if (GEngine != nullptr) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "OverlayWidgetControllerClass == NULL");
		}

		return nullptr; 
	}

	if (OverlayWidgetController == nullptr) {
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
	}

	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ABS, UAttributeSet* AS)
{
	
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass uninitialised. Please set in BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass uninitialised. Please set in BP_AuraHUD"));

	if (OverlayWidgetClass != NULL) {
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);

		OverlayWidget = Cast<UAuraUserWidget>(Widget);

		FWidgetControllerParams WidgetControllerParams(PC, PS, ABS, AS);

		UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

		OverlayWidget->SetWidgetController(WidgetController);

		Widget->AddToViewport();
	}
}

