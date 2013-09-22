/*
  ���ܣ�����GDI���������ɰ��Ŀ�ͨͼ��̫��ͼ   ��һ���ȽϿɰ��Ĳ����̣�
  ���ߣ�����
  ���ڣ�2013.9.20
  ע�ͣ���Щ���ܻ����Ǻ����ƣ��д��Ľ�
*/



#include <windows.h>

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
     static TCHAR szAppName[] = TEXT ("DrawItem") ;
     HWND         hwnd ;
     MSG          msg ;
     WNDCLASS     wndclass ;

     wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
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
     
     hwnd = CreateWindow (szAppName,                                        // window class name
                          TEXT ("The tai chi by the fourth group"),                                   // window caption
                          WS_OVERLAPPEDWINDOW|WS_VSCROLL|WS_HSCROLL,        // window style
                          CW_USEDEFAULT,              // initial x position
                          CW_USEDEFAULT,              // initial y position
                          CW_USEDEFAULT,              // initial x size
                          CW_USEDEFAULT,              // initial y size
                          NULL,                       // parent window handle
                          NULL,                       // window menu handle
                          hInstance,                  // program instance handle
                          NULL) ;                     // creation parameters
     
     ShowWindow (hwnd, iCmdShow) ;
     UpdateWindow (hwnd) ;
     
     while (GetMessage (&msg, NULL, 0, 0))
     {
          TranslateMessage (&msg) ;
          DispatchMessage (&msg) ;
     }
     return msg.wParam ;
}



LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	
	static HPEN oldPen,hwhitePen,hblackPen,hblackPen1,hnullPen,hbluePen,hpinkPen
		,hpinkPen1,hredPen,hgreenPen;
	static HBRUSH oldBrush,hwhiteBrush,hblackBrush,hpinkBrush
		,hgreenBrush,hredBrush,hgoldBrush,hblueBrush,hscBrush;

	static cxClient,cyClient;
	static SIZE size;
	
	int x,y;

	//���ô�Բ�İ뾶��СԲ�İ뾶
	int add=50;
	int add1=10;


	static iHscrollPos,iVscrollPos;
	static iVmax=120,iHmax=250;
    
    //���岻���̵����ԭ����������Ӧ�İ뾶
	int x1,y1;
	
	

	switch(message)
	{
	case WM_CREATE:
		//�Զ���Ļ���
		hwhitePen=CreatePen(PS_SOLID,3,RGB(255,255,255));
		hblackPen=CreatePen(PS_SOLID,0,RGB(0,0,0));
		hblackPen1=CreatePen(PS_SOLID,1,RGB(0,0,0));
		hpinkPen=CreatePen(PS_SOLID,0,RGB(255,192,203));
		hpinkPen1=CreatePen(PS_SOLID,2,RGB(255,192,203));
		hredPen=CreatePen(PS_SOLID,3,RGB(255,0,0));
		hnullPen=(HPEN)GetStockObject(NULL_PEN);
		hgreenPen=CreatePen(PS_SOLID,3,RGB(0,255,0));

		

		//�Զ���Ļ�ˢ
		hwhiteBrush=CreateSolidBrush(RGB(255,255,255));
		hblackBrush=CreateSolidBrush(RGB(0,0,0));
        hgreenBrush=CreateSolidBrush(RGB(0,200,255));
		hblueBrush=CreateSolidBrush(RGB(0,0,255));
		hpinkBrush=CreateSolidBrush(RGB(255,192,203));
		hredBrush=CreateSolidBrush(RGB(255,0,0));
		hgoldBrush=CreateSolidBrush(RGB(255,255,0));
		hscBrush=CreateSolidBrush(RGB(153,204,0));


		//������ֱ�������ĳ�ʼλ�ú͹�����Χ
		SetScrollRange(hwnd,SB_VERT,0,iVmax,FALSE);
		SetScrollPos(hwnd,SB_VERT,iVscrollPos,TRUE);

		//��ˮƽ������������Ӧ������
		SetScrollRange(hwnd,SB_HORZ,0,iHmax,FALSE);
		SetScrollPos(hwnd,SB_HORZ,0,TRUE);

		return 0;
	case WM_SIZE:

		cxClient=LOWORD(lParam);
		cyClient=HIWORD(lParam);

		

		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hwnd,&ps);
	    
		//����ӳ��ģʽ�Ĳ���
		SetMapMode(hdc,MM_ANISOTROPIC);
		SetViewportExtEx(hdc,3,3,&size);
		SetWindowExtEx(hdc,1,-1,&size);
		/*x=cxClient/6;
		y=(-cyClient)/6;*/
		x=100-iHscrollPos;
		y=-(100)+iVscrollPos;
		
	    

		//���Ȼ���������β�������Ļ���������ɫΪNULL_PEN
		oldPen=(HPEN)SelectObject(hdc,hnullPen);
		//��뻡��Ĭ�ϵĻ�ˢ����ɫ��
		Pie(hdc,x-add,y+add,x+add,y-add,x,y+add,x,y-add);
		//���û�ˢ��ɫΪ��ɫ
		oldBrush=(HBRUSH)SelectObject(hdc,hblackBrush);
		//���Ұ뻡
		Pie(hdc,x-add,y+add,x+add,y-add,x,y-add,x,y+add);
		//���û���Ϊ��ɫ��1�ţ�
		SelectObject(hdc,hblackPen1);
		//����Χ�������»���
		Arc(hdc,x-add,y+add,x+add,y-add,x,y+add,x,y-add);
		Arc(hdc,x-add,y+add,x+add,y-add,x,y-add,x,y+add);
		
		
		//���������Բ���ұ�����
		SelectObject(hdc,hnullPen);
		SelectObject(hdc,hwhiteBrush);
		Pie(hdc,x-add/2,y+add,x+add/2,y,x,y,x,y+add);

		//���������Բ����������������Ӧ����ɫ
		SelectObject(hdc,hblackPen);
		SelectObject(hdc,hblackBrush);
		Pie(hdc,x-add/2,y,x+add/2,y-add,x,y,x,y+add);
		
		//��������
		SelectObject(hdc,hblackBrush);
		Ellipse(hdc,x-add1/2,y+add/2+add1/2,x+add1/2,y+add/2-add1/2);
		
		//��������
		SelectObject(hdc,hwhiteBrush);
		Ellipse(hdc,x-add1/2,y-add/2+add1/2,x+add1/2,y-add/2-add1/2);
		



		//���滭�ɰ��Ĳ�����

		SetMapMode(hdc,MM_ANISOTROPIC);
		SetViewportExtEx(hdc,3,3,&size);
		SetWindowExtEx(hdc,1,-1,&size);


		//�����������ϵ�ĵ�
		x1=300-iHscrollPos;
		y1=-100+iVscrollPos;

	    //���û��ʺͻ�ˢ���������ͷ��
		SelectObject(hdc,hnullPen);
		SelectObject(hdc,hgoldBrush);
		Ellipse(hdc,x1-30,y1+30,x1+30,y1-30);

		//�������۾�
		SelectObject(hdc,hblueBrush);
		Ellipse(hdc,x1-10-3,y1+10+3,x1-10+3,y1+10-3);
		Ellipse(hdc,x1+10-3,y1+10+3,x1+10+3,y1+10-3);
		
		//���ǿ�
		SelectObject(hdc,hredPen);
		MoveToEx(hdc,x1,y1-2,NULL);
		LineTo(hdc,x1,y1-8);
		
		//�����
		SelectObject(hdc,hgreenPen);
		Arc(hdc,x1-15,y1+20,x1+15,y1-20,x1-10,y1-20,x1+10,y1-20);
		
		//������������Ĳ���
		SelectObject(hdc,hnullPen);
		SelectObject(hdc,hredBrush);
		Ellipse(hdc,x1-3-50,y1-30+2,x1-3+50,y1-30-50-50+2);

		//������
		SelectObject(hdc,hscBrush);

		Ellipse(hdc,x1-2-4,y1-30-50-3+30+4,x1-2+4,y1-30-50-3+30-4);

		Ellipse(hdc,x1-4-4,y1-30-50-3+10+4,x1-4+4,y1-30-50-3+10-4);

		Ellipse(hdc,x1-5-4,y1-30-50-3-10+4,x1-5+4,y1-30-50-3-10-4);


		EndPaint(hwnd,&ps);
		return 0;
	case WM_VSCROLL:
		switch(LOWORD(wParam))
		{
		case SB_LINEUP:
			iVscrollPos-=1;
			break;
		case SB_LINEDOWN:
			iVscrollPos+=1;
			break;
		case SB_PAGEUP:
			iVscrollPos-=25;
			break;
		case SB_PAGEDOWN:
			iVscrollPos+=25;
			break;
		case SB_THUMBPOSITION:
			iVscrollPos=HIWORD(wParam);
			break;
		case SB_TOP:
			iVscrollPos=0;
			break;
		case SB_BOTTOM:
			iVscrollPos=iVmax;
			break;
		default:
			break;
		}


		iVscrollPos=max(0,min(iVscrollPos,iVmax));

		if(iVscrollPos!=GetScrollPos(hwnd,SB_VERT))
		{
			SetScrollPos(hwnd,SB_VERT,iVscrollPos,TRUE);

			InvalidateRect(hwnd,NULL,TRUE);
		}

		return 0;
	case WM_HSCROLL:
		switch(LOWORD(wParam))
		{
		case SB_LINELEFT:
			iHscrollPos-=1;
			break;
		case SB_LINERIGHT:
			iHscrollPos+=1;
			break;
		case SB_PAGELEFT:
			iHscrollPos-=50;
			break;
		case SB_PAGERIGHT:
			iHscrollPos+=50;
			break;
		case SB_THUMBPOSITION:
			iHscrollPos=HIWORD(wParam);
			break;
		case SB_LEFT:
			iHscrollPos=0;
			break;
		case SB_RIGHT:
			iHscrollPos=iHmax;
			break;
		default:
			break;
		}

		iHscrollPos=max(0,min(iHscrollPos,iHmax));


		if(iHscrollPos!=GetScrollPos(hwnd,SB_HORZ))
		{
			SetScrollPos(hwnd,SB_HORZ,iHscrollPos,TRUE);
			InvalidateRect(hwnd,NULL,TRUE);
		}
		return 0;
	case WM_DESTROY:
		DeleteObject(hgreenPen);
		DeleteObject(hredPen);
		DeleteObject(hpinkPen);
		DeleteObject(hwhitePen);
		DeleteObject(hblackPen);
		DeleteObject(hblackPen1);
		DeleteObject(hwhiteBrush);
		DeleteObject(hblackBrush);
		DeleteObject(hpinkBrush);
		DeleteObject(hredBrush);
		DeleteObject(hgoldBrush);
		DeleteObject(hblueBrush);
		DeleteObject(hscBrush);
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd,message,wParam,lParam);
}