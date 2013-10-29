/************************************************************************/
/* 
	功能：大富翁
	作者：亮亮
	日期：2013.10.22
	已经实现的功能：
			1.添加计时器（60秒）
			2.金币会动（ˇ）
			3.计分（金币--1分  炸弹-- -10分   秒表--暂停7秒  瓶子--眩晕3秒）
			4.人物能够向上跳跃吃金币（可以连跳三次，跳跃过程中可以左右移动）
			5.金币、炸弹、秒表可以随机出现
			6.开始、重新开始、暂停实现
			7.space第一次实现暂停，第二次实现继续
			8.游戏说明：a或left键--左移  z--向上跳动  d或right--向右移动 space--暂停继续
			9.加速键也已经实现，具体的加速键可以参见菜单注解
	还需要实现的功能：
			1.最高纪录和当前纪录的同步     （∨）
			2.添加显示最高纪录的Dialog      （∨）
			3.保存游戏和加载游戏进度      （林信屹*）
			4.子窗口Edit与游戏同步的问题  （林信屹*）
			5.背景音乐和吃金币时的音乐以及炸弹和秒表下落时的音乐（∨）

	实现的功能中不理想的部分：
			1.向上跳比较不合理，看起来比较傻
			   初步想法：根据任务当前所在的位置来确定下一次要jump的距离
		    
			
	已知bug：

	       1.图形交叉移动有问题（问题主要来源于防止屏幕闪烁）
		       想法：暂无
			   出发点：当前的设备描述表
		   2.当三个都被我吃掉后，状态都为false
		       则不会重新唤醒一个新的金币，后续中需要更正这个bug
		        初步想法：用一个变量来存储死的数目，当达到3的时候，会唤醒第一个
*/
/************************************************************************/

#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <ATLComTime.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

//引入头文件
#include "resource.h"
#include "Members.h"
#include "Manage.h"
#include "Sound.h"

int i,k;

DollarsAndbombs dollar[8][3];

//int deadNumbers[8]={0,0,0,0,0,0,0,0};

int bombs=0,times=0;

Record mRecord(750,0);

Marry marry(440,470,20);

Time myTime(5,0,60,0);

//加速与否
//boolean jasu=false;


//当前纪录和时间
int myCurrentRcd=0;
int myCurrentTime=60;

//非模态对话框来显示最高纪录
HWND hDlgMaxRecord;

//窗口处理函数
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

//最高纪录对话框处理
BOOL CALLBACK MaxRecordProc (HWND, UINT, WPARAM, LPARAM) ;
//帮助Dlg处理
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

	//加载自定义的icon和cursor
	wndclass.hIcon=LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1));
	wndclass.hCursor=LoadCursor(hInstance,MAKEINTRESOURCE(IDC_CURSOR1));

	wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
	wndclass.lpszMenuName  = NULL ;
	wndclass.lpszClassName = szAppName ;
	
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

	/*hDlgMaxRecord=CreateDialog(hInstance,TEXT("最高纪录"),hwnd,MaxRecordProc);*/
	


	//加载加速键
	haccel=LoadAccelerators(hInstance,MAKEINTRESOURCE(IDR_ACCELERATOR1));

	while (GetMessage (&msg, NULL, 0, 0))
	{
		/*if(!TranslateAccelerator(hwnd,haccel,&msg)||(hDlgMaxRecord==0||!IsDialogMessage(hDlgMaxRecord,&msg)))
		{
			TranslateMessage (&msg) ;
			DispatchMessage (&msg) ;
		}*/
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

	TCHAR buf[128];

	//窗口的宽、高
	static int cxClient,cyClient;
	//显示器的宽和高
	static int screenX,screenY;
	//实例代号
	static HINSTANCE hInstance;

	//位图的相关句柄
	static HBITMAP hOldmap,hBitmap1,hcloudBit,hcloudMakBit,hgameoverBit,hgameoverMask;

	//位图的高和宽
	static int cx,cy,cx1,cy1,cx2,cy2;

	BITMAP  bitmap;

	int temp,temp1;
	
	static boolean isPuase=false;

	//两个变量来处理数字的变化

	static int first=6,second=0;

	static int count=60;

	static boolean isStart=false,isEnd=false;


	//画笔
	static HPEN  myPen;

	//纪录跳的次数（最多可以连续3次）
	static int jump_times=0;

	switch (message)
	{
	//按键处理
	case WM_KEYDOWN:
		
		if (isStart)
		{
			hdc=GetDC(hwnd);
			switch(wParam)
			{

			case VK_SPACE:

				if (!isPuase)
				{
					GameManagement::pauseMyGame(hwnd);
					isPuase=true;
				}else{
					myCurrentTime--;
					GameManagement::startMyTimer(hwnd);
					
					isPuase=false;
				}

				break;

			case VK_LEFT:

				marry.move(0);
				marry.isMoved=true;

				break;
			case VK_RIGHT:

				marry.move(2);
				marry.isMoved=true;


				break;
			}
			ReleaseDC(hwnd,hdc);
		}
		
		return 0;


	case WM_KEYUP:
		if (isStart)
		{
			switch(wParam)
			{
			case VK_LEFT:
			case 0x61:
			case 0x41:
				//marry.isMoved=false;
				marry.SetSpeed(0);
				break;
			/*case 0x77:
			case 0x57:
				marry.isJumped=false;
				break;*/
			case VK_RIGHT:
			case 0x64:
			case 0x44:
				//marry.isMoved=false;
				marry.SetSpeed(0);
				break;
			case 0x77:
			case 0x57:
				break;
			}
		}

		return 0;
	
	case WM_CHAR:
		if (isStart)
		{
			hdc=GetDC(hwnd);
			switch(wParam)
			{
			//a、A为向左
			case 0x61:
			case 0x41:
				
				marry.move(0);
				marry.isMoved=true;

				break;
			//w、W向上
			/*case 0x77:
			case 0x57:*/
			case 0x5A:
			case 0x7A:
				{
					//TCHAR buf1[50];
					
					//mciSendString(TEXT("stop guanghao"),buf,lstrlen(buf),NULL);
					PlayMySound::playJump(buf);
					
					hdc=GetDC(hwnd);
					
					marry.move(1);
					marry.isJumped=true;
					ReleaseDC(hwnd,hdc);
					
				}
				break;

			//d、D向右
			case 0x64:
			case 0x44:
				marry.move(2);
				marry.isMoved=true;
				break;
			}
			ReleaseDC(hwnd,hdc);
		}
		
		return 0;

	case WM_TIMER:
		switch(wParam)
		{
		//检测跳跃
		case ID_Timer7:
			hdc=GetDC(hwnd);
			if (marry.GetAllowedStatus())
			{
				if (marry.isJumped)
				{
					marry.Jump(hdc,hBitmap1);
				}else if (marry.isMoved)
				{
					if (marry.GetSpeed()!=0)
					{
						marry.testMove(hdc,hBitmap1);
					}

				}
			}
			ReleaseDC(hwnd,hdc);
			break;
		//让时钟动起来
		case ID_Timer2:
			if (myCurrentTime>0)
			{
				hdc=GetDC(hwnd);
				myCurrentTime--;
				myTime.Draw(myCurrentTime,hdc);
				ReleaseDC(hwnd,hdc);
			}
			else
			{
				//PlaySound(TEXT("./sound/gameover.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
				mciSendString(TEXT("close adu"),buf,lstrlen(buf),NULL);
				PlayMySound::playGameover(buf);
				mRecord.SetMaxRecord(myCurrentRcd);
				isStart=false;
				isEnd=true;
				GameManagement::stopMyGame(hwnd);
				//KillTimer(hwnd,ID_Timer7);
				//KillTimer(hwnd,ID_Timer8);
				myCurrentTime=0;
				InvalidateRect(hwnd,NULL,FALSE);

			}
			break;

		//金币下落
		case ID_Timer3:

			hdc=GetDC(hwnd);
	
			for (i=0;i<8;i++)
			{
				for (k=0;k<3;k++)
				{
					
					temp1=dollar[i][k].IsTouched(marry.x,marry.y,marry.cx);
					if (dollar[i][k].y+dollar[i][k].speed<=430&&temp1==0)
					{
						if (dollar[i][k].isAlived())
						{
							dollar[i][k].Change(hdc,hBitmap1);
							if (dollar[i][k].y>=270)
							{
								temp=(k+1)%3;
								dollar[i][temp].setAlive(true);
								//deadNumbers[i]--;
							}
							
						}
					    //这里还有待改善，当三个都被我吃掉后，状态都为false
						//则不会重新唤醒一个新的金币，后续中需要更正这个bug
						//初步想法：用一个变量来存储死的数目，当达到3的时候，会唤醒第一个
						
					}else
					{
						if (temp1!=0)
						{
							if (temp1==5)
							{

								PlayMySound::playJiashi(buf);

								KillTimer(hwnd,ID_Timer2);
								SetTimer(hwnd,ID_Timer6,7000,NULL);
							}else if (temp1==1||temp1==-10)
							{
								if (temp1==1)
								{

									PlayMySound::playJinBi(buf);
								}else if (temp1==-10)
								{

									PlayMySound::playZhaDan(buf);
								}
								myCurrentRcd+=temp1;
								if (myCurrentRcd<=0)
								{
									myCurrentRcd=0;
								}
								mRecord.Change(hdc,myCurrentRcd,hBitmap1);
							}else if (temp1==3)
							{
								//jasu=true;
								//设置不可以移动，出现眩晕症状
								marry.setIsAllowed(false);
								marry.Cachu(hdc,hBitmap1);
                                marry.x=marry.x;
								marry.y=470;
								PlayMySound::playXuanyun(buf);
								marry.Draw(hdc);
								SetTimer(hwnd,ID_Timer9,3000,NULL);
							}

						}
						
						dollar[i][k].Cachu(hdc,hBitmap1);
						dollar[i][k].setAlive(false);
						
						dollar[i][k].Set(150+i*75,100+30*((i/2)%2),1,0);
					    //dollar[i][k].SetJiasu(jasu);
						dollar[i][k].SetType(0);
						
					}
					
				}
			}
			
			ReleaseDC(hwnd,hdc);

			break;

		//产生炸弹
		case ID_Timer4:
			srand((int)time(0));

			temp=rand()%160;
			temp=temp/20;

			for (k=0;k<3;k++)
			{
				if (!dollar[temp][k].isAlived())
				{
					dollar[temp][k].SetType(1);

					break;
				}
			}

			temp1=rand()%80;
			temp1=temp1/10;
			if (temp1!=temp)
			{
				for (k=0;k<3;k++)
				{
					if (!dollar[temp1][k].isAlived())
					{
						dollar[temp1][k].SetType(1);

						break;
					}
				}
			}
			
			break;

		//产生加时时钟
		case ID_Timer5:
			srand((int)time(0));
			temp=rand()%160;
			temp=temp/20;

			for (k=0;k<3;k++)
			{
				if (!dollar[temp][k].isAlived())
				{
					dollar[temp][k].SetType(2);
					break;
				}
			}

			
			
			break;


		//时间暂停
		case ID_Timer6:
			SetTimer(hwnd,ID_Timer2,1000,NULL);
			KillTimer(hwnd,ID_Timer6);
			break;

		//产生加速
		case ID_Timer8:
			
			srand((int)time(0));
			temp=rand()%160;
			temp=temp/20;

			for (k=0;k<3;k++)
			{
				if (!dollar[temp][k].isAlived())
				{
					dollar[temp][k].SetType(3);
					break;
				}
			}

			break;
		//恢复原来的速度
		case ID_Timer9:

			KillTimer(hwnd,NULL);
			//jasu=false;

			marry.setIsAllowed(true);

			//变为原来的速度
			break;
		}

		return 0;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		//最高纪录：
		case ID_40010:
			hDlgMaxRecord=CreateDialog(hInstance,MAKEINTRESOURCE(IDD_DIALOG4),hwnd,MaxRecordProc);
			ShowWindow(hDlgMaxRecord,SW_SHOW);
			//hDlgMaxRecord=CreateDialog(hInstance,TEXT("最高纪录"),hwnd,MaxRecordProc);

			break;

		//开始游戏
		case ID_40001:
		case ID_MENUITEM40001:

			if (!isStart)
			{
				hdc=GetDC(hwnd);
				
				myCurrentRcd=0;
				myCurrentTime=60;
				InvalidateRect(hwnd,NULL,FALSE);
				mciSendString(TEXT("close gameover"),buf,lstrlen(buf),NULL);
				//mciSendString(TEXT("close adu"),buf,lstrlen(buf),NULL);
				PlayMySound::playBkg(buf);
				GameManagement::startMyGame(hwnd,hdc,dollar);
				
				marry.setIsAllowed(true);
				
				ReleaseDC(hwnd,hdc);
				isStart=true;
				isEnd=false;
			}else
			{
				//给出一个温馨的提示，程序正在运行
				DialogBox(hInstance,MAKEINTRESOURCE(IDD_DIALOG3),hwnd,AboutProc);
			}

			break;

		//暂停游戏
		case ID_40002:
		case ID_MENUITEM40002:
			if (isStart)
			{
				GameManagement::pauseMyGame(hwnd);
				isPuase=true;
				
			}
			break;

		//重新开始
		case ID_40003:
		case ID_MENUITEM40003:
			
			mciSendString(TEXT("close gameover"),buf,lstrlen(buf),NULL);
			PlayMySound::playBkg(buf);

			GameManagement::stopMyGame(hwnd);
			myCurrentRcd=0;
			myCurrentTime=60;
			InvalidateRect(hwnd,NULL,FALSE);

			hdc=GetDC(hwnd);
			GameManagement::startMyGame(hwnd,hdc,dollar);

			marry.setIsAllowed(true);
			ReleaseDC(hwnd,hdc);

			isStart=true;
			isEnd=false;
			break;

		//退出游戏
		case ID_40004:
		case ID_MENUITEM40004:

			//exit(0);
			SendMessage(hwnd,WM_CLOSE,0,0);
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
		{
			hdc=GetDC(hwnd);

			hInstance=((LPCREATESTRUCT)lParam)->hInstance;


			//PlayMySound::playBkg(buf);

			
			//背景
			hBitmap1=LoadBitmap(hInstance,TEXT("Background"));
			GetObject(hBitmap1,sizeof(BITMAP),&bitmap);
			cx=bitmap.bmWidth;
			cy=bitmap.bmHeight;


			hgameoverBit=LoadBitmap(hInstance,TEXT("gameover"));
			hgameoverMask=LoadBitmap(hInstance,TEXT("gameovermask"));

			//加载云图
			hcloudBit=LoadBitmap(hInstance,TEXT("clouds"));
			GetObject(hcloudBit,sizeof(BITMAP),&bitmap);
			cx2=bitmap.bmWidth;
			cy2=bitmap.bmHeight;

			hcloudMakBit=LoadBitmap(hInstance,TEXT("clouds_mask"));

			

			//加载金币
			for (i=0;i<8;i++)
			{
				for (k=0;k<3;k++)
				{
					dollar[i][k].loadMyBitmap(hInstance);
				}
			}


			//加载小人
			marry.loadMyBitmap(hInstance);

			//加载纪录
			mRecord.loadMybitmap(hInstance);

			//加载时间
			myCurrentTime=60;
			myTime.loadMyBitmap(hInstance);
			myTime.setHbitmap1(hBitmap1);


			ReleaseDC(hwnd,hdc);
		}
		
		return 0 ;

	case WM_SIZE:
		screenX=GetSystemMetrics(SM_CXSCREEN);
		screenY=GetSystemMetrics(SM_CYSCREEN);

		cxClient=905;
		cyClient=650;

		//将窗口放在显示器的正中央
		MoveWindow(hwnd,(screenX-cxClient)/2,(screenY-cyClient-40)/2,cxClient,cyClient,TRUE);

		return 0 ;

	case WM_PAINT:
		hdc = BeginPaint (hwnd, &ps) ;

		

		hdcMem=CreateCompatibleDC(hdc);
		//加载到内存设备描述表
		hOldmap=(HBITMAP)SelectObject(hdcMem,hBitmap1);

		//背景
		BitBlt(hdc,0,0,cxClient,cyClient,hdcMem,0,0,SRCCOPY);


		if (isEnd)
		{
			SelectObject(hdcMem,hgameoverMask);
			BitBlt(hdc,245,245,410,110,hdcMem,0,0,SRCPAINT);


			SelectObject(hdcMem,hgameoverBit);

			BitBlt(hdc,245,245,410,110,hdcMem,0,0,SRCAND);


			/*BitBlt(hdc,287,170,325,260,hdcMem,0,0,SRCCOPY);*/
			/*TransparentBlt(hdc,245,245,410,110,hdcMem,0,0,410,110,RGB(255,255,255));*/
		}
		

		//画云图
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


		marry.Draw(hdc);

		myTime.Draw(myCurrentTime,hdc);


		//mRecord.Draw(hdc,hBitmap1);
		mRecord.Change(hdc,myCurrentRcd,hBitmap1);

		
		//恢复
		SelectObject(hdcMem,hOldmap);

		DeleteObject(hdcMem);
		
		EndPaint (hwnd, &ps) ;
		return 0 ;

	case WM_DESTROY:

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


//最高纪录对话框处理

BOOL CALLBACK MaxRecordProc(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam)
{

	switch(message)
	{
	case WM_INITDIALOG:

		
		TCHAR buf1[10];
		wsprintf(buf1,TEXT("%d"),mRecord.GetMaxRecord());
		SetDlgItemText(hDlg,IDC_STATIC2,buf1);

		//ShowWindow(hDlg,SW_SHOW);
		return FALSE;

	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case IDCANCEL:
			case IDOK:
				DestroyWindow(hDlg);
				return TRUE;
			}
		}

	}

	return FALSE;
}