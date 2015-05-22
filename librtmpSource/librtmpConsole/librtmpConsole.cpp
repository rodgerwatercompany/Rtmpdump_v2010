// librtmpConsole.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <stdio.h>
#include<rtmp_sys.h>
#include<log.h>
#include<amf.h>
#pragma comment(lib,"ws2_32.lib")
int InitSockets()  
{  
#ifdef WIN32  
	WORD version;  
	WSADATA wsaData;  
	version = MAKEWORD(1, 1);  
	return (WSAStartup(version, &wsaData) == 0);  
#else  
	return TRUE;  
#endif  
}  
void CleanupSockets()  
{  
#ifdef WIN32  
	WSACleanup();  
#endif  
}  

int _tmain(int argc, _TCHAR* argv[])
{
	RTMP *rtmp; 
	int setupFlag,connectFlag,streamFlag;
	char uri[]="rtmp://192.168.100.186/live/livestream";  
	if (!InitSockets()) return -1;  
	rtmp = RTMP_Alloc();   
	if(rtmp == NULL)  
		printf("alloc failed...\n"); 
	else
		printf("alloc success...\n");

	RTMP_Init(rtmp);   
	setupFlag = RTMP_SetupURL(rtmp, (char*)uri);   
	if(setupFlag < 0)  
		printf("setup url failed...\n"); 
	else
		printf("setup url success...\n");

	RTMP_EnableWrite(rtmp);   

	connectFlag=RTMP_Connect(rtmp, NULL);   
	if(connectFlag < 0)  
		printf("connnect failed...\n"); 
	else
		printf("connect success...\n");

	streamFlag=RTMP_ConnectStream(rtmp,0);   
	if(streamFlag < 0)  
		printf("connect stream failed...\n"); 
	else
		printf("connect stream success...\n");
	CleanupSockets();
	Sleep(10000);
	return 0;  
}