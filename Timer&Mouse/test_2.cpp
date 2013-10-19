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
BOOL    CALLBACK AboutDlgProc (HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK  Dialog1Proc(HWND , UINT ,WPARAM, LPARAM);
BOOL CALLBACK  RecordDlgProc(HWND , UINT ,WPARAM, LPARAM);
BOOL CALLBACK  TimeOverDlgProc(HWND , UINT ,WPARAM, LPARAM);


HWND  hdialg1=NULL,hdialg2=NULL;

static int myTime=3000;

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

	//������ģ̬�Ի�����߼�¼��
	hdialg2=CreateDialog(hInstance,MAKEINTRESOURCE(IDD_DIALOG2),hwnd,RecordDlgProc);

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
	static TCHAR *buttonLable[]={
		TEXT("��ʼ"),TEXT("�˳�"),TEXT("����ʱ��")
	};

	static TCHAR *textLable[]={
		TEXT("��߼�¼"),TEXT("��ǰ��¼"),TEXT("��ǰ���õ�ʱ��Ϊ��")
	};


	static HWND hButton[3],hText[3],hScrollBar,hTime;

	//��̬���ֵı�������
	static HBRUSH hstaticBrush,hGreenBrush,holdBrush;

	//����ͳ�ƺϷ��Ĵ����Լ����Ϸ��Ĵ���
	static int count=0,uncount=0;

	static boolean leftPressed=false,rightPressed=false;

	static int cxClient,cyClient;

	HDC hdc;
	PAINTSTRUCT ps;
	
	static RECT clickRect;

	static POINT iCurrentPos;

	static boolean isStart=false,isEnd=false;

	TCHAR buf[20];

	//ʱ�����
	

	static int myRecord=0,tempRecord=0;

	static HINSTANCE hinstance;

	//��̬���
	HWND hDlgstatic1;

	//�����ڶ��ַ��Ŀ�͸�
	static int cxChar,cyChar;
	int k;

	static int iVscrollPos=3;

	

	switch (message)
	{


	case WM_COMMAND:

		switch(LOWORD(wParam))
		{
	    //��ʼ
		case 0:
		case ID_40001:
			if(isStart)
			{
				MessageBox(hwnd,TEXT("�������������У����Ժ�^_^"),TEXT("����"),NULL);
			}
			count=0;
			uncount=0;
			leftPressed=false;
			rightPressed=false;
			isStart=true;
			InvalidateRect(hwnd,NULL,TRUE);
			SetTimer(hwnd,ID_TIMER1,myTime,NULL);
			break;

		//����ʱ��
		case 2:
		case ID_40002:
			/*hdialg1=CreateDialog(hinstance,MAKEINTRESOURCE(IDD_DIALOG1),hwnd,Dialog1Proc);
			if(hdialg1)
			{
				ShowWindow(hdialg1,SW_NORMAL);
			}
			break;*/

			if(isStart)
			{
				MessageBox(hwnd,TEXT("�������������У����Ժ�^_^"),TEXT("����"),NULL);
			}
			DialogBox(hinstance,MAKEINTRESOURCE(IDD_DIALOG1),hwnd,Dialog1Proc);
			
			iVscrollPos=myTime/1000;
			iVscrollPos=max(3,min(iVscrollPos,20));
			SetScrollPos(hScrollBar,SB_CTL,iVscrollPos,TRUE);

			TCHAR tempBuf[10];
			wsprintf(tempBuf,TEXT("%d  s"),myTime/1000);
			SetWindowText(hTime,tempBuf);
			break;

		//��ʾ��߼�¼
		case ID_40003:
			//SetDlgItemInt(hdialg2,IDC_EDIT1,myRecord,TRUE);
			//SetDlgItemText(hdialg2,IDC_EDIT1,);
			hDlgstatic1=GetDlgItem(hdialg2,IDC_STATIC2);
			TCHAR buff[20];
			wsprintf(buff,TEXT("%d"),myRecord);
			SetWindowText(hDlgstatic1,buff);
			ShowWindow(hdialg2,SW_NORMAL);

			break;

		case 1:
		//�˳�
		case ID_40004:
			exit(0);
			break;

		//����
		case ID_40014:
			//MessageBox(hwnd,TEXT("success"),TEXT("test"),MB_OK);
			//MessageBox(hwnd,TEXT("�����������˰ɣ�"),TEXT("����"),NULL);
			DialogBox(hinstance,MAKEINTRESOURCE(IDD_DIALOG3),hwnd,AboutDlgProc);
			break;
		}

		return 0;

	case WM_LBUTTONDOWN:

		iCurrentPos.x=LOWORD(lParam);
		iCurrentPos.y=HIWORD(lParam);

        if (PtInRect(&clickRect,iCurrentPos)&&isStart)
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

		if(PtInRect(&clickRect,iCurrentPos)&&isStart)
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
		if (PtInRect(&clickRect,iCurrentPos)&&isStart)
		{
			uncount++;
		}
		
		return 0;

	case WM_RBUTTONDBLCLK:
		iCurrentPos.x=LOWORD(lParam);
		iCurrentPos.y=HIWORD(lParam);
		if (PtInRect(&clickRect,iCurrentPos)&&isStart)
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
			
			isStart=false;
			isEnd=true;
			KillTimer(hwnd,ID_TIMER1);
			//MessageBox(hwnd,TEXT("Time is over!"),TEXT("��ʾ"),NULL);
			DialogBox(hinstance,MAKEINTRESOURCE(IDD_DIALOG4),hwnd,TimeOverDlgProc);
			InvalidateRect(hwnd,NULL,FALSE);
			
			break;
		}

		return 0;

	case WM_CREATE:

		hinstance=((LPCREATESTRUCT)lParam)->hInstance;
		

		cxChar=LOWORD(GetDialogBaseUnits());
		cyChar=HIWORD(GetDialogBaseUnits());

		for(int i=0;i<3;i++)
		{
			hButton[i]=CreateWindow(TEXT("button"),buttonLable[i]
			,WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
				0,0,0,0,
				hwnd,
				(HMENU)i,
				hinstance,NULL);
		}

		for(int j=0;j<3;j++)
		{
			hText[j]=CreateWindow(TEXT("static"),textLable[j],
				WS_CHILD|WS_VISIBLE|SS_LEFT,
				0,0,0,0,hwnd,(HMENU)(j+3),
				hinstance,NULL
				);
		}
		

		hstaticBrush=CreateSolidBrush(GetSysColor(COLOR_BTNHIGHLIGHT));

		hGreenBrush=CreateSolidBrush(RGB(0,255,0));

		hScrollBar=CreateWindow(TEXT("scrollbar"),
			NULL,WS_CHILD|WS_VISIBLE|WS_TABSTOP|SBS_VERT,
			0,0,0,0,
			hwnd,
			(HMENU)6,
			hinstance,
			NULL);

		hTime=CreateWindow(TEXT("static"),TEXT("3  s"),
			WS_CHILD|WS_VISIBLE|SS_LEFT,
			0,0,0,0,
			hwnd,
			(HMENU)7,
			hinstance,NULL);

		SetScrollRange(hScrollBar,SB_CTL,3,20,FALSE);
		SetScrollPos(hScrollBar,SB_CTL,3,FALSE);

		//SetTimer(hwnd,ID_TIMER1,5000,NULL);

		return 0 ;

    //�Թ�����������Ӧ�Ĵ���
	case WM_VSCROLL:
		switch(LOWORD(wParam))
		{
		case SB_PAGEDOWN:
			iVscrollPos+=6;
			break;
		case SB_LINEDOWN:
			iVscrollPos++;
			break;
		case SB_PAGEUP:
			iVscrollPos-=6;
			break;
		case SB_LINEUP:
			iVscrollPos--;
			break;
		case SB_TOP:
			iVscrollPos=3;
			break;
		case SB_BOTTOM:
			iVscrollPos=20;
			break;
		case SB_THUMBPOSITION:
			iVscrollPos=HIWORD(wParam);
			break;
		default:
			break;
		}

		iVscrollPos=max(3,min(iVscrollPos,20));
		SetScrollPos(hScrollBar,SB_CTL,iVscrollPos,TRUE);
		myTime=iVscrollPos*1000;

		TCHAR tempBuf[10];
		wsprintf(tempBuf,TEXT("%d  s"),myTime/1000);
		SetWindowText(hTime,tempBuf);

		return 0;

	case WM_SETFOCUS:
		SetFocus(hScrollBar);
		return 0;
	//���ڶԾ�̬���ֵı�����ɫ����
	case WM_CTLCOLORSTATIC:
         k=GetWindowLong((HWND)lParam,GWL_ID);
		 if(k>=3&&k<=5||k==7)
		 {
			 SetBkColor((HDC)wParam,GetSysColor(COLOR_BTNHIGHLIGHT));
			 return (LRESULT)hstaticBrush;
		 }
		break;
	case WM_SIZE:
		
		cxClient=LOWORD(lParam);
		cyClient=HIWORD(lParam);

		clickRect.left=cxClient*2/5-60;
		clickRect.right=cxClient*3/5+60;
		clickRect.bottom=cyClient;
		clickRect.top=0;

		//����button��λ��
		for (int i=0;i<3;i++)
		{
			MoveWindow(hButton[i],100*i+5,5,90,2*cyChar,TRUE);
		}

		//textLable��λ��
		for (int j=0;j<3;j++)
		{
				MoveWindow(hText[j],cxClient*3/5+120,cyClient*j/3,150,2*cyChar,TRUE);
			
		}
		
		//��������λ��
		MoveWindow(hScrollBar,cxClient/8-10,100,cxClient/14,cyClient-10*cyChar,TRUE);

		//ʱ���λ��
		MoveWindow(hTime,cxClient*3/5+260,cyClient*2/3,50,cyChar,TRUE);

		SetFocus(hwnd);

		return 0 ;

	case WM_PAINT:
		
		hdc=BeginPaint(hwnd,&ps);
	    holdBrush=(HBRUSH)SelectObject(hdc,hGreenBrush);
		Rectangle(hdc,clickRect.left,clickRect.top,clickRect.right,clickRect.bottom);

		//��ʾ��߼�¼
		if (myRecord>=tempRecord)
		{
			TextOut(hdc,cxClient*3/5+180,60,buf,wsprintf(buf,TEXT("������߼�¼Ϊ��%d"),myRecord));
			tempRecord=myRecord;
		}
		

		//��ʾ��ǰ��¼
		if (isEnd)
		{
			TextOut(hdc,cxClient*3/5+180,cyClient/3+40,buf,wsprintf(buf,TEXT("�ֻش���Ϊ��%d"),count));
			TextOut(hdc,cxClient*3/5+180,cyClient/3+80,buf,wsprintf(buf,TEXT("���Ϸ���������Ϊ��%d"),uncount));
			isEnd=false;
		}

		//TextOut(hdc,cxClient*3/5+300,cyClient*2/3,L" s",strlen(" s"));
		
		SelectObject(hdc,holdBrush);

		EndPaint(hwnd,&ps);

		return 0 ;

	case WM_DESTROY:
		DeleteObject(hGreenBrush);
		DeleteObject(hstaticBrush);
		PostQuitMessage(0);
		return 0 ;
	}
	return DefWindowProc (hwnd, message, wParam, lParam) ;
}

//����ʱ��ĶԻ���Ĵ���
BOOL CALLBACK  Dialog1Proc(HWND hDlg, UINT message,
							WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_INITDIALOG:
		SetFocus(GetDlgItem(hDlg, IDC_EDIT1)); // �������뽹��
		return FALSE ;
	case WM_COMMAND:
		switch(wParam)
		{
		case IDOK:
			//�õ��༭����ı�
			myTime=1000*GetDlgItemInt(hDlg,IDC_EDIT1,NULL,TRUE);
			
			EndDialog(hDlg,TRUE);
			return TRUE;

		case IDCANCEL:
			EndDialog(hDlg,TRUE);
			return TRUE;

		}
		break;
	}

	return FALSE;
}



//���ڶԻ���Ĵ���
BOOL CALLBACK AboutDlgProc (HWND hDlg, UINT message,
							WPARAM wParam, LPARAM lParam)
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

BOOL CALLBACK RecordDlgProc (HWND hDlg, UINT message,
							WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			EndDialog(hDlg,TRUE);
			return TRUE;
		case IDCANCEL:
			EndDialog(hDlg,TRUE);
			return TRUE;
		}
	}

	return FALSE;
}

//ʱ�䵽
BOOL CALLBACK TimeOverDlgProc(HWND hDlg, UINT message,
							 WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			EndDialog(hDlg,TRUE);
			return TRUE;
		}
	}

	return FALSE;
}