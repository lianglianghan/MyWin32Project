/*
  ���ܣ������������Ե�ͷ�ļ�
  ���ߣ�����
  ���ڣ�2013.9.19
*/


//������ʾ������
#define NUMLINES ((int) (sizeof sysmetrics / sizeof sysmetrics [0]))

//����ṹ��
struct  
{
	int  	iIndex ;       //������
	TCHAR * 	szLabel ;  //ָ����ַ���ָ��
 	TCHAR * 	szDesc ; //ָ����ַ���ָ��
}


//������sysmetrics[]�ṹ����ĳ�ʼ����
sysmetrics [] =   {
  	SM_CXSCREEN, TEXT ("SM_CXSCREEN"),
		TEXT ("Screen width in pixels"),
	SM_CYSCREEN, TEXT ("SM_CYSCREEN"), 
		TEXT ("Screen height in pixels"),
	SM_CXVSCROLL, TEXT ("SM_CXVSCROLL"),
		TEXT ("Vertical scroll width"),
	SM_CYHSCROLL, TEXT ("SM_CYHSCROLL"),
		TEXT ("Horizontal scroll height"),
	SM_CYCAPTION, TEXT ("SM_CYCAPTION"),
		TEXT ("Caption bar height"),
	SM_CXBORDER, TEXT ("SM_CXBORDER"), 
		TEXT ("Window border width"),
	SM_CYBORDER,	TEXT ("SM_CYBORDER"), 
	TEXT ("Window border height"),
  	SM_CXSCREEN, TEXT ("SM_CXSCREEN"),
		TEXT ("Screen width in pixels"),
	SM_CYSCREEN, TEXT ("SM_CYSCREEN"), 
		TEXT ("Screen height in pixels"),
	SM_CXVSCROLL, TEXT ("SM_CXVSCROLL"),
		TEXT ("Vertical scroll width"),
	SM_CYHSCROLL, TEXT ("SM_CYHSCROLL"),
		TEXT ("Horizontal scroll height"),
	SM_CYCAPTION, TEXT ("SM_CYCAPTION"),
		TEXT ("Caption bar height"),
	SM_CXBORDER, TEXT ("SM_CXBORDER"), 
		TEXT ("Window border width"),
	SM_CYBORDER,	TEXT ("SM_CYBORDER"), 
	TEXT ("Window border height"),
  	SM_CXSCREEN, TEXT ("SM_CXSCREEN"),
		TEXT ("Screen width in pixels"),
	SM_CYSCREEN, TEXT ("SM_CYSCREEN"), 
		TEXT ("Screen height in pixels"),
	SM_CXVSCROLL, TEXT ("SM_CXVSCROLL"),
		TEXT ("Vertical scroll width"),
	SM_CYHSCROLL, TEXT ("SM_CYHSCROLL"),
		TEXT ("Horizontal scroll height"),
	SM_CYCAPTION, TEXT ("SM_CYCAPTION"),
		TEXT ("Caption bar height"),
	SM_CXBORDER, TEXT ("SM_CXBORDER"), 
		TEXT ("Window border width"),
	SM_CYBORDER,	TEXT ("SM_CYBORDER"), 
	TEXT ("Window border height"),
  	SM_CXSCREEN, TEXT ("SM_CXSCREEN"),
		TEXT ("Screen width in pixels"),
	SM_CYSCREEN, TEXT ("SM_CYSCREEN"), 
		TEXT ("Screen height in pixels"),
	SM_CXVSCROLL, TEXT ("SM_CXVSCROLL"),
		TEXT ("Vertical scroll width"),
	SM_CYHSCROLL, TEXT ("SM_CYHSCROLL"),
		TEXT ("Horizontal scroll height"),
	SM_CYCAPTION, TEXT ("SM_CYCAPTION"),
		TEXT ("Caption bar height"),
	SM_CXBORDER, TEXT ("SM_CXBORDER"), 
		TEXT ("Window border width"),
	SM_CYBORDER,	TEXT ("SM_CYBORDER"), 
	TEXT ("Window border height"),
  	SM_CXSCREEN, TEXT ("SM_CXSCREEN"),
		TEXT ("Screen width in pixels"),
	SM_CYSCREEN, TEXT ("SM_CYSCREEN"), 
		TEXT ("Screen height in pixels"),
	SM_CXVSCROLL, TEXT ("SM_CXVSCROLL"),
		TEXT ("Vertical scroll width"),
	SM_CYHSCROLL, TEXT ("SM_CYHSCROLL"),
		TEXT ("Horizontal scroll height"),
	SM_CYCAPTION, TEXT ("SM_CYCAPTION"),
		TEXT ("Caption bar height"),
	SM_CXBORDER, TEXT ("SM_CXBORDER"), 
		TEXT ("Window border width"),
	SM_CYBORDER,	TEXT ("SM_CYBORDER"), 
	TEXT ("Window border height")
};
