// Copyright 2024 Stefan Krsmanovic. All Rights Reserved.


#include "Widgets/ItemDisplayWidget.h"

#include "HelperFunctionLibrary.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Widgets/InventorySlotWidget.h"

void UItemDisplayWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UItemDisplayWidget::InitializeDisplayWidget(const int32 SlotSize, const UInventorySlotWidget* OwningSlot) const
{
	if(!IsVisible() || OwningSlot == nullptr || !OwningSlot->SlotItem.IsValid()) return;
	
	RootSizeBox->SetWidthOverride(SlotSize * OwningSlot->SlotItem.ItemWidth);
	RootSizeBox->SetHeightOverride(SlotSize * OwningSlot->SlotItem.ItemHeight);

	if(OwningSlot->SlotItem.CurrentStack > 1)
	{
		const FString& ItemStack = FString::FromInt(OwningSlot->SlotItem.CurrentStack);
		DisplayedItemStack->SetText(FText::FromString(ItemStack));		
	}
	else DisplayedItemStack->SetVisibility(ESlateVisibility::Hidden);

	DisplayedItemThumbnail->SetBrushFromTexture(OwningSlot->SlotItem.Thumbnail);

	switch(OwningSlot->SlotItem.CurrentItemDirection)
	{
	case EItemDirection::Left:
		DisplayedItemThumbnail->SetRenderScale(FVector2D(-1.0f, 0.0f));
		break;
	case EItemDirection::Down:
		DisplayedItemThumbnail->SetRenderTransformAngle(90.0f);
		break;
	case EItemDirection::Up:
		DisplayedItemThumbnail->SetRenderTransformAngle(-90.0f);
		break;
	default: break;
	}
}
