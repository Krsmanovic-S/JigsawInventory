// Copyright 2024 Stefan Krsmanovic. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Data/JigsawEnumsAndStructs.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HelperFunctionLibrary.generated.h"

class UWidget;

/* Library of useful functions used within the plugin, can be used in Blueprints and in C++ */
UCLASS(Abstract, NotBlueprintable, NotBlueprintType, ClassGroup = "Complete Jigsaw Inventory")
class COMPLETEJIGSAWINVENTORY_API UHelperFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/**
	 * An item struct is valid if the items name isn't 'None' and its stack is greater than 0.
	 * This exists for checking item validity in blueprints as the IsValid method cannot be used there
	 * 
	 * @param Item The item struct we are checking
	 * @return Is the passed in struct valid
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Helper Functions|Item Utilities")
	static bool DoesItemExist(FItemStruct Item);

	/**
	 * Get the item struct from the data table associated with the inventory
	 * 
	 * @param InputTable Data table to look into
	 * @param RowName Name of the row to look for (RowName column in data table)
	 * @return Struct that represents the item at the given data table row
	 */
	UFUNCTION(BlueprintCallable, Category = "Helper Functions|Item Utilities")
	static FItemStruct GetItemFromDataTable(UDataTable* InputTable, const FName& RowName);

	/**
	 * Loops parent to parent starting at the input widget until it finds
	 * one that corresponds to the class that was looked for
	 * 
	 * @param InWidget The widget where the search starts
	 * @param ClassToLookFor Widget class that we are looking for
	 * @return Pointer to the found widget or null if we could't find anything
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Helper Functions|Widget Utilities", meta = (ReturnDisplayName = "ParentWidget"))
	static UObject* GetParentWidgetOfClass(UWidget* InWidget, UClass* ClassToLookFor);
};
