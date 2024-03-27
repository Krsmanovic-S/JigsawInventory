// Copyright 2024 Stefan Krsmanovic. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JigsawInventoryComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class COMPLETEJIGSAWINVENTORY_API UJigsawInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UJigsawInventoryComponent();

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	int32 TotalSlots = 20;

	UPROPERTY(EditAnywhere)
	int32 MaxSlotsPerRow = 5;

	
	
};
