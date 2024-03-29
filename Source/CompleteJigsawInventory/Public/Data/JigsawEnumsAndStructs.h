// Copyright 2024 Stefan Krsmanovic. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "JigsawEnumsAndStructs.generated.h"

/**
 * Enum used to represent the category of an item, used for tooltips as
 * well as for determining the acceptable item type of a particular UI slot
 */
UENUM(BlueprintType)
enum class EItemCategory : uint8
{
	Everything UMETA(DisplayName = "Everything"),
	Weapon UMETA(DisplayName = "Weapon"),
	Helmet UMETA(DisplayName = "Helmet"),
	BodyArmor UMETA(DisplayName = "Body Armor"),
	Arms UMETA(DisplayName = "Arms"),
	Legs UMETA(DisplayName = "Legs"),
	Boots UMETA(DisplayName = "Boots"),
	Consumable UMETA(DisplayName = "Consumable"),
	Currency UMETA(DisplayName = "Currency")
};

/* Struct representing items in the Inventory System */
USTRUCT(BlueprintType)
struct FItemStruct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	FString Name = "None";
};