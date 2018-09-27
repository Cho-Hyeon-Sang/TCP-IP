#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/////////////////////////
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/stat.h>
/////////////////////////
#define MAXLINE 1024

int main(int argc, char *argv[])
{
	struct sockaddr_in serveraddr;
	int server_sockfd;
	int client_len;
	char buf[MAXLINE];

	if((server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("error : ");
		return 1;
	}

	// 연결 요청할 서버의 주소와 포트번호 프로토콜 등을 지정.
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveraddr.sin_port = htons(atoi(argv[1]));
	client_len = sizeof(serveraddr);

	// 서버에 연결 시도.
	if(connect(server_sockfd, (struct sockaddr *)&serveraddr, client_len) == -1)
	{
		perror("connect error : ");
		return 1;
	}

	memset(buf, 0x00, MAXLINE);
	read(0, buf, MAXLINE);
	if(write(server_sockfd, buf, MAXLINE) <= 0)
	{
		perror("write error : ");
		return 1;
	}
	memset(buf, 0x00, MAXLINE);
	if(read(server_sockfd, buf, MAXLINE) <= 0)
	{
		perror("read error : ");
		return 1;
	}
	close(server_sockfd);
	printf("read : %s\n", buf);
}
