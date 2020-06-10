// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class  ScreenDevice
{
public:
	ScreenDevice()
	{
		Init();
	};
	~ScreenDevice()
	{
		
	};
	//��Ļ�ֱ��ʿ�
	int ScreenWidth;
	//��Ļ�ֱ��ʸ�
	int ScreenHeight;
	//��Ļ����
	unsigned char* FrameBuff;

	void Init()
	{
		//��Ļ���طֱ���
		ScreenWidth = 1024;
		ScreenHeight = 1024;
		//��Ļ����  ÿ��������RGBA ����4�ֽ�
		FrameBuff = (unsigned char*)malloc(ScreenWidth * ScreenHeight * 4);

		//Test
		for (int i = ScreenHeight; i >= 0; i--)
		{
			for (int j = ScreenWidth; j >= 0; j--)
			{
				//R
				FrameBuff[i * ScreenWidth + j] = 0x0;
				//G
				FrameBuff[i * ScreenWidth + j + 1] = 0xFF;
				//B
				FrameBuff[i * ScreenWidth + j + 2] = 0x0;
				//A
				FrameBuff[i * ScreenWidth + j + 3] = 0xFF;
			}
		}
	}
};
