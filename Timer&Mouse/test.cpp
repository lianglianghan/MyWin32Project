/************************************************************************/
/* 
	���ܣ�����붨ʱ����Ӧ��
	���ߣ�����
	���ڣ�2013.10.15
*/
/************************************************************************/

#include <windows.h>
#include "resource.h"
#define ID_TIMER1 100

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
					PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName [] = TEXT ("BitMap") ;
	HWND         hwnd ;
	MSG          msg ;
	WNDCLASS     wndclass ;
	HMENU        hmenu;
	HACCEL       haccel;

	wndclass.style         = CS_HREDRAW | CS_VREDRAW|DOUBLE_CLICK ;
	wndclass.lpfnWndProc   = WndProc ;
	wndclass.cbClsExtra    = 0 ;
	wndclass.cbWndExtra    = 0 ;
	wndclass.hInstance     = hInstance ;
	wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
	wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
	wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
	wndclass.lpszMenuName  = NULL ;
	wndclass.lpszClassName = szAppName ;

	

	if (!RegisterClass (&wndclass))
	{
		MessageBox (NULL, TEXT ("This program requires Windows NT!"),
			szAppName, MB_ICONERROR) ;
		return 0 ;
	}

	hwnd = CreateWindow (szAppName, TEXT ("Mouse&Timer"), 
		WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL) ;

	//��Ӳ˵�
	hmenu=LoadMenu(hInstance,MAKEINTRESOURCE(IDR_MENU1));
	SetMenu(hwnd,hmenu);

	ShowWindow (hwnd, iCmdShow) ;
	UpdateWindow (hwnd) ;

	//���ټ�
	haccel=LoadAccelerators(hInstance,MAKEINTRESOURCE(IDR_ACCELERATOR2));

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
	//����ͳ�ƺϷ��Ĵ����Լ����Ϸ��Ĵ���
	static int count=0,uncount=0;

	static boolean leftPressed=false,rightPressed=false;

	static int cxClient,cyClient;

	HDC hdc;
	PAINTSTRUCT ps;
	
	static RECT clientRect;

	static POINT iCurrentPos;

	static boolean isTimed=false;

	TCHAR buf[40];

	//ʱ�����
	static int myTime=5000;

	static int myRecord=0;

	switch (message)
	{


	case WM_COMMAND:

		switch(LOWORD(wParam))
		{
	    //��ʼ
		case ID_40001:
			count=0;
			InvalidateRect(hwnd,NULL,TRUE);
			SetTimer(hwnd,ID_TIMER1,myTime,NULL);
			break;

		//����ʱ��
		case ID_40002:
			
			break;

		//��ʾ��߼�¼
		case ID_40003:

			break;

		//�˳�
		case ID_40004:
			exit(0);
			break;

		//����
		case ID_40014:
			//MessageBox(hwnd,TEXT("success"),TEXT("test"),MB_OK);
			MessageBox(hwnd,TEXT("�����������˰ɣ�"),TEXT("����"),NULL);
			break;
		}

		return 0;

	case WM_LBUTTONDOWN:

		iCurrentPos.x=LOWORD(lParam);
		iCurrentPos.y=HIWORD(lParam);

        if (PtInRect(&clientRect,iCurrentPos))
        {
			if (!leftPressed)
			{
				if (!rightPressed)
				{
					leftPressed=true;
				}else
				{
					count++;
					leftPressed=false;
					rightPressed=false;
				}
			}else{
				uncount++;
			}
        }
		
		return 0;

	case WM_RBUTTONDOWN:
		iCurrentPos.x=LOWORD(lParam);
		iCurrentPos.y=HIWORD(lParam);

		if(PtInRect(&clientRect,iCurrentPos))
		{
			if (!rightPressed)
			{
				if (!leftPressed)
				{
					rightPressed=true;
				} 
				else
				{
					count++;
					leftPressed=false;
					rightPressed=false;
				}
			} 
			else
			{
				uncount++;
			}
		}
		
		return 0;
	
	case WM_LBUTTONDBLCLK:
		iCurrentPos.x=LOWORD(lParam);
		iCurrentPos.y=HIWORD(lParam);
		if (PtInRect(&clientRect,iCurrentPos))
		{
			uncount++;
		}
		
		return 0;

	case WM_RBUTTONDBLCLK:
		iCurrentPos.x=LOWORD(lParam);
		iCurrentPos.y=HIWORD(lParam);
		if (PtInRect(&clientRect,iCurrentPos))
		{
			uncount++;
		}
		
		return 0;

	case WM_TIMER:
		
		switch(wParam)
		{
		case ID_TIMER1:
			if(count>myRecord)
			{
				myRecord=count;
			}
			isTimed=true;
			InvalidateRect(hwnd,NULL,FALSE);
			
			break;
		}

		return 0;

	case WM_CREATE:
		
		GetClientRect(hwnd,&clientRect);

		//SetTimer(hwnd,ID_TIMER1,5000,NULL);

		return 0 ;

	case WM_SIZE:
		
		cxClient=LOWORD(lParam);
		cyClient=HIWORD(lParam);

		return 0 ;

	case WM_PAINT:
		
		hdc=BeginPaint(hwnd,&ps);

		if (isTimed)
		{
			isTimed=false;
			
			wsprintf(buf,TEXT("�ֻش���Ϊ��%d ,���Ϸ���������Ϊ��%d"),count,uncount);
			RECT rect1;
			rect1.left=cxClient*1/5;
			rect1.right=cxClient*3/5;
			rect1.top=0;
			rect1.bottom=cyClient/5;
			DrawText(hdc,buf,-1,&rect1,DT_CENTER|DT_VCENTER);

		}

		EndPaint(hwnd,&ps);

		return 0 ;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0 ;
	}
	return DefWindowProc (hwnd, message, wParam, lParam) ;
}
