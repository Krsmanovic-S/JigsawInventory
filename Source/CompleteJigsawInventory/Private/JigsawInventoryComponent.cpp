// Copyright 2024 Stefan Krsmanovic. All Rights Reserved.


#include "JigsawInventoryComponent.h"


UJigsawInventoryComponent::UJigsawInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UJigsawInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}
