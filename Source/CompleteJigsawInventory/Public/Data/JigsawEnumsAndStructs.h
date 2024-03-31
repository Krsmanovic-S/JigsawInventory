// Copyright 2024 Stefan Krsmanovic. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "JigsawEnumsAndStructs.generated.h"

class UTexture2D;

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

UENUM(BlueprintType)
enum class EItemDirection : uint8
{
	Right UMETA(DisplayName = "Right"),
	Down UMETA(DisplayName = "Down"),
	Left UMETA(DisplayName = "Left"),
	Up UMETA(DisplayName = "Up")
};

/**
 * Since we cannot use TPair or TTuple in Blueprints, we create this struct 
 * to serve our purpose. Used in assigning DefaultItems of the Inventory
 */
USTRUCT(BlueprintType)
struct FItemRowStruct
{
	GENERATED_BODY()

	/**
	 * Name of the row for the item inside the ItemDataTable,
	 * used when looking up said table to find the FItemStruct
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Row Struct")
	FName ItemRowName;

	/* What should the current stack of the found item be? */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Row Struct", meta = (ClampMin = "0"))
	int32 Amount = 1;
};

/* Struct representing items in the Inventory System */
USTRUCT(BlueprintType)
struct FItemStruct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	FString Name = "None";

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (ClampMin = 1))
	int32 ItemWidth = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (ClampMin = 1))
	int32 ItemHeight = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	TObjectPtr<UTexture2D> Thumbnail;
	
	UPROPERTY(BlueprintReadOnly, Category = "Item Properties")
	int32 CurrentStack = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (ClampMin = 1))
	int32 MaximumStack = 1;

	UPROPERTY(BlueprintReadOnly, Category = "Item Properties")
	EItemDirection CurrentItemDirection = EItemDirection::Right;

	/* An item is valid only if its name is not "None" and its stack is greater than 0 */
	bool IsValid() const { return Name != "None" && CurrentStack > 0; }

	/* Setting the name to "None" marks the item as empty, no need to change anything else */
	void Clear() { Name = "None"; }

	/**
	 * This operator overload is needed for when we are using the Contains() method on a 
	 * TArray of FItemStruct, as we need to explain to the engine what makes two structs equal
	 */
	bool operator==(const FItemStruct& OtherItem) const { return Name == OtherItem.Name; }
};