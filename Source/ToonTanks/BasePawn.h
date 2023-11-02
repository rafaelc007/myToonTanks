// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDestruction();

	UFUNCTION(BluePrintCallable)
	void SetTurretRotSpeed(float speed);

private:
	UPROPERTY(VisibleAnywhere, Category="Capsule")
	class UCapsuleComponent* capsuleComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* baseMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* turretMesh;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* projectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category="Movement")
	float mTurretRotSpeed;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

protected:
	void RotateTurret(FVector lookAtTarget);

	void Fire();
};
