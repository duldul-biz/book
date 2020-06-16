// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUICpp.h"
#include "ImageUtils.h"
#include "Engine/Texture2DDynamic.h"
#include "Engine/Engine.h"
#include "ClothingSystemEditor/Private/ClothingSystemEditorPrivatePCH.h"

static UTexture2D* CreateTextureFromBGRA(unsigned char* data, int width, int height)
{
	

}

void UMainUICpp::NativeConstruct()
{	
	if (UImage* img = Cast<UImage>(GetWidgetFromName(FName(TEXT("MainImage")))))
	{
		MainImage = img;
	}

	//��ȡ�豸��� Ȼ���ʼ��
	float X = GSystemResolution.ResX;
	float Y = GSystemResolution.ResY;
	HScreenDevice::GetInstance()->Init(X,Y);

	//��ʼ�����̱���
	MainTexture = UTexture2D::CreateTransient(HScreenDevice::GetInstance()->ScreenWidth, HScreenDevice::GetInstance()->ScreenHeight, PF_B8G8R8A8);
	MainColors = new FColor[HScreenDevice::GetInstance()->ScreenWidth *  HScreenDevice::GetInstance()->ScreenHeight];

	//���û���һ��Cube
	HScreenDevice::GetInstance()->shape = new HCube();

}

void UMainUICpp::Update(float InDeltaTime)
{
	//1������
	HScreenDevice::GetInstance()->Draw();
	//2��֡������ʾ����Ļ�������ǰ�FrameBuffer ������һ������MainTexture Ȼ�����ڵ�UE��UImage���棩
	for (int i = 0; i < HScreenDevice::GetInstance()->ScreenHeight; i++)
	{
		for (int j = 0; j < HScreenDevice::GetInstance()->ScreenWidth; j++)
		{
			MainColors[i * HScreenDevice::GetInstance()->ScreenWidth + j].R = HScreenDevice::GetInstance()->FrameBuff[(i * HScreenDevice::GetInstance()->ScreenWidth + j) * 4 + 0];
			MainColors[i * HScreenDevice::GetInstance()->ScreenWidth + j].G = HScreenDevice::GetInstance()->FrameBuff[(i * HScreenDevice::GetInstance()->ScreenWidth + j) * 4 + 1];
			MainColors[i * HScreenDevice::GetInstance()->ScreenWidth + j].B = HScreenDevice::GetInstance()->FrameBuff[(i * HScreenDevice::GetInstance()->ScreenWidth + j) * 4 + 2];
			MainColors[i * HScreenDevice::GetInstance()->ScreenWidth + j].A = HScreenDevice::GetInstance()->FrameBuff[(i * HScreenDevice::GetInstance()->ScreenWidth + j) * 4 + 3];
		}
	}

#if WITH_EDITORONLY_DATA
	MainTexture->MipGenSettings = TMGS_NoMipmaps;
#endif
	MainTexture->NeverStream = true;

	MainTexture->SRGB = 0;

	FTexture2DMipMap& Mip = MainTexture->PlatformData->Mips[0];
	void* Data = Mip.BulkData.Lock(LOCK_READ_WRITE);

	FMemory::Memcpy(Data, MainColors, HScreenDevice::GetInstance()->ScreenWidth *  HScreenDevice::GetInstance()->ScreenHeight * 4);
	Mip.BulkData.Unlock();
	MainTexture->UpdateResource();

	if(MainImage)
	{
		MainImage->SetBrushFromTexture(MainTexture );
	}
}

