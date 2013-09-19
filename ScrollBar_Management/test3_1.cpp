/* 
   功能：添加水平滚动条、竖直滚动条
   作者：亮亮
   日期：2013.9.19

*/

#include <windows.h>
#include "system1.h"

//置前声明
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;


LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;
//窗口函数原型说明
int WINAPI WinMain (HINSTANCE hInstance, 
 HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT ("SysMets2") ;

	HWND 	hwnd ;
	MSG   	msg ;
	WNDCLASS 	wndclass ;

	wndclass.style	    = CS_HREDRAW | CS_VREDRAW ;
	//指向窗口处理函数
 	wndclass.lpfnWndProc	= WndProc ;
 	wndclass.cbClsExtra 	= 0 ;
 	wndclass.cbWndExtra 	= 0 ;
 	wndclass.hInstance	= hInstance; 
 	wndclass.hIcon  	= LoadIcon (NULL, 
							IDI_APPLICATION) ;
	wndclass.hCursor 	= LoadCursor (NULL, IDC_ARROW);

	wndclass.hbrBackground 	=(HBRUSH)GetStockObject
					(WHITE_BRUSH) ;
	wndclass.lpszMenuName  	= NULL ;
	wndclass.lpszClassName 	= szAppName ;
							
	if (!RegisterClass (&wndclass))  
    {
		MessageBox (NULL, 
		  TEXT ("This program requires Windows NT!"), 
          szAppName, MB_ICONERROR) ;
                 
		return 0; 
	}
	hwnd = CreateWindow( 
			szAppName,
			TEXT ("Get System Metrics No. 2"),	
			WS_OVERLAPPEDWINDOW| WS_VSCROLL | WS_HSCROLL,
			CW_USEDEFAULT,	// initial x position
			CW_USEDEFAULT,	// initial y position
			CW_USEDEFAULT,	// initial x size
			CW_USEDEFAULT,	// initial y size
			NULL,			// parent window handle
		    NULL,	        // 16window menu handle
		    hInstance,	    // program instance handle
		    NULL) ; 	    // creation parameters

	ShowWindow (hwnd, iCmdShow) ;
	UpdateWindow (hwnd) ;

	while (GetMessage (&msg, NULL, 0, 0))
    {
		TranslateMessage (&msg) ;
		DispatchMessage (&msg) ;
    }
	return msg.wParam ;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, 
				          WPARAM wParam, LPARAM lParam)
{
	static int cxChar,cxCaps,cyChar,
			   cyClient,cxClient,iVscrollPos, iHscrollPos; 
	HDC         hdc ;	
	int         i,x, y ;	
	PAINTSTRUCT ps ;
	TCHAR  szBuffer[10] ;
	TEXTMETRIC  tm ;
	switch (message)
	{
	case	WM_CREATE:
	  	hdc = GetDC (hwnd); 
	   	GetTextMetrics (hdc, &tm) ;
		cxChar = tm.tmAveCharWidth ;

		cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) 
			    * cxChar / 2 ;

		cyChar = tm.tmHeight + tm.tmExternalLeading ;

	   	ReleaseDC (hwnd, hdc) ;

		SetScrollRange (hwnd,SB_VERT,0,
						NUMLINES - 1, FALSE) ;
						
		SetScrollPos   (hwnd, SB_VERT, 
						iVscrollPos, TRUE) ;

		SetScrollRange(hwnd,SB_HORZ,0,47,FALSE);
	
		SetScrollPos(hwnd,SB_HORZ,iHscrollPos,TRUE);


		return 0 ;//end of WM_CREATE
	case WM_SIZE:
		 /* 在窗口大小改变时,Windows给窗口函数发送消息,
		消息是一个MSG结构,MSG中有四个项,
		它们是:hwnd是指向窗口的指针,消息名WM_SIZE,
		及wparam,lParam参数.WinMain中的消息循环把MSG送到窗口函数,
		所以窗口函数的四个参数对应MSG中的四个项.窗口函数中,lParam参数代表当前窗口显示区域的坐标, 
		lParam参数的低位字段中包含显示区域的宽度,高位字段中包含显示区域的高度*/
		cyClient = HIWORD (lParam) ;
		cxClient = LOWORD(lParam);

		return 0 ;
	//处理竖直滚动条
	case WM_VSCROLL:
		//wParam的低两位存放的是滚动消息的通知码
		switch (LOWORD (wParam))
		{
		case SB_LINEUP:
  			iVscrollPos -= 1 ;
			break ;
		case SB_LINEDOWN:
			iVscrollPos += 1 ; 
			break ;
		case SB_PAGEUP:
			iVscrollPos -= cyClient / cyChar ; 
			break ;
		case SB_PAGEDOWN:
			iVscrollPos += cyClient / cyChar ;
			break ;
		case SB_THUMBPOSITION:
			//wParam的高两位存放的是滚动条当前的位置
			iVscrollPos = HIWORD (wParam) ;
			break ;
		case SB_TOP:
			iVscrollPos =0;
			break;
		case SB_BOTTOM:
			iVscrollPos =NUMLINES-1;
			break;
		default :
			break ;
		}
	iVscrollPos = max (0, 
					min (iVscrollPos, NUMLINES - 1)) ;
	if (iVscrollPos != GetScrollPos (hwnd,SB_VERT))

	{
		//设置滚动条当前的位置
		SetScrollPos (hwnd,SB_VERT,iVscrollPos,TRUE) ;
		//重画用户区
		InvalidateRect (hwnd,NULL,TRUE) ;
    }

		return 0 ;


	//用来处理水平滚动条的消息
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
			iHscrollPos-=cxClient/cxChar;
			break;
		case SB_PAGERIGHT:
			iHscrollPos+=cxClient/cxChar;
			break;
		case SB_THUMBPOSITION:
			iHscrollPos=HIWORD(wParam);
			break;
		case SB_LEFT:
			iHscrollPos=0;
			break;
		case SB_RIGHT:
			iHscrollPos=47;
			break;
		default:
			break;

		}


		iHscrollPos=max(0,min(iHscrollPos,47));
		if(iHscrollPos!=GetScrollPos(hwnd,SB_HORZ))
		{
			SetScrollPos(hwnd,SB_HORZ,iHscrollPos,TRUE);
			InvalidateRect(hwnd,NULL,TRUE);
		}

		return 0;
	case WM_PAINT:
		hdc = BeginPaint (hwnd, &ps); 
		
		for (i = 0 ; i < NUMLINES ; i++) 
		{
			x=cxChar*(0-iHscrollPos)*3/2;
			y = cyChar * (i - iVscrollPos) ;
			TextOut (hdc, x, y,sysmetrics[i].szLabel,
				lstrlen (sysmetrics[i].szLabel)) ;
			TextOut (hdc,x+22 * cxCaps, y,
				sysmetrics[i].szDesc, 
			lstrlen (sysmetrics[i].szDesc)) ;
			SetTextAlign (hdc, TA_RIGHT | TA_TOP) ;
			TextOut (hdc, x+22 * cxCaps + 40 * cxChar, 
			  y, szBuffer,
			  wsprintf (szBuffer, TEXT ("%5d"),
			  GetSystemMetrics 
			  (sysmetrics[i].iIndex))) ;
			SetTextAlign (hdc, TA_LEFT | TA_TOP) ;
        }
		EndPaint (hwnd, &ps); 
		return 0 ;

	case WM_DESTROY:
		PostQuitMessage (0) ; 
		return 0 ;
     }
	return DefWindowProc (hwnd, message, 
						  wParam, lParam) ; 
}