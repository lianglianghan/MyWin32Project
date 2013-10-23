#include <Windows.h>
#include "resource.h"

#ifndef DOLLARS_H

#define DOLLARS_H

struct  
{
	int mybitmap;
	int mybitmapMask;
}

dollarsPicture[]=
{
	IDB_BITMAP23,IDB_BITMAP24,

}

;

class DollarsAndbombs
{
private:
	boolean isAlive;

public:
	//0--����� 1--��ը��  2--����ʱ��� 3--��ʱ����ͣ �������Ĵ�����
	int type;

	int speed;

	/*//λͼ�ı��(Դ�ļ���maskͼ�ļ���
	int map1,map2;*/

	//��ҵ�λ��
	int x,y;


	//��ҵĴ�С
	int cx,cy;

	//���
	HBITMAP myBitmap,myBitmapMask;

	BITMAP bitmap;


	DollarsAndbombs()
	{

	}

	DollarsAndbombs(int x,int y,int speed,int type)
	{
		this->x=x;
		this->y=y;
		this->speed=speed;
		this->type=type;

	}

	//����λͼ
	void loadMyBitmap(HINSTANCE hInstance)
	{
		this->myBitmap=LoadBitmap(hInstance,MAKEINTRESOURCE(dollarsPicture[this->type].mybitmap));
		this->myBitmapMask=LoadBitmap(hInstance,MAKEINTRESOURCE(dollarsPicture[this->type].mybitmapMask));

		GetObject(this->myBitmap,sizeof(BITMAP),&bitmap);
		cx=bitmap.bmWidth;
		cy=bitmap.bmHeight;
	}


	//��̬�仯λ��
	void Change()
	{
		this->y+=this->speed;
	}

	//��ʼ����������
	void Set(int x,int y,int speed,int type)
	{
		this->x=x;
		this->y=y;
		this->speed=speed;
		this->type=type;
	}

	//��������
	void setAlive(boolean status)
	{
		this->isAlive=status;
	}

	boolean isAlived()
	{
		return this->isAlive;
	}



};



#endif