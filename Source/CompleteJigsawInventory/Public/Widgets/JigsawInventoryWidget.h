// Copyright 2024 Stefan Krsmanovic. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JigsawInventoryWidget.generated.h"

class UJigsawInventoryComponent;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = "Inventory Widgets")
class COMPLETEJIGSAWINVENTORY_API UJigsawInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "Jigsaw Inventory Widget")
	void InitializeInventoryWidget();

private:
	
	TObjectPtr<UJigsawInventoryComponent> InventoryComponent;

	
};
