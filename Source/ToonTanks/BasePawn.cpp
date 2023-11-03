// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->capsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	this->RootComponent = capsuleComp;

	this->baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	baseMesh->SetupAttachment(capsuleComp);

	this->turretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurrentMesh"));
	turretMesh->SetupAttachment(baseMesh);

	this->projectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	projectileSpawnPoint->SetupAttachment(turretMesh);

}

void ABasePawn::RotateTurret(FVector lookAtTarget)
{
	FVector toTarget = lookAtTarget - turretMesh->GetComponentLocation();
	FRotator lookAtRotation = FRotator(0.f, toTarget.Rotation().Yaw, 0.f);
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	turretMesh->SetWorldRotation(
		FMath::RInterpTo(
			turretMesh->GetComponentRotation(),
			lookAtRotation,
			DeltaTime,
			mTurretRotSpeed
		)
	);
}

void ABasePawn::SetTurretRotSpeed(float speed)
{
	this->mTurretRotSpeed = speed;
}

void ABasePawn::Fire()
{
	auto projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileClass,
		projectileSpawnPoint->GetComponentLocation(),
		projectileSpawnPoint->GetComponentRotation());
	projectile->SetOwner(this);
}

void ABasePawn::HandleDestruction()
{
	if (this->ExplodeParticle) UGameplayStatics::SpawnEmitterAtLocation(
		GetWorld(),
		this->ExplodeParticle,
		this->GetActorTransform());

	if (this->DeathSound) UGameplayStatics::PlaySoundAtLocation(this, DeathSound, this->GetActorLocation());

	if (DeathCameraShakeClass) GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
}