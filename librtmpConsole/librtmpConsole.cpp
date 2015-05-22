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
	char uri[] = "rtmp://103.240.216.205:1935/SlotMachine";  
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

	printf("hostname = %s \n",rtmp->Link.hostname.av_val);
	printf("port = %d \n",rtmp->Link.port);
	printf("protocol = %d \n",rtmp->Link.protocol);

	RTMP_EnableWrite(rtmp);   

	connectFlag=RTMP_Connect(rtmp, NULL);   
	if(connectFlag < 0)  
		printf("connnect failed...\n"); 
	else
		printf("connect success...\n");
		
	// 惠砞﹚ぃ礛穦ΤPacket Header岿粇.
	// rtmp_readpacket failed to read rtmp packet header
	rtmp->Link.playpath.av_val = "SlotMachine";
	rtmp->Link.playpath.av_len = strlen(rtmp->Link.playpath.av_val);
	rtmp->Link.sockshost.av_val = "rtmp://103.240.216.205:1935/SlotMachine";
	rtmp->Link.sockshost.av_len = strlen(rtmp->Link.sockshost.av_val);

	printf("Link.hostname = %s \n",rtmp->Link.hostname.av_val);
	printf("Link.playpath = %s \n",rtmp->Link.playpath);
	
  AVal swfHash = { 0, 0 }; 
  uint32_t swfSize = 0;  
  /*
	RTMP_SetupStream(rtmp,RTMP_PROTOCOL_RTMP,
		&rtmp->Link.hostname,
		1935,
		&rtmp->Link.sockshost,
		&rtmp->Link.playpath,
		&rtmp->Link.tcUrl,
		&rtmp->Link.swfUrl,
		&rtmp->Link.pageUrl,
		&rtmp->Link.app,
		&rtmp->Link.auth,
		&swfHash,
		swfSize,
		&rtmp->Link.flashVer,
		&rtmp->Link.subscribepath,
		0,0,false,5);
	

	*/

	streamFlag = RTMP_ConnectStream( rtmp, 0);   
	if(streamFlag < 0)  
		printf("connect stream failed...\n"); 
	else
		printf("connect stream success...\n");


                
	CleanupSockets();
	Sleep(10000);
	return 0;  
}