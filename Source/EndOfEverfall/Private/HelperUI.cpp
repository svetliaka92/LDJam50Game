// Fill out your copyright notice in the Description page of Project Settings.


#include "HelperUI.h"
#include "Components/Image.h"


void UHelperUI::SetClickHelperVisible(bool bVisible)
{
	if (bVisible == bImageVisible)
	{
		return;
	}

	bImageVisible = bVisible;

	if (IsValid(ClickImage))
	{
		ClickImage->SetVisibility((bVisible) ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
	}
}
