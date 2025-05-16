#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(){
	const char *filename = "test.bin";
	unsigned char data[] = {4, 5, 2, 2, 3, 3, 7, 9, 1, 5};
	unsigned char buffer[4];

	int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd == -1){
		perror("open for write");
		return 1;
	}
	write(fd, data, sizeof(data));
	close(fd);
	
	fd = open(filename, O_RDONLY);
	if(fd == -1){
		perror("open for read");
		return 1;
	}

	//move on 3 byte
	lseek(fd, 3, SEEK_SET);

	//reading 4 bytes
	ssize_t count = read(fd, buffer, 4);
	if(count == -1) {
		perror("read");
		close(fd);
		return 1;
	}

	//print the result
	printf("Read bytes: ");	
	for(int i = 0; i < count; i++){
		printf("%d ", buffer[i]);
	}
	printf("\n");
	close(fd);
	return 0;
}
	
