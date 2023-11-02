// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "PawnTank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API APawnTank : public ABasePawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnTank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BluePrintCallable)
	void SetSpeed(float speed);

	UFUNCTION(BluePrintCallable)
	void SetTurnRate(float rate);

	void HandleDestruction();

	APlayerController* GetTankPlayerController() const;

private:
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* springArm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* camera;

	UPROPERTY(EditDefaultsOnly, Category="Movement")
	float mSpeed;

	UPROPERTY(EditDefaultsOnly, Category="Movement")
	float mTurnRate;

	void Move(float);
	void Turn(float);
	void AimTurret();

	APlayerController* mPlayerControllerRef;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
