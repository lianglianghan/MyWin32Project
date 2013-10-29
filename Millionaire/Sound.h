#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

#ifndef SOUND_H
#define SOUND_H

class PlayMySound
{
public :

	//static TCHAR buf[128];

	static void playBkg(TCHAR buf[128])
	{
		mciSendString(TEXT("close adu"),buf,lstrlen(buf),NULL);
		mciSendString(TEXT("open ./sound/millionaire.mp3 type mpegvideo alias adu"),buf,lstrlen

			(buf),NULL);
		mciSendString(TEXT("play adu"),buf,lstrlen(buf),NULL);

		mciSendString(TEXT("play adu repeat"),buf,lstrlen(buf),NULL); 

	}

	static void playGameover(TCHAR buf[128])
	{
		mciSendString(TEXT("open ./sound/gameover.wav type mpegvideo alias gameover"),buf,lstrlen(buf),NULL);
		mciSendString(TEXT("play gameover"),buf,lstrlen(buf),NULL);
		//mciSendString(TEXT("play gameover repeat"),buf,lstrlen(buf),NULL);
	}

	static void playJinBi(TCHAR buf[128])
	{
		mciSendString(TEXT("close jinbi"),buf,lstrlen(buf),NULL);
		mciSendString(TEXT("open ./sound/jinbi.wav type avivideo alias jinbi"),buf,lstrlen

			(buf),NULL);

		mciSendString(TEXT("play jinbi"),buf,lstrlen(buf),NULL);
	}

	static void playJiashi(TCHAR buf[128])
	{
		mciSendString(TEXT("close jiashi"),buf,lstrlen(buf),NULL);
		mciSendString(TEXT("open ./sound/jiashi.wav type avivideo alias jiashi"),buf,lstrlen

			(buf),NULL);

		mciSendString(TEXT("play jiashi"),buf,lstrlen(buf),NULL);
	}

	static void playZhaDan(TCHAR buf[128])
	{
		mciSendString(TEXT("close zhadan"),buf,lstrlen(buf),NULL);
		mciSendString(TEXT("open ./sound/zhadan.wav type avivideo alias zhadan"),buf,lstrlen

			(buf),NULL);

		mciSendString(TEXT("play zhadan"),buf,lstrlen(buf),NULL);
	}

	static void playJump(TCHAR buf[128])
	{
		mciSendString(TEXT("close guanghao"),buf,lstrlen(buf),NULL);
		mciSendString(TEXT("open ./sound/jump.wav type avivideo alias guanghao"),buf,lstrlen

			(buf),NULL);

		mciSendString(TEXT("play guanghao"),buf,lstrlen(buf),NULL);
	}

	static void playXuanyun(TCHAR buf[128])
	{
		mciSendString(TEXT("close xuanyun"),buf,lstrlen(buf),NULL);
		mciSendString(TEXT("open ./sound/xuanyun.mp3 type mpegvideo alias xuanyun"),buf,lstrlen

			(buf),NULL);

		mciSendString(TEXT("play xuanyun"),buf,lstrlen(buf),NULL);
	}

};

#endif