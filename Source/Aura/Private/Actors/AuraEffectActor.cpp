// Copyright Norse Game Studio


#include "Actors/AuraEffectActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraEffectActor::AAuraEffectActor()
{

	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));

}

//void AAuraEffectActor::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSwwep, const FHitResult& SweepResult)
//{
//	if (OtherActor != nullptr) {
//
//		//TODO: Change this to apply a Gameplay Effect. For now using const_cast as a hack.
//		if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor)) {
//			const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));
//
//			UAuraAttributeSet* MutableAuraAttributeSet = const_cast<UAuraAttributeSet*>(AuraAttributeSet);
//
//			MutableAuraAttributeSet->SetHealth(AuraAttributeSet->GetHealth() + 25.f);
//			//MutableAuraAttributeSet->SetMana(AuraAttributeSet->GetMana() - 25.f);
//			Destroy();
//		}
//	}
//}
//
//void AAuraEffectActor::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//
//}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	/*Sphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnSphereBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::OnSphereEndOverlap);*/
}

