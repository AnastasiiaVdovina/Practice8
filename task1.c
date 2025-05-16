#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

int main(){
	int pipefd[2]; //pipe[0] - for reading, pipe[1] - writing
	char buffer[4096]; //4kb
	memset(buffer, 'A', sizeof(buffer));

	if(pipe(pipefd) == -1){
		perror("pipe");
		return 1;

	}

	//making the write descriptor non-blocking
	int flags = fcntl(pipefd[1], F_GETFL);
	fcntl(pipefd[1], F_SETFL, flags | O_NONBLOCK);
		

	// i`m going to write smth in pipe, but without reading
	int total_written = 0;	
	while(1){
		ssize_t count = write(pipefd[1], buffer, sizeof(buffer));
		if(count == -1){
			if(errno == EAGAIN){
				printf("Pipe buffer full - write would block\n");
				break;

			}else{
				perror("write");
				break;
			}

		}
		
				
		if (count < sizeof(buffer)){
			printf("Partial write: %zd bytes instead of %zu\n",count, sizeof(buffer));
			break;
		}	

		total_written += count;
		printf("%d bytes was written\n", total_written);
	
	}

	return 0;

}
