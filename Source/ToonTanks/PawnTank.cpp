// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"

APawnTank::APawnTank()
{
    this->springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArm"));
	springArm->SetupAttachment(RootComponent);

    this->camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(springArm);
}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();

    mPlayerControllerRef = Cast<APlayerController>(GetController());
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    AimTurret();
}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APawnTank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APawnTank::Turn);

    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &APawnTank::Fire);

}

void APawnTank::AimTurret()
{
    if (mPlayerControllerRef)
    {
        FHitResult hitResult;
        mPlayerControllerRef->GetHitResultUnderCursor(
            ECollisionChannel::ECC_Visibility,
            false,
            hitResult
            );
        RotateTurret(hitResult.ImpactPoint);
    }
}

void APawnTank::Move(float value)
{
    FVector moveVector = FVector::ZeroVector;
    float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    moveVector.X = mSpeed * DeltaTime * value;

    this->AddActorLocalOffset(moveVector, true);
}

void APawnTank::Turn(float value)
{
    FRotator deltaRotation = FRotator::ZeroRotator;
    float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    deltaRotation.Yaw = value * DeltaTime * mTurnRate;
    this->AddActorLocalRotation(deltaRotation, true);
}

void APawnTank::SetSpeed(float speed)
{
    this->mSpeed = speed;
}

void APawnTank::SetTurnRate(float rate)
{
    this->mTurnRate = rate;
}

APlayerController* APawnTank::GetTankPlayerController() const
{
    return mPlayerControllerRef;
}

void APawnTank::HandleDestruction()
{
    Super::HandleDestruction();
    // Don't destroy, otherwise the camera will be destroyed
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
}