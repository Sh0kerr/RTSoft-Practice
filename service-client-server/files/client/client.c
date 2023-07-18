#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <inttypes.h>
#include "../../kern-files/drv_ioctl.h"

#define BILLION 1000000000L

int main() {
	int res;
	int sock;
	struct sockaddr_in addr;

	int num;
	printf("Number of iterations: ");
	scanf("%d", &num);

	char cmd[1024];
	printf("Command: ");
	scanf("%s", &cmd);

	uint64_t diff;
	struct timespec start, end;
	
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0) {
		perror("socket");
		return 1;
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(3425);
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("connect");
		return 1;
	}

 	for (int i = 0; i < num; i++) {
		clock_gettime(CLOCK_MONOTONIC, &start);
		send(sock, cmd, 1024, 0);
		recv(sock, &res, sizeof(int), 0);
		printf("Response: %d\n", res);
		clock_gettime(CLOCK_MONOTONIC, &end);
		diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
		diff *= 0.001;
		printf("Time: %" PRIu64 "\n", diff);
	}
	
	close(sock);
	return 0;
}

