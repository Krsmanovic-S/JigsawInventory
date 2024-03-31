// Copyright 2024 Stefan Krsmanovic. All Rights Reserved.


#include "Widgets/ItemDisplayWidget.h"

#include "Components/Image.h"
#include "Components/SizeBox.h"

void UItemDisplayWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UItemDisplayWidget::InitializeDisplayWidget(const int32& InSlotSize, const FItemStruct& InItem) const
{
	RootSizeBox->SetWidthOverride(InSlotSize);
	RootSizeBox->SetHeightOverride(InSlotSize);
	
	if(InItem.IsValid())
	{
		DisplayedItemThumbnail->SetBrushFromTexture(InItem.Thumbnail);
	}
}
