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
	//0--》金币 1--》炸弹  2--》加时秒表 3--》时间暂停 （其他的待定）
	int type;

	int speed;

	/*//位图的编号(源文件和mask图文件）
	int map1,map2;*/

	//金币的位置
	int x,y;


	//金币的大小
	int cx,cy;

	//句柄
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

	//加载位图
	void loadMyBitmap(HINSTANCE hInstance)
	{
		this->myBitmap=LoadBitmap(hInstance,MAKEINTRESOURCE(dollarsPicture[this->type].mybitmap));
		this->myBitmapMask=LoadBitmap(hInstance,MAKEINTRESOURCE(dollarsPicture[this->type].mybitmapMask));

		GetObject(this->myBitmap,sizeof(BITMAP),&bitmap);
		cx=bitmap.bmWidth;
		cy=bitmap.bmHeight;
	}


	//动态变化位置
	void Change()
	{
		this->y+=this->speed;
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



};



#endif