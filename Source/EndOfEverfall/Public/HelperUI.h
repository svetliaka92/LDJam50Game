// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HelperUI.generated.h"

class UImage;

UCLASS()
class ENDOFEVERFALL_API UHelperUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetClickHelperVisible(bool bVisible);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidgetOptional))
	UImage* ClickImage = nullptr;

	bool bImageVisible = false;
};
