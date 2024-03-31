// Copyright 2024 Stefan Krsmanovic. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/JigsawEnumsAndStructs.h"
#include "ItemDisplayWidget.generated.h"

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

	void InitializeDisplayWidget(const int32& InSlotSize, const FItemStruct& InItem) const;

private:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> RootSizeBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> DisplayedItemThumbnail;	
};
