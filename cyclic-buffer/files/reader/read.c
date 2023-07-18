#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
 
#define BUFFER_LENGTH 256
static char receive[BUFFER_LENGTH];
 
int main() {
   int ret, fd;
   char stringToSend[BUFFER_LENGTH];
   
   fd = open("/dev/taskbuff", O_RDONLY);
   if (fd < 0){
      perror("Failed to open the device\n");
      return errno;
   }
   
   printf("Reading from the device...\n");
   
   ret = read(fd, receive, BUFFER_LENGTH);
   printf(receive);
   if (ret < 0){
      perror("Failed to read the message\n");
      return errno;
   }
   
   printf("The received message is [%s]\n", receive);
   close(fd);
   
   return 0;
}

