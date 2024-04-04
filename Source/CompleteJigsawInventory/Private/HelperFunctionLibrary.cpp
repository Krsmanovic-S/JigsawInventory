// Copyright 2024 Stefan Krsmanovic. All Rights Reserved.


#include "HelperFunctionLibrary.h"

#include "Blueprint/WidgetTree.h"

bool UHelperFunctionLibrary::DoesItemExist(FItemStruct Item)
{
	return Item.IsValid();
}

FItemStruct UHelperFunctionLibrary::GetItemFromDataTable(UDataTable* InputTable, const FName& RowName)
{
	if(InputTable != nullptr)
	{
		FItemStruct* ItemFromTable = InputTable->FindRow<FItemStruct>(RowName, "");

		if(ItemFromTable != nullptr) return *ItemFromTable;
	}
	else UE_LOG(LogTemp, Error, TEXT("Passed in a null data table in %hs"), __FUNCTION__);
    
	return FItemStruct();
}

UObject* UHelperFunctionLibrary::GetParentWidgetOfClass(UWidget* InWidget, UClass* ClassToLookFor)
{
	if(const UObject* Top = InWidget->GetOuter())
	{
		for(;;)
		{
			UObject* CurrentOuter = Top->GetOuter();

			if(CurrentOuter->IsA(ClassToLookFor)) { return CurrentOuter; }

			if(CurrentOuter->IsA<UWidgetTree>() || CurrentOuter->IsA<UWidget>())
			{
				Top = CurrentOuter;
			}
			else { return nullptr; }
		}
	}
 
	return nullptr;
}
