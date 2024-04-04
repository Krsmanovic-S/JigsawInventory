// Copyright 2024 Stefan Krsmanovic. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JigsawInventoryWidget.generated.h"

class UJigsawInventoryComponent;
class UUniformGridPanel;
class UInventorySlotWidget;

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
	void InitializeInventoryWidget(UJigsawInventoryComponent* InInventoryComp);

	UFUNCTION()
	void RefreshAllSlots();

protected:

	void ConstructInitialSlots();

	void ConstructUseDefinitions();
	
private:
	
	TObjectPtr<UJigsawInventoryComponent> InventoryComp;
	
	/* Grid where all the slots are added */
	UPROPERTY(BlueprintReadWrite, Category = "Inventory Widget", meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UUniformGridPanel> InventoryGrid;

	UPROPERTY()
	TArray<TObjectPtr<UInventorySlotWidget>> InventorySlots;
};
