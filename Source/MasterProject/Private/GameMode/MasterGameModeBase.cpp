// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/MasterGameModeBase.h"

#include "Player/MainCharacter.h"
#include "Player/MainPlayerController.h"

AMasterGameModeBase::AMasterGameModeBase()
{
	DefaultPawnClass = AMainCharacter::StaticClass();
	PlayerControllerClass = AMainPlayerController::StaticClass(); 
}
