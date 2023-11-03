// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	this->BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	this->RootComponent = BaseMesh;

	this->ProjectileMover = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMover"));
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	// Bound OnHit to be called on hit events
	BaseMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(
	UPrimitiveComponent* HitComp,
	AActor*OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& hit
)
{
	AActor* owner = GetOwner();
	if (owner == nullptr)
	{
		Destroy();
		return;
	}

	auto myInstigator = owner->GetInstigatorController();
	auto damageTypeClass = UDamageType::StaticClass();
		if (OtherActor && OtherActor != this && OtherActor != owner){
			UGameplayStatics::ApplyDamage(OtherActor, this->DamageAmount, myInstigator, this, damageTypeClass);
			if (HitParticles)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), this->HitParticles, OtherActor->GetActorTransform());
			}
			Destroy();
		}
	Destroy();
}
