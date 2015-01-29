//
//  server.c
//  test
//
//  Created by ZouSF on 15/1/24.
//  Copyright (c) 2015年 ZouSF. All rights reserved.
//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>//使用socket(), accept(), connect(), listen()函数
#include<sys/socket.h>//使用socket(), accept(), connect(), listen()函数
#include<netinet/in.h>//使用INADDR_ANY和struct sockaddr_in
#include <unistd.h>//使用close()函数

#define MAXLINE 4096

int main(int argc, char** argv)
{
    int    listenfd, connfd;
    struct sockaddr_in     servaddr;
    char    buff[4096];
    int     n;
    
    if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){
        printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(6666);
    
    if( bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){
        printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }
    
    if( listen(listenfd, 10) == -1){
        printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }
    
    printf("======waiting for client's request======\n");
    if( (connfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) == -1){
        printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
        //continue;
    }
    while(1){
//        if( (connfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) == -1){
//            printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
//            continue;
//        }
        n = recv(connfd, buff, MAXLINE, 0);
        buff[n] = '\0';
     	if(buff[0]!='\0'){
        printf("recv msg from client: %s\n", buff);
        }
        else{
            break;
        }
//        close(connfd);
    }
    close(connfd);

    close(listenfd);
}
