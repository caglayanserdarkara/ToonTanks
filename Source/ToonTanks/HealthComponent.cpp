#include "HealthComponent.h"
#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"


UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	//When Owner of the component take damage, our DamageTaken functions will be called.

	ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
}


void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                   class AController* Instigator, AActor* DamageCauser)
{
	if (Damage <= 0.f)
	{
		return;
	}

	Health -= Damage;
	if (ToonTanksGameMode && Health <= 0.f)
	{
		ToonTanksGameMode->ActorDied(DamagedActor);
	}
}
