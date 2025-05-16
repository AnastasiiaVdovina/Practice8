#include <stdio.h>

int main(){
	int pid;
	pid = fork();
	
	if(pid == -1){
		perror("fork failed");
		return 1;
	}

	printf("PID returned by fork(): %d\n", pid);
	return 0;

}

