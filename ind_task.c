#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

int main(){
	int fd = open("fifofile", O_WRONLY | O_NONBLOCK);
	if (fd == -1){
		perror("open");
		return 1;
	}

	const char *msg = "Hello world!";
	ssize_t result = write(fd, msg, strlen(msg));
	
	if(result == -1){
		perror("write");
		printf("errno = %d (%s)\n", errno, strerror(errno));
	}

	close(fd);
	return 0;

}
