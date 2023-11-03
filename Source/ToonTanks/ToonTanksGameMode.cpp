// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"
#include "PawnTower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    HandleGameStart();
}

void AToonTanksGameMode::ActorDied(AActor* deadActor)
{
    if (deadActor == Tank)
    {
        Tank->HandleDestruction();
        if (ToonTanksPlayerController)
        {
            ToonTanksPlayerController->SetPlayerEnabledState(false);
        }
        GameOver(false);
    } else if (APawnTower* destroyedTower = Cast<APawnTower>(deadActor)) 
    {
        destroyedTower->HandleDestruction();
        --this->TargetTowers;
        if (TargetTowers <= 0)
        {
            GameOver(true);
        }
    }
}

void AToonTanksGameMode::HandleGameStart()
{
    this->Tank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
    this->ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
    this->TargetTowers = GetTargetTowerCount();

    StartGame();

    if (ToonTanksPlayerController)
    {
        // disable controller before start
        ToonTanksPlayerController->SetPlayerEnabledState(false);

        FTimerHandle playerEnableTimerHandle;
        FTimerDelegate inputDelegate = FTimerDelegate::CreateUObject(
            ToonTanksPlayerController,
            &AToonTanksPlayerController::SetPlayerEnabledState,
            true
            );
        GetWorldTimerManager().SetTimer(playerEnableTimerHandle, inputDelegate, StartDelay, false);
    }
}


int32 AToonTanksGameMode::GetTargetTowerCount()
{
    TArray<AActor*> allTowers;
    UGameplayStatics::GetAllActorsOfClass(this, APawnTower::StaticClass(), allTowers);

    UE_LOG(LogTemp, Warning, TEXT("Found %d towers"), allTowers.Num());

    return allTowers.Num();
}

