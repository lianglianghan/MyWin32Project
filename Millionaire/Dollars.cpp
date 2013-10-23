#include <Windows.h>
#include "resource.h"

#include "Dollars.h"

DollarsAndbombs::DollarsAndbombs(int x,int y,int speed,int type,HINSTANCE hIstance)
{
	x=x;
	y=y;
	speed=speed;
	type=type;

	myBitmap=LoadBitmap(hIstance,MAKEINTRESOURCE(IDB_BITMAP3 ));
	GetObject(myBitmap,sizeof(BITMAP),&bitmap);
	cx=bitmap.bmWidth;
	cy=bitmap.bmHeight;

	myBitmapMask=LoadBitmap(hIstance,MAKEINTRESOURCE(IDB_BITMAP4 ));
}


void DollarsAndbombs::Change()
{
	y+=speed;
}