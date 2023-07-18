#include <stdio.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "../../kern-files/drv_ioctl.h"

int main() {
	int fd, sock, listener;
	struct sockaddr_in addr;
	char cmd[1024] = {0};
	int val;
	int bytes_read;
	
	fd = open("/dev/taskbuff", O_RDONLY);
	if(fd < 0) {
		perror("Fail\n");
		return 1;
	}

	listener = socket(AF_INET, SOCK_STREAM, 0);
	if(listener < 0) {
		perror("socket");
		return 1;
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(3425);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("bind");
		return 1;
	}

	listen(listener, 1);
	while(1) {
		sock = accept(listener, NULL, NULL);
		if(sock < 0) {
			perror("accept");
			return 1;
		}

		while(1) {
			bytes_read = recv(sock, cmd, 1024, 0);
			if(bytes_read <= 0) {
				break;
			}

			if(strcmp(cmd, "IOC_GET") == 0) ioctl(fd, IOC_GET, &val);
			else return 1;

			send(sock, &val, sizeof(val), 0);
			memset(cmd, '\0', sizeof(cmd));
		}
		close(sock);
	}

	close(listener);
	close(fd);
	return 0;
}

