/************************************************************************/
/* 功能：绘制位图、画动态直线
   作者：亮亮
   日期：2013.10.4
   注释：当线比较多的时候，那些线闪的特别严重（一定要解决）
   问题：在MOUSE_MOVE中，因为重画了客户区，由于以前画的线没有放在内存设备描述表中，
          一旦当线的条数比较多的时候，就会发生比较严重的线体闪烁问题。
   改进方案：1.在MOUSE_MOVE中删除以前中间的线
              2.将原先画好的线加入到内存设备描述表中
   解决方案：1.在绘制直线的时候，始终不要发送WM_PAINT消息
              2.在鼠标移动过程中，利用SetRop2（hdc,R2_NOT)画线来擦除上一条动态线
			  3.将iCurrenPos设置为静态的,每次移动后先擦除原来的线，然后在把当前鼠标的位置赋给iCurrentPos
   
*/
/************************************************************************/

#include <windows.h>
#define maxLines 1000

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
					PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName [] = TEXT ("BitMap") ;
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

	hwnd = CreateWindow (szAppName, TEXT ("LoadBitmap Demo"), 
		WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL) ;

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
	static HBITMAP  hOldmap,hBitmap1,hBitmap2,hBitmap3 ;
	//用来获得矩形区的大小
	static int     cxClient, cyClient;
	//用来获得各个图片的大小
	static int     cx1,cy1,cx2,cy2,cx3,cy3;
	//用来获得图片的宽度和高度
	BITMAP         bitmap ;
	//设备描述表和内存设备描述表
	HDC            hdc, hdcMem;
	//实例句柄
	HINSTANCE      hInstance ;

	PAINTSTRUCT    ps ;

	static POINT   begin[1000],end[1000];

	static  POINT  iCurrentPos;

	static boolean isPressed=FALSE;

	//用来统计线的条数
	static int count=0;
	
	switch (message)
	{
	case WM_LBUTTONDOWN:
		/*if(!isPressed)
		{
			count++;
			f[count].x=LOWORD(lParam);
			f[count].y=HIWORD(lParam);
			isPressed=TRUE;
			
		}
		*/
		
		if(!isPressed)
		{
			isPressed=TRUE;
			count++;
			begin[count].x=LOWORD(lParam);
			begin[count].y=HIWORD(lParam);
			iCurrentPos.x=LOWORD(lParam);
			iCurrentPos.y=HIWORD(lParam);
			hdc=GetDC(hwnd);
			MoveToEx(hdc,begin[count].x,begin[count].y,NULL);
			LineTo(hdc,begin[count].x,begin[count].y);
			ReleaseDC(hwnd,hdc);
			
		}

		return 0;

	case WM_MOUSEMOVE:
		if(isPressed)
		{
			hdc=GetDC(hwnd);
			//取当前背景色的反色，画两次等于没有画一样
			SetROP2(hdc,R2_NOT);
			
			MoveToEx(hdc,begin[count].x,begin[count].y,NULL);
			LineTo(hdc,iCurrentPos.x,iCurrentPos.y);
				
			iCurrentPos.x=LOWORD(lParam);
			iCurrentPos.y=HIWORD(lParam);
			MoveToEx(hdc,begin[count].x,begin[count].y,NULL);
			LineTo(hdc,iCurrentPos.x,iCurrentPos.y);
			ReleaseDC(hwnd,hdc);
		}

		return 0;

	case WM_LBUTTONUP:
		/*if(isPressed)
		{

			e[count].x=LOWORD(lParam);
			e[count].y=HIWORD(lParam);
			isPressed=FALSE;
			InvalidateRect(hwnd,NULL,FALSE);
		}*/

		if(isPressed)
		{
			end[count].x=LOWORD(lParam);
			end[count].y=HIWORD(lParam);
			isPressed=FALSE;
			//InvalidateRect(hwnd,NULL,FALSE);
			//画动态线
			hdc=GetDC(hwnd);

			//画出最终的曲线
		
			MoveToEx(hdc,begin[count].x,begin[count].y,NULL);
			LineTo(hdc,end[count].x,end[count].y);

			ReleaseDC(hwnd,hdc);
		}
		return 0;
	
	case WM_CREATE:
		hdc=GetDC(hwnd);
		hInstance = ((LPCREATESTRUCT) lParam)->hInstance ;
		
		//加载第一个位图
		hBitmap1 = LoadBitmap (hInstance, TEXT("Clouds")) ;

		GetObject (hBitmap1, sizeof (BITMAP), &bitmap) ;

		cx1 = bitmap.bmWidth ;
		cy1 = bitmap.bmHeight ;
		
		//加载第二个位图
		hBitmap2=LoadBitmap(hInstance,TEXT("BP"));
		GetObject(hBitmap2,sizeof(BITMAP),&bitmap);
		cx2=bitmap.bmWidth;
		cy2=bitmap.bmHeight;
		
		//加载第三个位图
		hBitmap3=LoadBitmap(hInstance,TEXT("MaskBP"));
		GetObject(hBitmap3,sizeof(BITMAP),&bitmap);
		cx3=bitmap.bmWidth;
		cy3=bitmap.bmHeight;

		ReleaseDC(hwnd,hdc);
		return 0 ;

	case WM_SIZE:
		//客户区的宽度和高度
		cxClient = LOWORD (lParam) ;
		cyClient = HIWORD (lParam) ;
		return 0 ;

	case WM_PAINT:
		hdc = BeginPaint (hwnd, &ps) ;

		hdcMem = CreateCompatibleDC (hdc) ;
		hOldmap=(HBITMAP)SelectObject (hdcMem, hBitmap1) ;
		
		//背景
		//可以用来将真个客户区画满
		StretchBlt(hdc, 0, 0, cxClient, cyClient, hdcMem, 0, 0,cx1,cy1, SRCCOPY) ;
		//BitBlt(hdc, 0, 0, cxClient, cyClient, hdcMem, 0, 0 SRCCOPY) ;

		//显示第一个位图
		SelectObject(hdcMem,hBitmap2);
		BitBlt(hdc,100,10,cx2,cy2,hdcMem,0,0,SRCCOPY);

		//显示第二个位图
		SelectObject(hdcMem,hBitmap3);
		BitBlt(hdc,250,10,cx3,cy3,hdcMem,0,0,SRCCOPY);

		//用来得到透明的位图（1-->按位或(背景与mask图） 2-->按位与（与bp）)
	
		BitBlt(hdc,400,10,cx3,cy3,hdcMem,0,0,SRCPAINT);
		SelectObject(hdcMem,hBitmap2);
		BitBlt(hdc,400,10,cx2,cy2,hdcMem,0,0,SRCAND);

		if(count!=0)
		{
			for(int i=1;i<=count;i++)
			{
				MoveToEx(hdc,begin[i].x,begin[i].y,NULL);
				LineTo(hdc,end[i].x,end[i].y);
			}
			
		}


		DeleteDC (hdcMem) ;
		EndPaint (hwnd, &ps) ;
		return 0 ;

	case WM_DESTROY:

		DeleteObject (hBitmap1) ;
		DeleteObject(hBitmap2);
		PostQuitMessage (0) ;
		return 0 ;
	}
	return DefWindowProc (hwnd, message, wParam, lParam) ;
}
