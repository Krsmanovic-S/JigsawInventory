// Copyright 2024 Stefan Krsmanovic. All Rights Reserved.


#include "Widgets/JigsawInventoryWidget.h"

#include "JigsawInventoryComponent.h"
#include "Components/UniformGridPanel.h"
#include "Data/JigsawInventoryInfo.h"
#include "Widgets/InventorySlotWidget.h"

void UJigsawInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UJigsawInventoryWidget::InitializeInventoryWidget(UJigsawInventoryComponent* InInventoryComp)
{
	// We don't need to initialize a widget that was already initialized
	if(InventoryComp != nullptr && InventoryComp == InInventoryComp) return;
	
	if(InInventoryComp != nullptr)
	{
		InventoryComp = InInventoryComp;

		// Binding Inventory Component delegates
		if(!InventoryComp->OnInventoryUpdated.IsBound())
		{
			InventoryComp->OnInventoryUpdated.AddDynamic(this, &UJigsawInventoryWidget::RefreshAllSlots);
		}
		
		ConstructInitialSlots();

		const AController* OwnerController = InventoryComp->GetOwner()->GetInstigatorController();

		// We want to construct Item Use Definitions for Player-owned inventories as they are the only
		// ones right now that can use items. Feel free to change this if you want other pawns to use items
		if(OwnerController && OwnerController->IsA<APlayerController>()) ConstructUseDefinitions();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Null inventory passed into %hs"), __FUNCTION__);
		RemoveFromParent();
	}
}

void UJigsawInventoryWidget::RefreshAllSlots()
{
	
}

void UJigsawInventoryWidget::ConstructInitialSlots()
{
	int32 CurrentRow = 0, CurrentColumn = 0;
	
	InventoryGrid->ClearChildren();
	InventorySlots.Empty();
	
	for(int i = 0; i < InventoryComp->GetTotalSlots(); i++)
	{
		// Did we reach the maximum amount of slots in the current row?
		if(CurrentColumn == InventoryComp->GetMaxSlotsPerRow())
		{
			CurrentColumn = 0;
			CurrentRow++;
		}

		if(UInventorySlotWidget* CurrentSlot =
			NewObject<UInventorySlotWidget>(this, InventoryComp->GetInventoryData()->SlotWidgetClass))
		{
			// First we set all the required information for the slot
			CurrentSlot->OwningInventoryWidget = this;

			// And then we want to add it to the grid panel as well as the TArray so we can keep track of it
			InventorySlots.Add(CurrentSlot);
			InventoryGrid->AddChildToUniformGrid(CurrentSlot, CurrentRow, CurrentColumn);
			
			CurrentColumn++;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Unable to create Inventory Slot in %hs"), __FUNCTION__);
			return;
		}
	}
}

void UJigsawInventoryWidget::ConstructUseDefinitions()
{
	
}
