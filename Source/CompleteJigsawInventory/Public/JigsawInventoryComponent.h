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

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Jigsaw Inventory Functions")
	void Server_AddItem(FItemStruct ItemToAdd);

	static TPair<int32, int32> GetIndexRangeForItem(const FItemStruct& InItem);
	
	void AssignItemToSlots(const int32& FirstSlot, const FItemStruct& ItemToAssign);
	
	bool CanItemFitInSlot(int32 IndexToCheck, const FItemStruct& InItem) const;
	
	UFUNCTION(BlueprintCallable, Category = "Jigsaw Inventory Functions")
	bool IsOwnerOnServer() const;
	
	UFUNCTION(NetMulticast, Reliable, Category = "Jigsaw Inventory Functions")
	void Multicast_UpdateInventoryUI();
	
	UFUNCTION(Category = "Jigsaw Inventory Functions")
	void OnRep_CurrentItems();
	
	FORCEINLINE int32 GetBasicSlotAmount() const { return BasicSlotAmount; }
	FORCEINLINE int32 GetMaxSlotsPerRow() const { return MaxSlotsPerRow; }
	FORCEINLINE UJigsawInventoryInfo* GetInventoryData() const { return InventoryData; }
	FORCEINLINE TArray<FItemStruct> GetCurrentItems() const { return CurrentItems; } 
	
protected:
	virtual void BeginPlay() override;
	
	void AddStartupItems();
	
private:

	UPROPERTY(EditAnywhere, Category = "Jigsaw Inventory Settings")
	int32 BasicSlotAmount = 20;

	UPROPERTY(EditAnywhere, Category = "Jigsaw Inventory Settings")
	int32 MaxSlotsPerRow = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Jigsaw Inventory Settings")
	TObjectPtr<UJigsawInventoryInfo> InventoryData;

	/** 
	 * Items that can be set in blueprints that will get added to the owner when the game 
	 * starts.  Uses the custom row struct to find items by name inside the ItemDataTable. 
	 * We cannot use TPair or TTuple here because they cannot be exposed to blueprints
	 */
	UPROPERTY(EditAnywhere, Category = "Jigsaw Inventory")
	TArray<FItemRowStruct> DefaultItems;
	
	UPROPERTY(ReplicatedUsing = OnRep_CurrentItems, BlueprintReadOnly,
		Category = "Jigsaw Inventory", meta = (AllowPrivateAccess = true))
	TArray<FItemStruct> CurrentItems;

public:
	
	UPROPERTY(BlueprintCallable, Category = "Jigsaw Inventory")
	FInventoryUpdated OnInventoryUpdated;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Jigsaw Inventory")
	FInventoryOpened OnInventoryOpened;

	UPROPERTY(BlueprintReadWrite, Category = "Jigsaw Inventory")
	bool HalveStackKeyPressed = false;

	UPROPERTY(BlueprintReadWrite, Category = "Jigsaw Inventory")
	bool SplitKeyPressed = false;

	/* Used for keeping track of whether an addition of an item was successful or only partial */
	UPROPERTY(BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = true))
	int32 LastAddedItemStack = 0;

	void DebugInventory();
};
