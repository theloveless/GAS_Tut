// Copyright Norse Game Studio


#include "Player/AuraPlayerController.h"
//Enhanced input
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubSystems.h"
#include "InputActionValue.h"

#include "Interaction/EnemyInterface.h"


AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//Setting up the Enhanced input system
	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (Subsystem != nullptr) {
		Subsystem->AddMappingContext(AuraContext, 0);
	}

	
	//Setting up Input modes
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);

	SetInputMode(InputModeData);
}


void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>()) {
		
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}

}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;

	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	if (CursorHit.bBlockingHit == false) {
		return;
	}

	LastActor = ThisActor;

	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	/*
		Line trace from cursor. There are several scenarios

		A: LastActor is nullptr && ThisActor is nullptr
			- Do nothing
		B: LastActor is nullptr && ThisActor is valid
			- Call HighlightActor on ThisActor.
		C: LastActor is valid && ThisActor is nullptr.
			- Call UnHihlightActor on LastActor.
		D: LastActor is Valid && ThisActor is valid and not the same
			- Call UnHighlightActor on LastActor and HighlightActor on ThisActor
		E: LastActor is Valid && ThisActor is valid and the same
			- Do nothing.
	*/

	if (LastActor == nullptr) {
		if (ThisActor != nullptr) {
			//Case B
			ThisActor->HighlightActor();
		}
		else {
			//Case A. We do nothing but show else statement for clarity.
		}
	}
	else { //LastActor is valid
		if (ThisActor == nullptr) {
			//Case C
			LastActor->UnHighlightActor();
		}
		else {
			//Both Actors are valid. We need to check if they are the same
			if (LastActor != ThisActor) {
			//Case D
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			else {
				//Case E. Do nothing. Keep statement for clarity.
			}
		}
	}

}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	check(MoveAction);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

