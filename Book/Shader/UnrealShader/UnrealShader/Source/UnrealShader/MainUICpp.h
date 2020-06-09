// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Image.h"
#include "MainUICpp.generated.h"

/**
 * 
 */



UCLASS()
class UNREALSHADER_API UMainUICpp : public UUserWidget
{
	GENERATED_BODY()
protected:
	//��ʼ��
	void NativeConstruct() override;

	////Update����
	//UFUNCTION(BlueprintCallable)
	//void Update(float InDeltaTime);

private:
	// Image�ؼ� �൱����Ļ
	UImage* MainImage;
	// Imageÿ֡���Ƶ����� �������Ⱦ��ScreenDevice��ȡ�� FrameBuffer ��䵽���MainTexture
	UTexture2D* MainTexture;
	// �豸
	//ScreenDevice Device;
};
