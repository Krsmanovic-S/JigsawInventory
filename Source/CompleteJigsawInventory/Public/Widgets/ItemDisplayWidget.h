// Copyright 2024 Stefan Krsmanovic. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/JigsawEnumsAndStructs.h"
#include "ItemDisplayWidget.generated.h"

class UInventorySlotWidget;
class UTextBlock;
class UImage;
class USizeBox;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = "Inventory Widgets")
class COMPLETEJIGSAWINVENTORY_API UItemDisplayWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "Item Display Widget Functions")
	void InitializeDisplayWidget(const int32 SlotSize, const UInventorySlotWidget* OwningSlot) const;

private:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> RootSizeBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> DisplayedItemThumbnail;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> DisplayedItemStack;
};
