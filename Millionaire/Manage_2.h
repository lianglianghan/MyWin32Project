#include <Windows.h>
#include "resource.h"
#include "Members.h"

#ifndef MANAGE_H
#define MANAGE_H

class GameManagement
{
public:

	static void startMyTimer(HWND hwnd)
	{
		SetTimer(hwnd,ID_Timer2,1000,NULL);
		SetTimer(hwnd,ID_Timer3,100,NULL);
		SetTimer(hwnd,ID_Timer4,5000,NULL);
		SetTimer(hwnd,ID_Timer5,18000,NULL);
		SetTimer(hwnd,ID_Timer7,30,NULL);
		SetTimer(hwnd,ID_Timer8,7000,NULL);
	}

	static void startMyGame(HWND hwnd,HDC hdc,DollarsAndbombs dollar[8][3])
	{
		int i,k;
		for (i=0;i<8;i++)
		{
			for (k=0;k<3;k++)
			{
				dollar[i][k].Set(150+i*75,100+30*((i/2)%2),1+2*i,0);
				dollar[i][k].SetType(0);
				if (k==0)
				{
					dollar[i][k].setAlive(true);
				}else
				{
					dollar[i][k].setAlive(false);
				}

			}

		}
		for (i=0;i<8;i++)
		{
			dollar[i][0].draw(hdc);
			dollar[i][0].setFirstMove(false);
		}

		startMyTimer(hwnd);
	}

	static void stopMyGame(HWND hwnd)
	{
		KillTimer(hwnd,ID_Timer2);
		KillTimer(hwnd,ID_Timer3);
		KillTimer(hwnd,ID_Timer4);
		KillTimer(hwnd,ID_Timer5);
		KillTimer(hwnd,ID_Timer6);
		KillTimer(hwnd,ID_Timer7);
		KillTimer(hwnd,ID_Timer8);
	}

	static void pauseMyGame(HWND hwnd)
	{
		stopMyGame(hwnd);
	}


};


#endif