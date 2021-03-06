/*=================================================
* FileName: TimePlugin.h
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

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "TimeManager.h"

DECLARE_LOG_CATEGORY_EXTERN(TimePlugin, Log, All);

class TIMEPLUGIN_API FTimePlugin : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void EnforceSingletonActor(UWorld* World);
	ATimeManager* SpawnSingletonActor(UWorld* World);
	void InitSingletonActor(UWorld* World, const UWorld::InitializationValues IVS);

	ATimeManager* GetSingletonActor(UObject* WorldContextObject);

	/**
	* Singleton-like access to this module's interface.  This is just for convenience!
	* Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	*
	* @return Returns singleton instance, loading the module on demand if needed
	*/
	static inline FTimePlugin& Get()
	{
		return FModuleManager::LoadModuleChecked< FTimePlugin >("TimePlugin");
	}

	/**
	* Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	*
	* @return True if the module is loaded and ready to use
	*/
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("TimePlugin");
	}
};
