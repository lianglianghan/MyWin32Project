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

//得分
class Record
{
private:

	int currentRecord;

	int maxRecord;

	//百位、十位、个位
	int x,y,z;

	//起点坐标
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

		x=myRecord/100;
		y=(myRecord%100)/10;
		z=(myRecord%100)%10;

		this->loadMybitmap(this->hInstance);

		this->Draw(hdc,hbitmap1);
		
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

//炸弹类和奖励类

class DollarsAndbombs
{
private:
	boolean isAlive;

	boolean firstMove;

public:
	//0--》金币 1--》炸弹  2--》加时秒表 3--》时间暂停 （其他的待定）
	int type;

	int speed;

	//金币的位置
	int x,y;

	//金币的大小
	int cx,cy;

	//句柄
	HBITMAP myBitmap,myBitmapMask;

	BITMAP bitmap;

	HINSTANCE hInstance;

	int IsTouched(int x,int y,int cx)
	{
		int temp=0;
		if (((this->x>=x&&this->x<=x+cx)||(this->x+this->cx>=x&&this->x+this->cx<=x+cx))&&(this->y)+(this->cy)>=y)
		{
			if (this->type==0)
			{
				temp=1;
			}else if (this->type==1)
			{
				temp=-10;
			}else if (this->type==2)
			{
				temp=5;
			}
		}

		return temp;
	}

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
	//加载位图
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

	//动态变化位置,并画出所需要的图形
	void Change(HDC hdc,HBITMAP hbitmap1)
	{

		HDC hdcMem;
		hdcMem=CreateCompatibleDC(hdc);


		this->Cachu(hdc,hbitmap1);

		this->y+=this->speed;


		this->draw(hdc);
	
	
		DeleteObject(hdcMem);
	}

	void SetXY(int x,int y)
	{
		this->x=x;
		this->y=this->y;
	}

	//初始化各个变量
	void Set(int x,int y,int speed,int type)
	{
		this->x=x;
		this->y=y;
		this->speed=speed;
		this->type=type;
	}

	//设置生死
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


//人物类

class Marry
{
private:

	int speed;

public:
	
	//句柄
	HBITMAP myBitmap,myBitmapMask;

	int x,y;
	int cx,cy;

	BITMAP bitmap;

	HINSTANCE hInstance;

	int jump[6];

	Marry(int x,int y,int speed)
	{
		this->x=x;
		this->y=y;
		this->speed=speed;
		
	}


	void Draw(HDC hdc)
	{
		HDC hdcMem;
		hdcMem=CreateCompatibleDC(hdc);
		SelectObject(hdcMem,this->myBitmapMask);
		BitBlt(hdc,this->x,this->y,this->cx,this->cy,hdcMem,0,0,SRCPAINT);

		SelectObject(hdcMem,this->myBitmap);
		BitBlt(hdc,this->x,this->y,this->cx,this->cy,hdcMem,0,0,SRCAND);
		DeleteObject(hdcMem);
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
		//向左
		case 0:
			if ((this->x)>=(this->speed))
			{
				this->x-=this->speed;
			}
			
			break;
		//向上
		case 1:

			if (this->y>=250)
			{
					this->y-=10;
			}
		
			break;
		//向右
		case 2:
			if (this->x+this->cx<900)
			{
				this->x+=this->speed;
			}
			break;
		//向下
		case 3:
			if (this->y+this->cy<=600)
			{
				this->y+=15;
			}
			
			break;
		}
		
		this->Draw(hdc);
		
		DeleteObject(hdcMem);
	
	}
	
};


//时钟的0-9
struct
{
	int map1;
	int map2;
}
group []=
{
	IDB_BITMAP3,IDB_BITMAP4,
	IDB_BITMAP5,IDB_BITMAP6,
	IDB_BITMAP7,IDB_BITMAP8,
	IDB_BITMAP9,IDB_BITMAP10,
	IDB_BITMAP11,IDB_BITMAP12,
	IDB_BITMAP13,IDB_BITMAP14,
	IDB_BITMAP15,IDB_BITMAP16,
	IDB_BITMAP17,IDB_BITMAP18,
	IDB_BITMAP19,IDB_BITMAP20,
	IDB_BITMAP21,IDB_BITMAP22
};


//时钟类
class Time
{
private:
   int first,second;
   int x1,y1,x2,y2;
public:

	HINSTANCE hInstance;
	BITMAP bitmap;
	int cx,cy;
	HBITMAP myBitmap,myBitmapMask,myBitmap1,myBitmapMask1,hbitmap1;

	Time(int x1,int y1,int x2,int y2)
	{
		this->x1=x1;
		this->y1=y1;

		this->x2=x2;
		this->y2=y2;
	}

	void setHbitmap1(HBITMAP hbitmap1)
	{
		this->hbitmap1=hbitmap1;
	}

	void loadMyBitmap(HINSTANCE hInstance)
	{
		this->hInstance=hInstance;
		myBitmap=LoadBitmap(hInstance,MAKEINTRESOURCE(group[this->first].map1));
		myBitmapMask=LoadBitmap(hInstance,MAKEINTRESOURCE(group[this->first].map2));
		
		myBitmap1=LoadBitmap(hInstance,MAKEINTRESOURCE(group[this->second].map1));
		myBitmapMask1=LoadBitmap(hInstance,MAKEINTRESOURCE(group[this->second].map2));

		GetObject(myBitmap,sizeof(BITMAP),&bitmap);
		this->cx=bitmap.bmWidth;
		this->cy=bitmap.bmHeight;

	}

	void Draw(int currentTime,HDC hdc)
	{
		HDC hdcMem;
		HPEN myPen;
		myPen=CreatePen(PS_SOLID,3,RGB(246,144,49));
		hdcMem=CreateCompatibleDC(hdc);

		this->first=currentTime/10;
		this->second=currentTime%10;

		loadMyBitmap(this->hInstance);



		SelectObject(hdcMem,this->hbitmap1);
		BitBlt(hdc,0,0,150,130,hdcMem,0,0,SRCCOPY);
		
		SelectObject(hdc,GetStockObject(NULL_BRUSH));
		SelectObject(hdc,myPen);
		RoundRect(hdc,10,15,130,80,10,10);


		SelectObject(hdcMem,myBitmapMask);
		BitBlt(hdc,this->x1,this->y1,this->cx,this->cy,hdcMem,0,0,SRCPAINT);
		SelectObject(hdcMem,myBitmap);
		BitBlt(hdc,this->x1,this->y1,this->cx,this->cy,hdcMem,0,0,SRCAND);

		SelectObject(hdcMem,myBitmapMask1);
		BitBlt(hdc,this->x2,this->y2,this->cx,this->cy,hdcMem,0,0,SRCPAINT);
		SelectObject(hdcMem,myBitmap1);
		BitBlt(hdc,this->x2,this->y2,this->cx,this->cy,hdcMem,0,0,SRCAND);


		DeleteObject(myPen);
		DeleteObject(hdcMem);
	}

};



#endif