// Copyright Norse Game Studio

#pragma once

#include "CoreMinimal.h"
#include "Characters/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
	

public:

	AAuraEnemy();

	/** Begin Enemyinterface	*/
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

	/** End Enemyinterface	*/

protected:

	virtual void BeginPlay() override;
};
