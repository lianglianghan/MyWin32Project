#include <Windows.h>
#include "resource.h"
#include <time.h>

#pragma comment(lib, "msimg32.lib")

#ifndef DOLLARS_H

#define DOLLARS_H

struct  
{
	int mybitmap;
	int mybitmapMask;
} dollarsPicture[]=
{
	IDB_BITMAP23,IDB_BITMAP24,
	IDB_BITMAP27,IDB_BITMAP28,
	IDB_BITMAP32,IDB_BITMAP31,
}
;

int recordPicture[10]={
	IDB_BITMAP30,IDB_BITMAP33,
	IDB_BITMAP34,IDB_BITMAP35,IDB_BITMAP36,IDB_BITMAP37,IDB_BITMAP38,
	IDB_BITMAP39,IDB_BITMAP40,IDB_BITMAP29
};

class Record
{
private:

	int currentRecord;

	int maxRecord;


	//��λ��ʮλ����λ
	int x,y,z;


	//�������
	int px,py;
	
	

public:

	HBITMAP myBitmap,myBitmap1,myBitmap2;
	HINSTANCE hInstance;

	BITMAP bitmap;

	int cx,cy;

	Record(int x1,int y1)
	{
		this->x=0;
		this->y=0;
		this->z=0;
		this->px=x1;
		this->py=y1;
	}

	void SetPos(int x1,int y1)
	{
		
	}

	int GetRecord()
	{
		return this->currentRecord;
	}

	void SetCurrentRecord(int tempRecord)
	{
		this->currentRecord=tempRecord;
	}

	void SetMaxRecord(int temp)
	{
		if (temp>(this->maxRecord))
		{
			this->maxRecord=temp;
		}
	}

	void Change(HDC hdc,int myRecord,HBITMAP hbitmap1)
	{
		/*HDC hdcMem;
		hdcMem=CreateCompatibleDC(hdc);*/

		x=myRecord/100;
		y=(myRecord%100)/10;
		z=(myRecord%100)%10;

		this->loadMybitmap(this->hInstance);

		this->Draw(hdc,hbitmap1);

		/*DeleteObject(hdcMem);*/
		
	}

	void Draw(HDC hdc,HBITMAP hbitmap1)
	{
		HDC hdcMem;
		hdcMem=CreateCompatibleDC(hdc);

		SelectObject(hdcMem,hbitmap1);
		BitBlt(hdc,this->px,this->py,3*this->cx,this->cy,hdcMem,this->px,this->py,SRCCOPY);

		SelectObject(hdcMem,this->myBitmap);
		TransparentBlt(hdc,this->px,this->py,this->cx,this->cy,hdcMem,0,0,this->cx,this->cy,RGB(255,255,255));
		SelectObject(hdcMem,this->myBitmap1);
		TransparentBlt(hdc,this->px+40,this->py,this->cx,this->cy,hdcMem,0,0,this->cx,this->cy,RGB(255,255,255));
		SelectObject(hdcMem,this->myBitmap2);
		TransparentBlt(hdc,this->px+80,this->py,this->cx,this->cy,hdcMem,0,0,this->cx,this->cy,RGB(255,255,255));
        
		DeleteObject(hdcMem);

	}

	void loadMybitmap(HINSTANCE hInstance)
	{
		this->hInstance=hInstance;

		this->myBitmap=LoadBitmap(hInstance,MAKEINTRESOURCE(recordPicture[this->x]));
		this->myBitmap1=LoadBitmap(hInstance,MAKEINTRESOURCE(recordPicture[this->y]));
		this->myBitmap2=LoadBitmap(hInstance,MAKEINTRESOURCE(recordPicture[this->z]));

		GetObject(this->myBitmap,sizeof(BITMAP),&bitmap);
		this->cx=bitmap.bmWidth;
		this->cy=bitmap.bmHeight;
	}

};


class DollarsAndbombs
{
private:
	boolean isAlive;

	boolean firstMove;

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

	HINSTANCE hInstance;


	DollarsAndbombs()
	{
		this->firstMove=true;
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
		this->hInstance=hInstance;
		this->myBitmap=LoadBitmap(hInstance,MAKEINTRESOURCE(dollarsPicture[this->type].mybitmap));
		this->myBitmapMask=LoadBitmap(hInstance,MAKEINTRESOURCE(dollarsPicture[this->type].mybitmapMask));

		GetObject(this->myBitmap,sizeof(BITMAP),&bitmap);
		cx=bitmap.bmWidth;
		cy=bitmap.bmHeight;
	}

	void setFirstMove(boolean status)
	{
		this->firstMove=status;
	}

	boolean getFirstMove()
	{
		return this->firstMove;
	}

	void Cachu(HDC hdc,HBITMAP hbitmap1)
	{
		HDC hdcMem;
		hdcMem=CreateCompatibleDC(hdc);
		SelectObject(hdcMem,hbitmap1);
		BitBlt(hdc,this->x,this->y,this->cx,this->cy,hdcMem,this->x,this->y,SRCCOPY);

		DeleteObject(hdcMem);

	}

	void draw(HDC hdc)
	{
		HDC hdcMem;
		hdcMem=CreateCompatibleDC(hdc);

		SelectObject(hdcMem,this->myBitmapMask);
		BitBlt(hdc,this->x,this->y,this->cx,this->cy,hdcMem,0,0,SRCPAINT);

		SelectObject(hdcMem,this->myBitmap);
		BitBlt(hdc,this->x,this->y,this->cx,this->cy,hdcMem,0,0,SRCAND);

		DeleteObject(hdcMem);
	}

	//��̬�仯λ��,����������Ҫ��ͼ��
	void Change(HDC hdc,HBITMAP hbitmap1)
	{

		HDC hdcMem;
		hdcMem=CreateCompatibleDC(hdc);

		/*SelectObject(hdcMem,hbitmap1);
		BitBlt(hdc,this->x,this->y,this->cx,this->cy,hdcMem,this->x,this->y,SRCCOPY);
		*/

		this->Cachu(hdc,hbitmap1);

		this->y+=this->speed;

	
		/*SelectObject(hdcMem,this->myBitmapMask);
		BitBlt(hdc,this->x,this->y,this->cx,this->cy,hdcMem,0,0,SRCPAINT);

		SelectObject(hdcMem,this->myBitmap);
		BitBlt(hdc,this->x,this->y,this->cx,this->cy,hdcMem,0,0,SRCAND);*/

		this->draw(hdc);
	
	
		DeleteObject(hdcMem);
	}

	void SetXY(int x,int y)
	{
		this->x=x;
		this->y=this->y;
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

	void setSpeed(int speed)
	{
		this->speed=speed;
	}

	void SetType(int i)
	{
		srand((int)time(0));
		int temp=rand()%80;
		temp=temp/10;
		this->type=i;
		this->loadMyBitmap(this->hInstance);
		if (i==0)
		{
			this->speed=50+temp;
		}else if (i==1)
		{
			this->speed=50+temp;
		}else if (i==2)
		{
			this->speed=50+temp;
		}
	}

	int GetType()
	{
		return this->type;
	}


};



//������

class Marry
{
private:

	

	int speed;

public:
	
	//���
	HBITMAP myBitmap,myBitmapMask;

	int x,y;
	int cx,cy;

	BITMAP bitmap;

	HINSTANCE hInstance;

	Marry(int x,int y,int speed)
	{
		this->x=x;
		this->y=y;
		this->speed=speed;

	}

	void loadMyBitmap(HINSTANCE hInstance)
	{
		this->hInstance=hInstance;
		myBitmap=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP26));
		myBitmapMask=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP25));

		GetObject(myBitmap,sizeof(BITMAP),&bitmap);
		cx=bitmap.bmWidth;
		cy=bitmap.bmHeight;
	}

	void move(int type,HDC hdc,HBITMAP hbitmap1)
	{

		HDC hdcMem;
		hdcMem=CreateCompatibleDC(hdc);

		SelectObject(hdcMem,hbitmap1);
		BitBlt(hdc,this->x,this->y,this->cx,this->cy,hdcMem,this->x,this->y,SRCCOPY);
		
		switch(type)
		{
		//����
		case 0:
			if ((this->x)>=(this->speed))
			{
				this->x-=this->speed;
			}
			
			break;
		//����
		case 1:
			if (this->y-30>=500)
			{
				this->y-=30;
			}
			
			break;
		//����
		case 2:
			if (this->x+this->cx<900)
			{
				this->x+=this->speed;
			}
			
			break;
		//����
		case 3:
			if (this->y+30<=600)
			{
				this->y+=30;
			}
			
			break;
		}

		SelectObject(hdcMem,this->myBitmapMask);
		BitBlt(hdc,this->x,this->y,this->cx,this->cy,hdcMem,0,0,SRCPAINT);

		SelectObject(hdcMem,this->myBitmap);
		BitBlt(hdc,this->x,this->y,this->cx,this->cy,hdcMem,0,0,SRCAND);

		DeleteObject(hdcMem);
	
	}
	
	

};


//�÷�




#endif