/************************************************************************/
/* 
	���ܣ�����
	���ߣ�����
	���ڣ�2013.10.22
	�Ѿ�ʵ�ֵĹ��ܣ�
			1.��Ӽ�ʱ����60�룩
			2.��һᶯ������
			3.�Ʒ֣����--1��  ը��-- -10��   ���--��ͣ7��  ƿ��--ѣ��3�룩
			4.�����ܹ�������Ծ�Խ�ң������������Σ���Ծ�����п��������ƶ���
			5.��ҡ�ը�����������������
			6.��ʼ�����¿�ʼ����ͣʵ��
			7.space��һ��ʵ����ͣ���ڶ���ʵ�ּ���
			8.��Ϸ˵����a��left��--����  z--��������  d��right--�����ƶ� space--��ͣ����
			9.���ټ�Ҳ�Ѿ�ʵ�֣�����ļ��ټ����Բμ��˵�ע��
	����Ҫʵ�ֵĹ��ܣ�
			1.��߼�¼�͵�ǰ��¼��ͬ��     ���ţ�
			2.�����ʾ��߼�¼��Dialog      ���ţ�
			3.������Ϸ�ͼ�����Ϸ����      ��������*��
			4.�Ӵ���Edit����Ϸͬ��������  ��������*��
			5.�������ֺͳԽ��ʱ�������Լ�ը�����������ʱ�����֣��ţ�

	ʵ�ֵĹ����в�����Ĳ��֣�
			1.�������Ƚϲ������������Ƚ�ɵ
			   �����뷨����������ǰ���ڵ�λ����ȷ����һ��Ҫjump�ľ���
		    
			
	��֪bug��

	       1.ͼ�ν����ƶ������⣨������Ҫ��Դ�ڷ�ֹ��Ļ��˸��
		       �뷨������
			   �����㣺��ǰ���豸������
		   2.�����������ҳԵ���״̬��Ϊfalse
		       �򲻻����»���һ���µĽ�ң���������Ҫ�������bug
		        �����뷨����һ���������洢������Ŀ�����ﵽ3��ʱ�򣬻ỽ�ѵ�һ��
*/
/************************************************************************/

#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <ATLComTime.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

//����ͷ�ļ�
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

//�������
//boolean jasu=false;


//��ǰ��¼��ʱ��
int myCurrentRcd=0;
int myCurrentTime=60;

//��ģ̬�Ի�������ʾ��߼�¼
HWND hDlgMaxRecord;

//���ڴ�����
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

//��߼�¼�Ի�����
BOOL CALLBACK MaxRecordProc (HWND, UINT, WPARAM, LPARAM) ;
//����Dlg����
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

	//�����Զ����icon��cursor
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

	//���ز˵�
	hmenu=LoadMenu(hInstance,MAKEINTRESOURCE(IDR_MENU1));
	SetMenu(hwnd,hmenu);

	ShowWindow (hwnd, iCmdShow) ;
	UpdateWindow (hwnd) ;

	/*hDlgMaxRecord=CreateDialog(hInstance,TEXT("��߼�¼"),hwnd,MaxRecordProc);*/
	


	//���ؼ��ټ�
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

	//���ڵĿ���
	static int cxClient,cyClient;
	//��ʾ���Ŀ�͸�
	static int screenX,screenY;
	//ʵ������
	static HINSTANCE hInstance;

	//λͼ����ؾ��
	static HBITMAP hOldmap,hBitmap1,hcloudBit,hcloudMakBit,hgameoverBit,hgameoverMask;

	//λͼ�ĸߺͿ�
	static int cx,cy,cx1,cy1,cx2,cy2;

	BITMAP  bitmap;

	int temp,temp1;
	
	static boolean isPuase=false;

	//�����������������ֵı仯

	static int first=6,second=0;

	static int count=60;

	static boolean isStart=false,isEnd=false;


	//����
	static HPEN  myPen;

	//��¼���Ĵ���������������3�Σ�
	static int jump_times=0;

	switch (message)
	{
	//��������
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
			//a��AΪ����
			case 0x61:
			case 0x41:
				
				marry.move(0);
				marry.isMoved=true;

				break;
			//w��W����
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

			//d��D����
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
		//�����Ծ
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
		//��ʱ�Ӷ�����
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

		//�������
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
					    //���ﻹ�д����ƣ������������ҳԵ���״̬��Ϊfalse
						//�򲻻����»���һ���µĽ�ң���������Ҫ�������bug
						//�����뷨����һ���������洢������Ŀ�����ﵽ3��ʱ�򣬻ỽ�ѵ�һ��
						
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
								//���ò������ƶ�������ѣ��֢״
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

		//����ը��
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

		//������ʱʱ��
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


		//ʱ����ͣ
		case ID_Timer6:
			SetTimer(hwnd,ID_Timer2,1000,NULL);
			KillTimer(hwnd,ID_Timer6);
			break;

		//��������
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
		//�ָ�ԭ�����ٶ�
		case ID_Timer9:

			KillTimer(hwnd,NULL);
			//jasu=false;

			marry.setIsAllowed(true);

			//��Ϊԭ�����ٶ�
			break;
		}

		return 0;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		//��߼�¼��
		case ID_40010:
			hDlgMaxRecord=CreateDialog(hInstance,MAKEINTRESOURCE(IDD_DIALOG4),hwnd,MaxRecordProc);
			ShowWindow(hDlgMaxRecord,SW_SHOW);
			//hDlgMaxRecord=CreateDialog(hInstance,TEXT("��߼�¼"),hwnd,MaxRecordProc);

			break;

		//��ʼ��Ϸ
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
				//����һ����ܰ����ʾ��������������
				DialogBox(hInstance,MAKEINTRESOURCE(IDD_DIALOG3),hwnd,AboutProc);
			}

			break;

		//��ͣ��Ϸ
		case ID_40002:
		case ID_MENUITEM40002:
			if (isStart)
			{
				GameManagement::pauseMyGame(hwnd);
				isPuase=true;
				
			}
			break;

		//���¿�ʼ
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

		//�˳���Ϸ
		case ID_40004:
		case ID_MENUITEM40004:

			//exit(0);
			SendMessage(hwnd,WM_CLOSE,0,0);
			break;

		//������Ϸ����
		case ID_40005:
		case ID_MENUITEM40005:

			break;

		//�ָ���Ϸ����
		case ID_40006:
		case ID_MENUITEM40006:

			break;

		//��Ϸ���
		case ID_40007:
		case ID_MENUITEM40007:

			DialogBox(hInstance,MAKEINTRESOURCE(IDD_DIALOG2),hwnd,AboutProc);

			break;
		case ID_40008:
		//����
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

			
			//����
			hBitmap1=LoadBitmap(hInstance,TEXT("Background"));
			GetObject(hBitmap1,sizeof(BITMAP),&bitmap);
			cx=bitmap.bmWidth;
			cy=bitmap.bmHeight;


			hgameoverBit=LoadBitmap(hInstance,TEXT("gameover"));
			hgameoverMask=LoadBitmap(hInstance,TEXT("gameovermask"));

			//������ͼ
			hcloudBit=LoadBitmap(hInstance,TEXT("clouds"));
			GetObject(hcloudBit,sizeof(BITMAP),&bitmap);
			cx2=bitmap.bmWidth;
			cy2=bitmap.bmHeight;

			hcloudMakBit=LoadBitmap(hInstance,TEXT("clouds_mask"));

			

			//���ؽ��
			for (i=0;i<8;i++)
			{
				for (k=0;k<3;k++)
				{
					dollar[i][k].loadMyBitmap(hInstance);
				}
			}


			//����С��
			marry.loadMyBitmap(hInstance);

			//���ؼ�¼
			mRecord.loadMybitmap(hInstance);

			//����ʱ��
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

		//�����ڷ�����ʾ����������
		MoveWindow(hwnd,(screenX-cxClient)/2,(screenY-cyClient-40)/2,cxClient,cyClient,TRUE);

		return 0 ;

	case WM_PAINT:
		hdc = BeginPaint (hwnd, &ps) ;

		

		hdcMem=CreateCompatibleDC(hdc);
		//���ص��ڴ��豸������
		hOldmap=(HBITMAP)SelectObject(hdcMem,hBitmap1);

		//����
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
		

		//����ͼ
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

		
		//�ָ�
		SelectObject(hdcMem,hOldmap);

		DeleteObject(hdcMem);
		
		EndPaint (hwnd, &ps) ;
		return 0 ;

	case WM_DESTROY:

		//�ͷ���Դ
		DeleteObject(hBitmap1);

		PostQuitMessage (0) ;
		return 0 ;
	}
	return DefWindowProc (hwnd, message, wParam, lParam) ;
}


//�����Ի���Ĵ���
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


//��߼�¼�Ի�����

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