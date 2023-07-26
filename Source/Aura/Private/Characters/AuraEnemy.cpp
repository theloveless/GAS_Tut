// Copyright Norse Game Studio


#include "Characters/AuraEnemy.h"
#include "Aura.h"

AAuraEnemy::AAuraEnemy()
{
	if (GetMesh() != nullptr) {
		GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	}
}	

void AAuraEnemy::HighlightActor()
{
	if (GetMesh() != nullptr) {
		GetMesh()->SetRenderCustomDepth(true);
		GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	}

	if (Weapon != nullptr) {
		Weapon->SetRenderCustomDepth(true);
		Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	}
}

void AAuraEnemy::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);

	if (Weapon != nullptr) {
		Weapon->SetRenderCustomDepth(false);
	}
}
