// Copyright 2024 Stefan Krsmanovic. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "JigsawInventoryInfo.generated.h"

class UItemDisplayWidget;
class UDataTable;
class UInventorySlotWidget;

/**
 * 
 */
UCLASS(Blueprintable, ClassGroup = "Complete Jigsaw Inventory")
class COMPLETEJIGSAWINVENTORY_API UJigsawInventoryInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory Defaults")
	int32 InventorySlotSize = 100;
	
    /* Data table representing every item in the game */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory Defaults")
    TObjectPtr<UDataTable> ItemDataTable;

	/**
	 * All classes below are used for spawning or creation purposes as we want
	 * to create blueprints for each of the properties and not generic C++ ones
	 */
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Defaults")
	TSubclassOf<UInventorySlotWidget> SlotWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Defaults")
	TSubclassOf<UItemDisplayWidget> DisplayWidgetClass;
};