//
//  main.c
//  test
//
//  Created by ZouSF on 15/1/19.
//  Copyright (c) 2015年 ZouSF. All rights reserved.
//

#include<stdio.h>   //使用stdin,printf(),fgets()函数
#include<stdlib.h>  //使用exit（）函数
#include<string.h>   //使用strerror().memset().strlen（）函数
#include<errno.h>   //使用errno
//#include<sys/types.h>
//#include<sys/socket.h>
//#include<netinet/in.h>
#include <unistd.h>//使用close（）函数
#include <arpa/inet.h>//使用inet_pton（）函数

#define MAXLINE 4096

int main(int argc, char** argv)
{
    int    sockfd, n;
    char    recvline[4096], sendline[4096];
    struct sockaddr_in    servaddr;//服务器
    
    if( argc != 2){
        printf("usage: ./client <ipaddress>\n");
        exit(0);
    }
    
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
        exit(0);
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(6666);//将主机字节序转换成网络字节序
    if( inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0){
        printf("inet_pton error for %s\n",argv[1]);
        exit(0);
    }
    
    if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
        printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }
    while (1) {
        printf("send msg to server: \n");
        fgets(sendline, 4096, stdin);
        if (sendline[0]=='\0') {
            break;
        }
        if( send(sockfd, sendline, strlen(sendline), 0) < 0)
        {
            printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
            exit(0);
        }
    }
    close(sockfd);
    exit(0);
}

/*
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <unistd.h>
 #include <sys/socket.h>
 #include <netinet/in.h>
 int main (void)
 {
 char IPdotdec[20]; //存放点分十进制IP地址
 struct in_addr s; // IPv4地址结构体
 // 输入IP地址
 printf("Please input IP address: ");
 scanf("%s", IPdotdec);
 // 转换
 inet_pton(AF_INET, IPdotdec, (void *)&s);
 printf("inet_pton: 0x%x\n", s.s_addr); // 注意得到的字节序
 // 反转换
 inet_ntop(AF_INET, (void *)&s, IPdotdec, 16);
 printf("inet_ntop: %s\n", IPdotdec);
 }

 */

