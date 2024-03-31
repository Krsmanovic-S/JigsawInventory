// Copyright 2024 Stefan Krsmanovic. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/JigsawEnumsAndStructs.h"
#include "JigsawInventoryComponent.generated.h"

class UJigsawInventoryInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInventoryOpened);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInventoryUpdated);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class COMPLETEJIGSAWINVENTORY_API UJigsawInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UJigsawInventoryComponent();

	FORCEINLINE int32 GetTotalSlots() const { return TotalSlots; }
	FORCEINLINE int32 GetMaxSlotsPerRow() const { return MaxSlotsPerRow; }
	FORCEINLINE UJigsawInventoryInfo* GetInventoryData() const { return InventoryData; }
	
protected:
	virtual void BeginPlay() override;
	
	void AddStartupItems();
	
private:

	UPROPERTY(EditAnywhere, Category = "Jigsaw Inventory Settings")
	int32 TotalSlots = 20;

	UPROPERTY(EditAnywhere, Category = "Jigsaw Inventory Settings")
	int32 MaxSlotsPerRow = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Jigsaw Inventory Settings")
	TObjectPtr<UJigsawInventoryInfo> InventoryData;

	/** 
	 * Items that can be set in blueprints that will get added to the owner when the game 
	 * starts.  Uses the custom row struct to find items by name inside the ItemDataTable. 
	 * We cannot use TPair or TTuple here because they cannot be exposed to blueprints
	 */
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TArray<FItemRowStruct> DefaultItems;
	
	UPROPERTY()
	TArray<FItemStruct> CurrentItems;

public:
	
	UPROPERTY(BlueprintCallable, Category = "Jigsaw Inventory Component")
	FInventoryUpdated OnInventoryUpdated;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Jigsaw Inventory Component")
	FInventoryOpened OnInventoryOpened;
	
	UPROPERTY(BlueprintReadWrite, Category = "Jigsaw Inventory Component")
	bool IsInventoryOpen = false;

	UPROPERTY(BlueprintReadWrite, Category = "Jigsaw Inventory Component")
	bool HalveStackKeyPressed = false;

	UPROPERTY(BlueprintReadWrite, Category = "Jigsaw Inventory Component")
	bool SplitKeyPressed = false;
};
