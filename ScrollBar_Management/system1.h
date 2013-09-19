/*
  功能：这是用来测试的头文件
  作者：亮亮
  日期：2013.9.19
*/


//定义显示行数。
#define NUMLINES ((int) (sizeof sysmetrics / sizeof sysmetrics [0]))

//定义结构。
struct  
{
	int  	iIndex ;       //索引号
	TCHAR * 	szLabel ;  //指向宽字符的指针
 	TCHAR * 	szDesc ; //指向宽字符的指针
}


//下面是sysmetrics[]结构数组的初始化。
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
