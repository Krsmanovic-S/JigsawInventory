// Copyright 2024 Stefan Krsmanovic. All Rights Reserved.


#include "JigsawInventoryComponent.h"

#include "HelperFunctionLibrary.h"
#include "Data/JigsawInventoryInfo.h"
#include "Net/UnrealNetwork.h"


UJigsawInventoryComponent::UJigsawInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UJigsawInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UJigsawInventoryComponent, CurrentItems);
}

bool UJigsawInventoryComponent::IsOwnerOnServer() const
{
	if(GetOwner() != nullptr)
	{
		const AController* OwnerController = GetOwner()->GetInstigatorController();

		if(OwnerController && OwnerController->IsLocalPlayerController()) return true;
	}
	
	return false;
}

void UJigsawInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentItems.SetNum(BasicSlotAmount, false);

	AddStartupItems();

	// DebugInventory();
}

void UJigsawInventoryComponent::AddStartupItems()
{
	for(FItemRowStruct& ItemRowStruct : DefaultItems)
	{
		FItemStruct ItemToBeAdded =
			UHelperFunctionLibrary::GetItemFromDataTable(InventoryData->ItemDataTable, ItemRowStruct.ItemRowName);

		// Need to make sure we have authority here, otherwise the AddItem method will get executed twice
		if(ItemToBeAdded.IsValid() && GetOwner()->HasAuthority())
		{
			ItemToBeAdded.CurrentStack = ItemRowStruct.Amount;

			Server_AddItem(ItemToBeAdded);
		}
	}
}

void UJigsawInventoryComponent::DebugInventory()
{
	FString RowString = "";
	
	for(int i = 0; i < BasicSlotAmount; i++)
	{
		if(i != 0 && i % MaxSlotsPerRow == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *RowString);
			UE_LOG(LogTemp, Warning, TEXT("---------------"));

			RowString.Empty();
		}
		
		if(CurrentItems[i].IsValid())
		{
			FString ItemNameString = "- ";

			ItemNameString += CurrentItems[i].Name[0];

			RowString += ItemNameString;
		}
		else RowString += "- 0 ";
	}

	UE_LOG(LogTemp, Warning, TEXT("%s"), *RowString);
}

TPair<int32, int32> UJigsawInventoryComponent::GetIndexRangeForItem(const FItemStruct& InItem)
{
	int32 CalculatedWidth = InItem.ItemWidth, CalculatedHeight = InItem.ItemHeight;

	// Direction only impacts items that are not square-shaped
	if(InItem.ItemWidth != InItem.ItemHeight)
	{
		if(InItem.CurrentItemDirection == EItemDirection::Down || InItem.CurrentItemDirection == EItemDirection::Up)
		{
			CalculatedHeight = InItem.ItemWidth;
			CalculatedWidth = InItem.ItemHeight;
		}
	}

	TPair<int32, int32> Result;

	// We need to lower each by one first to correctly check indexes,
	// for example an item with a width of 5 will move up only 4 indexes
	Result.Key = CalculatedWidth - 1;
	Result.Value = CalculatedHeight - 1;

	switch(InItem.CurrentItemDirection)
	{
	case EItemDirection::Left:
		Result.Key *= -1;
		break;
	case EItemDirection::Up:
		Result.Value *= -1;
		break;
	default: break;
	}
	
	return Result;
}

void UJigsawInventoryComponent::AssignItemToSlots(const int32& FirstSlot, const FItemStruct& ItemToAssign)
{
	const TPair<int32, int32> ItemWidthAndHeight = GetIndexRangeForItem(ItemToAssign);

	for(int i = 0; i <= FMath::Abs(ItemWidthAndHeight.Key); i++)
	{
		CurrentItems[FirstSlot + i] = ItemToAssign;
		
		for(int j = 1; j <= FMath::Abs(ItemWidthAndHeight.Value); j++)
		{
			CurrentItems[FirstSlot + i + j * MaxSlotsPerRow] = ItemToAssign;
		}
	}
}

bool UJigsawInventoryComponent::CanItemFitInSlot(int32 IndexToCheck, const FItemStruct& InItem) const
{
	if(InItem.ItemWidth == 1 && InItem.ItemHeight == 1) return true;
	
	const TPair<int32, int32> ItemWidthAndHeight = GetIndexRangeForItem(InItem);
	
	for(int i = 0; i <= FMath::Abs(ItemWidthAndHeight.Key); i++)
	{
		const int32 CurrentRow = IndexToCheck / MaxSlotsPerRow;
		const int32 MinIndexInRow = CurrentRow * MaxSlotsPerRow;
		const int32 MaxIndexInRow = MinIndexInRow + MaxSlotsPerRow - 1;

		// If the width of the item exceeds the current row in any way we cannot fit it here
		if(IndexToCheck + i > MaxIndexInRow || IndexToCheck + i < MinIndexInRow) return false;
		
		for(int j = i; j <= FMath::Abs(ItemWidthAndHeight.Value); j++)
		{
			if(!CurrentItems.IsValidIndex(IndexToCheck + i + j * MaxSlotsPerRow) ||
				CurrentItems[IndexToCheck + i + j * MaxSlotsPerRow].IsValid())
			{
				return false;
			}
		}
	}	
	
	return true;
}

void UJigsawInventoryComponent::Server_AddItem_Implementation(FItemStruct ItemToAdd)
{
	if(!ItemToAdd.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Tried to add an invalid item in %hs"), __FUNCTION__);
		return;
	}

	// Look to increase a stack of an existing item
	for(int i = 0; i < BasicSlotAmount; i++)
	{
		if(ItemToAdd.CurrentStack == 0)
		{
			LastAddedItemStack = 0;
			
			if(IsOwnerOnServer()) Multicast_UpdateInventoryUI();
			
			return;
		}

		FItemStruct& CurrentItem = CurrentItems[i];

		// Found the same item
		if(CurrentItem.IsValid() && ItemToAdd == CurrentItem)
		{
			// Found item isn't maxed on capacity
			if(CurrentItem.CurrentStack < CurrentItem.MaximumStack)
			{
				// Can we take in the entire input item?
				if(CurrentItem.CurrentStack + ItemToAdd.CurrentStack < CurrentItem.MaximumStack)
				{
					CurrentItem.CurrentStack += ItemToAdd.CurrentStack;

					LastAddedItemStack = 0;
					
					if(IsOwnerOnServer()) Multicast_UpdateInventoryUI();
					
					return;
				}

				ItemToAdd.CurrentStack -= (CurrentItem.MaximumStack - CurrentItem.CurrentStack);
				CurrentItem.CurrentStack = CurrentItem.MaximumStack;

				LastAddedItemStack = ItemToAdd.CurrentStack;
			}
		}
	}

	// Look to add a new item into an empty slot
	for(int i = 0; i < BasicSlotAmount; i++)
	{
		if(!CurrentItems[i].IsValid() && CanItemFitInSlot(i, ItemToAdd))
		{
			if(ItemToAdd.CurrentStack <= ItemToAdd.MaximumStack)
			{
				AssignItemToSlots(i, ItemToAdd);

				LastAddedItemStack = 0;

				if(IsOwnerOnServer()) Multicast_UpdateInventoryUI();
				
				return;
			}

			FItemStruct CopyItem = ItemToAdd;
			CopyItem.CurrentStack = ItemToAdd.MaximumStack;

			AssignItemToSlots(i, CopyItem);

			ItemToAdd.CurrentStack -= ItemToAdd.MaximumStack;
		}
	}

	// Reaching this point means we failed to add the item entirely so we need to remember the left over amount
	LastAddedItemStack = ItemToAdd.CurrentStack;

	if(IsOwnerOnServer()) Multicast_UpdateInventoryUI();
}

void UJigsawInventoryComponent::Multicast_UpdateInventoryUI_Implementation()
{
	OnInventoryUpdated.Broadcast();
}

void UJigsawInventoryComponent::OnRep_CurrentItems()
{
	Multicast_UpdateInventoryUI();
}
