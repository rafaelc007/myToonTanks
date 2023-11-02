// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnTank.h"
#include "PawnTower.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

void APawnTower::BeginPlay()
{
    Super::BeginPlay();

    mTarget = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(mFireRateTimerHandle, this, &APawnTower::CheckFireConditions, mFireRate, true);
}

void APawnTower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    AimTarget();

}

bool APawnTower::InFireRange()
{
    if (mTarget)
    {
        FVector targetLocation = mTarget->GetActorLocation();
        // Find distance to target
        float distanceToTarg = FVector::Dist(GetActorLocation(), targetLocation);

        // Check to see if target is in range
        if (distanceToTarg <= mFireRange)
        {
            return true;
        }
    }
    return false;
}

void APawnTower::AimTarget()
{
    if (InFireRange())
    {
        FVector targetLocation = mTarget->GetActorLocation();
        // If in range, rotate turret toward target
        RotateTurret(targetLocation);
    }
}

void APawnTower::CheckFireConditions()
{
    if (InFireRange())
    {
        Fire();
    }
}

void APawnTower::setFireRange(float fireRange)
{
    this->mFireRange = fireRange;
}

void APawnTower::setFireRate(float fireRate)
{
    this->mFireRate = fireRate;
}

void APawnTower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}