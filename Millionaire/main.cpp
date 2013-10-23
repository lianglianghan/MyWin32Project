/************************************************************************/
/* 
	功能：大富翁
	作者：亮亮
	日期：2013.10.22
	需要实现的功能：
			1.添加计时器（60秒）
*/
/************************************************************************/

#include <windows.h>
#include "resource.h"

//引入头文件
#include "Dollars.h"


DollarsAndbombs dollars(160,100,50,0);
DollarsAndbombs dollar[10];


static int dollarsCount=10;

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





LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;
//帮助处理
BOOL CALLBACK AboutProc(HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
					PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName [] = TEXT ("BitMap") ;
	HWND         hwnd ;
	MSG          msg ;
	WNDCLASS     wndclass ;
	HMENU        hmenu;
	HACCEL       haccel;

	wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
	wndclass.lpfnWndProc   = WndProc ;
	wndclass.cbClsExtra    = 0 ;
	wndclass.cbWndExtra    = 0 ;
	wndclass.hInstance     = hInstance ;
	
	wndclass.hIcon=LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1));
	//wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
	wndclass.hCursor=LoadCursor(hInstance,MAKEINTRESOURCE(IDC_CURSOR1));
	wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
	wndclass.lpszMenuName  = NULL ;
	wndclass.lpszClassName = szAppName ;
	

	dollar[0].Set(300,130,50,0);
	dollar[1].Set(450,100,50,0);
	dollar[2].Set(600,130,50,0);
	

	if (!RegisterClass (&wndclass))
	{
		MessageBox (NULL, TEXT ("This program requires Windows NT!"),
			szAppName, MB_ICONERROR) ;
		return 0 ;
	}

	hwnd = CreateWindow (szAppName, TEXT ("Millionaire"), 
		WS_SYSMENU|WS_MINIMIZEBOX, 
		0, 0,
		0, 0,
		NULL, NULL, hInstance, NULL) ;

	//加载菜单
	hmenu=LoadMenu(hInstance,MAKEINTRESOURCE(IDR_MENU1));
	SetMenu(hwnd,hmenu);

	ShowWindow (hwnd, iCmdShow) ;
	UpdateWindow (hwnd) ;

	haccel=LoadAccelerators(hInstance,MAKEINTRESOURCE(IDR_ACCELERATOR1));

	while (GetMessage (&msg, NULL, 0, 0))
	{
		if(!TranslateAccelerator(hwnd,haccel,&msg))
		{
			TranslateMessage (&msg) ;
			DispatchMessage (&msg) ;
		}
	}
	return msg.wParam ;
}



LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc,hdcMem;
	PAINTSTRUCT ps;

	//窗口的宽、高
	static int cxClient,cyClient;
	//显示器的宽和高
	static int screenX,screenY;
	//实例代号
	static HINSTANCE hInstance;

	//位图的相关句柄
	static HBITMAP hOldmap,hBitmap1,htimeBit[10],htimeMakBit[10]
	               ,hcloudBit,hcloudMakBit;

	//位图的高和宽
	static int cx,cy,cx1,cy1,cx2,cy2;

	static RECT timeRect,dollRect1,dollRect2,dollRect3;

	BITMAP  bitmap;


	int i;

	//两个变量来处理数字的变化

	static int first=6,second=0;

	static int count=60;

	static boolean isStart=false,isEnd=false;


	//画笔
	static HPEN  myPen;

	//炸弹
	//static int dollX=160,dollY=100;
	

	switch (message)
	{

	case WM_TIMER:
		switch(wParam)
		{
		//让时钟动起来
		case ID_Timer2:
			if (count>0)
			{
				count--;
				first=count/10;
				second=count%10;

				InvalidateRect(hwnd,&timeRect,FALSE);
			}
			else
			{
				isStart=false;
				isEnd=true;
				KillTimer(hwnd,ID_Timer2);
				first=6;
				second=0;
				count=60;
				//InvalidateRect(hwnd,NULL,TRUE);
			}
			break;
			
		case ID_Timer3:

			if (dollars.y+75<=cyClient)
			{
				dollars.Change();
				for (i=0;i<3;i++)
				{
					dollar[i].Change();
				}
				InvalidateRect(hwnd,NULL,FALSE);

			}else
			{
				KillTimer(hwnd,ID_Timer3);
			}
			
			break;
		}

		return 0;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		//开始游戏
		case ID_40001:
		case ID_MENUITEM40001:

			if (!isStart)
			{
				SetTimer(hwnd,ID_Timer2,1000,NULL);
				SetTimer(hwnd,ID_Timer3,500,NULL);
				isStart=true;
			}else
			{
				//给出一个温馨的提示，程序正在运行
				DialogBox(hInstance,MAKEINTRESOURCE(IDD_DIALOG3),hwnd,AboutProc);
			}

			break;

		//暂停游戏
		case ID_40002:
		case ID_MENUITEM40002:
			
			break;

		//重新开始
		case ID_40003:
		case ID_MENUITEM40003:

			break;

		//退出游戏
		case ID_40004:
		case ID_MENUITEM40004:

			exit(0);
			break;

		//保存游戏进度
		case ID_40005:
		case ID_MENUITEM40005:

			break;

		//恢复游戏进度
		case ID_40006:
		case ID_MENUITEM40006:

			break;

		//游戏简介
		case ID_40007:
		case ID_MENUITEM40007:

			DialogBox(hInstance,MAKEINTRESOURCE(IDD_DIALOG2),hwnd,AboutProc);

			break;
		case ID_40008:
		//关于
		case ID_MENUITEM40008:
			
			DialogBox(hInstance,MAKEINTRESOURCE(IDD_DIALOG1),hwnd,AboutProc);

			break;
		}

		return 0;
	
	case WM_CREATE:
		hdc=GetDC(hwnd);

		hInstance=((LPCREATESTRUCT)lParam)->hInstance;

		//创建画笔
		myPen=CreatePen(PS_SOLID,3,RGB(246,144,49));

		hBitmap1=LoadBitmap(hInstance,TEXT("Background"));
		GetObject(hBitmap1,sizeof(BITMAP),&bitmap);
		cx=bitmap.bmWidth;
		cy=bitmap.bmHeight;

		for (i=0;i<10;i++)
		{
			htimeBit[i]=LoadBitmap(hInstance,MAKEINTRESOURCE(group[i].map1));
			if (i==0)
			{
				GetObject(htimeBit[i],sizeof(BITMAP),&bitmap);
				cx1=bitmap.bmWidth;
				cy1=bitmap.bmHeight;
			}

			htimeMakBit[i]=LoadBitmap(hInstance,MAKEINTRESOURCE(group[i].map2));

			
		}


		//加载云图
		hcloudBit=LoadBitmap(hInstance,TEXT("clouds"));
		GetObject(hcloudBit,sizeof(BITMAP),&bitmap);
		cx2=bitmap.bmWidth;
		cy2=bitmap.bmHeight;

		hcloudMakBit=LoadBitmap(hInstance,TEXT("clouds_mask"));

		dollars.loadMyBitmap(hInstance);

		dollar[0].loadMyBitmap(hInstance);
		dollar[1].loadMyBitmap(hInstance);
		dollar[2].loadMyBitmap(hInstance);
		


		ReleaseDC(hwnd,hdc);
		return 0 ;

	case WM_SIZE:
		screenX=GetSystemMetrics(SM_CXSCREEN);
		screenY=GetSystemMetrics(SM_CYSCREEN);

		cxClient=905;
		cyClient=650;

		//将窗口放在显示器的正中央
		MoveWindow(hwnd,(screenX-cxClient)/2,(screenY-cyClient-40)/2,cxClient,cyClient,TRUE);

		timeRect.left=0;
		timeRect.right=180;
		timeRect.top=0;
		timeRect.bottom=130;

		dollRect1.left=150;
		dollRect1.right=200;
		dollRect1.top=50;
		dollRect1.bottom=cyClient;

		return 0 ;

		

	case WM_PAINT:
		hdc = BeginPaint (hwnd, &ps) ;

		hdcMem=CreateCompatibleDC(hdc);
		//加载到内存设备描述表
		hOldmap=(HBITMAP)SelectObject(hdcMem,hBitmap1);

		//背景
		BitBlt(hdc,0,0,cxClient,cyClient,hdcMem,0,0,SRCCOPY);
		

		//画出时间周围的矩形框
		SelectObject(hdc,GetStockObject(NULL_BRUSH));
		SelectObject(hdc,myPen);

		/*Rectangle(hdc,10,30,150,100);*/
		RoundRect(hdc,10,15,130,80,10,10);


		SelectObject(hdcMem,htimeMakBit[first]);
		BitBlt(hdc,5,0,cx1,cy1,hdcMem,0,0,SRCPAINT);

		SelectObject(hdcMem,htimeBit[first]);
		BitBlt(hdc,5,0,cx1,cy1,hdcMem,0,0,SRCAND);


		SelectObject(hdcMem,htimeMakBit[second]);
		BitBlt(hdc,60,0,cx1,cy1,hdcMem,0,0,SRCPAINT);

		SelectObject(hdcMem,htimeBit[second]);
		BitBlt(hdc,60,0,cx1,cy1,hdcMem,0,0,SRCAND);


		//加载云图(3张）

		

		for (i=0;i<4;i++)
		{
			int addx=150;
			int addy=30;
			if (i==0||i==2)
			{
				SelectObject(hdcMem,hcloudMakBit);
				BitBlt(hdc,100+addx*i,0,cx2,cy2,hdcMem,0,0,SRCPAINT);

				SelectObject(hdcMem,hcloudBit);
				BitBlt(hdc,100+addx*i,0,cx2,cy2,hdcMem,0,0,SRCAND);
			}else
			{
				SelectObject(hdcMem,hcloudMakBit);
				BitBlt(hdc,100+addx*i,addy,cx2,cy2,hdcMem,0,0,SRCPAINT);

				SelectObject(hdcMem,hcloudBit);
				BitBlt(hdc,100+addx*i,addy,cx2,cy2,hdcMem,0,0,SRCAND);

			}
			
		}


		//画炸弹
		SelectObject(hdcMem,dollars.myBitmapMask);
		BitBlt(hdc,dollars.x,dollars.y,dollars.cx,dollars.cy,hdcMem,0,0,SRCPAINT);


		SelectObject(hdcMem,dollars.myBitmap);
		BitBlt(hdc,dollars.x,dollars.y,dollars.cx,dollars.cy,hdcMem,0,0,SRCAND);

		for (i=0;i<3;i++)
		{
			SelectObject(hdcMem,dollar[i].myBitmapMask);
			BitBlt(hdc,dollar[i].x,dollar[i].y,dollar[i].cx,dollar[i].cy,hdcMem,0,0,SRCPAINT);


			SelectObject(hdcMem,dollar[0].myBitmap);
			BitBlt(hdc,dollar[i].x,dollar[i].y,dollar[i].cx,dollar[i].cy,hdcMem,0,0,SRCAND);
		}

		

		
		//恢复
		SelectObject(hdcMem,hOldmap);

		DeleteObject(hdcMem);
		
		EndPaint (hwnd, &ps) ;
		return 0 ;

	case WM_DESTROY:


		for (i=0;i<10;i++)
		{
			DeleteObject(htimeBit[i]);
			DeleteObject(htimeMakBit[i]);
		}
		//释放资源
		DeleteObject(hBitmap1);


		PostQuitMessage (0) ;
		return 0 ;
	}
	return DefWindowProc (hwnd, message, wParam, lParam) ;
}


//帮助对话框的处理
BOOL CALLBACK AboutProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) 
{

	switch(message)
	{
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_BUTTON1:
			EndDialog(hDlg,TRUE);
			return TRUE;
		}
	}

	return FALSE;
}