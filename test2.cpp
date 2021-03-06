/*
  功能：Game1.0版  ---实现了字符串的围绕运动
  作者：亮亮
  日期：2013.9.08  
*/

#include <windows.h>
//下面两行用来解决播放音频时的问题
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

//#include <iostream.h>
//设置字符串的起始坐标
static int x=0,y=0;
//设置字符串的移动方向
//0-->right  1-->down   2-->left   3--->up    4-->
int direction=0;
//boolean direction=true;
static int uRed = 0, uGreen = 0, uBlue = 0;
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,PSTR szCmdLine,int iCmdShow)
{
	static TCHAR szAppName[]=TEXT("helloWin");

	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	wndclass.style=CS_HREDRAW|CS_VREDRAW;
	wndclass.lpfnWndProc=WndProc;
	wndclass.cbClsExtra=0;
	wndclass.cbWndExtra=0;
	wndclass.hInstance=hInstance;
	wndclass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hCursor=LoadCursor(NULL,IDC_ARROW);
	wndclass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName=NULL;
	wndclass.lpszClassName=szAppName;

	//进行注册窗口类
	if(!RegisterClass(&wndclass))
	{
		MessageBox(NULL,TEXT("This program requires Windows NT !"),szAppName,MB_ICONERROR);

		return 0;
	}

	hwnd=CreateWindow(szAppName,
		TEXT("Game1.0 --by the fourth gorup"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	//在屏幕上显示窗口(非用户区)
	ShowWindow(hwnd,iCmdShow);
	//显示用户区
	UpdateWindow(hwnd);

	//消息循环
	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	//返回操作系统（int）
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;

	switch(message)
	{
	case WM_CREATE:
		//PlaySound(TEXT("hello.wav"),NULL,SND_FILENAME|SND_ASYNC);
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hwnd,&ps);
		GetClientRect(hwnd,&rect);
		SetTextColor(hdc,RGB(uRed,uGreen,uBlue));
		//在屏幕中央显示“hello，Windows 98!”
		//DrawText(hdc,TEXT("Hello,Windows 98!"),-1,&rect,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		TextOut(hdc,x,y,"hello,windows 98!",strlen("hello,windows 98!"));
		
		EndPaint (hwnd, &ps) ;
		return 0;
	case WM_KEYDOWN:
		GetClientRect(hwnd,&rect);
		//cout>>rect.right;
		//printf("%of",rect.right);
		
		if(direction==0)
		{
			if(x+120<=rect.right)
			{
				x+=10;
			}
			else
			{
				
				direction=1;
			}
		}else if(direction==1)
		{
			if(y+20<=rect.bottom)
			{
				y+=10;
			}else
			{
				direction=2;
			}
		}
		else if(direction==2)
		{
			if(x>0)
			{
				x-=10;
			}
			else
			{
				direction=3;
			}

		}else if(direction==3)
		{
			if(y>0)
			{
				y-=10;
			}
			else
			{
				direction=0;
			}
		}
		
		//设置颜色用于变色
		uRed=rand()%256;
		uGreen=rand()%256;
		uBlue=rand()%256;

		InvalidateRect(hwnd,NULL,true);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	
	return DefWindowProc(hwnd,message,wParam,lParam);
}

