// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "PawnTower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API APawnTower : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BluePrintCallable)
	void setFireRange(float fireRange);

	UFUNCTION(BluePrintCallable)
	void setFireRate(float fireRate);

	void HandleDestruction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	class APawnTank* mTarget;

	UPROPERTY(EditDefaultsOnly)
	float mFireRange;

	FTimerHandle mFireRateTimerHandle;

	UPROPERTY(EditDefaultsOnly)
	float mFireRate;

	void CheckFireConditions();
	void AimTarget();
	bool InFireRange();

};
