// Copyright 2024 Stefan Krsmanovic. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/JigsawEnumsAndStructs.h"
#include "InventorySlotWidget.generated.h"

class USizeBox;
class UImage;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = "Inventory Widgets")
class COMPLETEJIGSAWINVENTORY_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()

	friend class UJigsawInventoryWidget;
	
public:

	virtual void NativeConstruct() override;
	
private:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> RootSizeBox;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> SlotImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ItemImage;
	
	UPROPERTY()
	TObjectPtr<UJigsawInventoryWidget> OwningInventoryWidget;
	
	/* This index corresponds to the CurrentItems array of the inventory component this slot belongs to */
	UPROPERTY()
	int32 SlotIndex = -1;

	/**
	 * Represents what type of item does this slot accept, by default every slot can accept 
	 * everything. If you want to change this to a TArray variable you of course can and slots
	 * could take in multiple types of items. Currently only relevant for equipment slots
	 */
	UPROPERTY(EditInstanceOnly, Category = "Inventory Slot")
	EItemCategory AcceptableItemType = EItemCategory::Everything;

	/* What item is in this slot */
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Slot", meta = (AllowPrivateAccess = true))
	FItemStruct SlotItem;
};
