// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksGameMode.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	this->mCurrentHealth = MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	this->ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::DamageTaken(
	AActor* DamagedActor,
	float Damage,
	const UDamageType* DamageType,
	AController* Instigator,
	AActor* DamageCauser)
{
	if (Damage <= 0.f) return;

	this->mCurrentHealth -= Damage;
	if (mCurrentHealth <= 0.f && this->ToonTanksGameMode)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is dead"), *this->GetOwner()->GetActorNameOrLabel());
		this->ToonTanksGameMode->ActorDied(this->GetOwner());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s took %f damage. Remaining health %f"), *this->GetOwner()->GetActorNameOrLabel(), Damage, mCurrentHealth);
	}
}