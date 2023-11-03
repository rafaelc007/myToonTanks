// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called every frame	
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category="Meshes")
	UStaticMeshComponent* BaseMesh;
	
	UPROPERTY(VisibleAnywhere, Category="Movement")
	class UProjectileMovementComponent* ProjectileMover;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	float DamageAmount = 5.f;

	UPROPERTY(EditDefaultsOnly, Category="Particles")
	UParticleSystem* HitParticles;

	UPROPERTY(EditDefaultsOnly, Category="Particles")
	class UParticleSystemComponent* SmokeTrail;

	UPROPERTY(EditDefaultsOnly, Category="Sounds")
	USoundBase* LaunchSound;

	UPROPERTY(EditDefaultsOnly, Category="Sounds")
	USoundBase* HitSound;

	UPROPERTY(EditDefaultsOnly, Category="Camera")
	TSubclassOf<UCameraShakeBase> HitCameraShakeClass;

	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HitComp,
		AActor*OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& hit
	);
};
