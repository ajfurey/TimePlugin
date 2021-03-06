/*=================================================
* FileName: TimePlugin.cpp
* Created by: EvoPulse
* Project name: EnvironmentProject
* Unreal Engine version: 4.25.0
* Created on:
*=================================================
*For parts referencing UE4 code, the following copyright applies:
* Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
*
* Feel free to use this software in any commercial/free game.
* Selling this as a plugin/item, in whole or part, is not allowed.
* See LICENSE for full licensing details.
* =================================================*/

#include "TimePlugin.h"
#include "EngineUtils.h"
#include "Editor/EditorEngine.h"

DEFINE_LOG_CATEGORY(TimePlugin);

void FTimePlugin::StartupModule()
{
	UE_LOG(TimePlugin, Warning, TEXT("TimePlugin StartupModle() Register OnWorldCreated delegate"));

	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	//Auto create our TimeManager
	//This is called everytime UWorld is created, which is a lot in the editor (every opened BP gets a UWorld)
	FWorldDelegates::OnPostWorldInitialization.AddRaw(this, &FTimePlugin::InitSingletonActor);
}

void FTimePlugin::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FWorldDelegates::OnPostWorldInitialization.RemoveAll(this);
}

void FTimePlugin::EnforceSingletonActor(UWorld* World)
{
	//Make sure there is only one instance of this actor!
	//Actor is not blueprintable, but users will find other ways!!
	bool bFoundFirstInstance = false;
	for (TActorIterator<ATimeManager> ActorItr(World); ActorItr; ++ActorItr)
	{
		if (bFoundFirstInstance == false)
		{
			bFoundFirstInstance = true;
		}
		else
		{
			ActorItr->Destroy();
		}
	}
}

ATimeManager* FTimePlugin::SpawnSingletonActor(UWorld* World)
{
	FVector location = FVector(0, 0, 0);
	FRotator rotate = FRotator(0, 0, 0);
	FActorSpawnParameters SpawnInfo;
	return World->SpawnActor<ATimeManager>(ATimeManager::StaticClass(), location, rotate, SpawnInfo);
}

void FTimePlugin::InitSingletonActor(UWorld* World, const UWorld::InitializationValues IVS)
{
	//Make sure we are in the correct UWorld!
	if (World->WorldType == EWorldType::Game || EWorldType::PIE || EWorldType::GamePreview || EWorldType::GameRPC || EWorldType::Editor)
	{
		//If we already have a TimeManagerEditorActor in the editor level, do not spawn another one
		//This also auto spawns a TimeManagerActor in the game world, if the user somehow sneaks a map in
		//that has not been opened while the plugin was active!

		EnforceSingletonActor(World);

		for (TActorIterator<ATimeManager> ActorItr(World); ActorItr; ++ActorItr)
		{
			//If TimeManager already exists
			return;
		}

		//Spawn TimeManager since there isn't one already
		SpawnSingletonActor(World);
	}
}

ATimeManager* FTimePlugin::GetSingletonActor(UObject* WorldContextObject)
{
	UWorld* World = WorldContextObject->GetWorld();

	EnforceSingletonActor(World);

	for (TActorIterator<ATimeManager> ActorItr(World); ActorItr; ++ActorItr)
	{
		return *ActorItr;
	}

	//In the impossible case that we don't have an actor, spawn one!
	return SpawnSingletonActor(World);
}
	
IMPLEMENT_MODULE(FTimePlugin, TimePlugin)