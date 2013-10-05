/************************************************************************/
/* ���ܣ�����λͼ������ֱ̬��
   ���ߣ�����
   ���ڣ�2013.10.4
   ע�ͣ����߱Ƚ϶��ʱ����Щ�������ر����أ�һ��Ҫ�����
   ���⣺��MOUSE_MOVE�У���Ϊ�ػ��˿ͻ�����������ǰ������û�з����ڴ��豸�������У�
          һ�����ߵ������Ƚ϶��ʱ�򣬾ͻᷢ���Ƚ����ص�������˸���⡣
   �Ľ�������1.��MOUSE_MOVE��ɾ����ǰ�м����
              2.��ԭ�Ȼ��õ��߼��뵽�ڴ��豸��������
   ���������1.�ڻ���ֱ�ߵ�ʱ��ʼ�ղ�Ҫ����WM_PAINT��Ϣ
              2.������ƶ������У�����SetRop2��hdc,R2_NOT)������������һ����̬��
			  3.��iCurrenPos����Ϊ��̬��,ÿ���ƶ����Ȳ���ԭ�����ߣ�Ȼ���ڰѵ�ǰ����λ�ø���iCurrentPos
   
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
	//������þ������Ĵ�С
	static int     cxClient, cyClient;
	//������ø���ͼƬ�Ĵ�С
	static int     cx1,cy1,cx2,cy2,cx3,cy3;
	//�������ͼƬ�Ŀ�Ⱥ͸߶�
	BITMAP         bitmap ;
	//�豸��������ڴ��豸������
	HDC            hdc, hdcMem;
	//ʵ�����
	HINSTANCE      hInstance ;

	PAINTSTRUCT    ps ;

	static POINT   begin[1000],end[1000];

	static  POINT  iCurrentPos;

	static boolean isPressed=FALSE;

	//����ͳ���ߵ�����
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
			//ȡ��ǰ����ɫ�ķ�ɫ�������ε���û�л�һ��
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
			//����̬��
			hdc=GetDC(hwnd);

			//�������յ�����
		
			MoveToEx(hdc,begin[count].x,begin[count].y,NULL);
			LineTo(hdc,end[count].x,end[count].y);

			ReleaseDC(hwnd,hdc);
		}
		return 0;
	
	case WM_CREATE:
		hdc=GetDC(hwnd);
		hInstance = ((LPCREATESTRUCT) lParam)->hInstance ;
		
		//���ص�һ��λͼ
		hBitmap1 = LoadBitmap (hInstance, TEXT("Clouds")) ;

		GetObject (hBitmap1, sizeof (BITMAP), &bitmap) ;

		cx1 = bitmap.bmWidth ;
		cy1 = bitmap.bmHeight ;
		
		//���صڶ���λͼ
		hBitmap2=LoadBitmap(hInstance,TEXT("BP"));
		GetObject(hBitmap2,sizeof(BITMAP),&bitmap);
		cx2=bitmap.bmWidth;
		cy2=bitmap.bmHeight;
		
		//���ص�����λͼ
		hBitmap3=LoadBitmap(hInstance,TEXT("MaskBP"));
		GetObject(hBitmap3,sizeof(BITMAP),&bitmap);
		cx3=bitmap.bmWidth;
		cy3=bitmap.bmHeight;

		ReleaseDC(hwnd,hdc);
		return 0 ;

	case WM_SIZE:
		//�ͻ����Ŀ�Ⱥ͸߶�
		cxClient = LOWORD (lParam) ;
		cyClient = HIWORD (lParam) ;
		return 0 ;

	case WM_PAINT:
		hdc = BeginPaint (hwnd, &ps) ;

		hdcMem = CreateCompatibleDC (hdc) ;
		hOldmap=(HBITMAP)SelectObject (hdcMem, hBitmap1) ;
		
		//����
		//��������������ͻ�������
		StretchBlt(hdc, 0, 0, cxClient, cyClient, hdcMem, 0, 0,cx1,cy1, SRCCOPY) ;
		//BitBlt(hdc, 0, 0, cxClient, cyClient, hdcMem, 0, 0 SRCCOPY) ;

		//��ʾ��һ��λͼ
		SelectObject(hdcMem,hBitmap2);
		BitBlt(hdc,100,10,cx2,cy2,hdcMem,0,0,SRCCOPY);

		//��ʾ�ڶ���λͼ
		SelectObject(hdcMem,hBitmap3);
		BitBlt(hdc,250,10,cx3,cy3,hdcMem,0,0,SRCCOPY);

		//�����õ�͸����λͼ��1-->��λ��(������maskͼ�� 2-->��λ�루��bp��)
	
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
