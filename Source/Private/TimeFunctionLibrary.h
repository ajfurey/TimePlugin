/*=================================================
* FileName: TimeFunctionLibrary.h
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

#include "TimePlugin.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TimeFunctionLibrary.generated.h"

/*
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu.
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/

UCLASS()
class TIMEPLUGIN_API UTimeManagerFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

		UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Time Instance", Keywords = ""), meta = (WorldContext = "WorldContextObject"), Category = "TimeManager")
		static ATimeManager * GetTimeManager(UObject* WorldContextObject)
	{
		return FTimePlugin::Get().GetSingletonActor(WorldContextObject);
	}
};
