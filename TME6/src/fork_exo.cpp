#include <iostream>
#include <unistd.h>
#include "rsleep.h"
#include <sys/wait.h>

int main () {
	const int N = 3;
	int i;
	int j;
	std::cout << "main pid=" << getpid() << std::endl;
	pid_t mypid=getpid();
	
	for (i=1, j=N; i<=N && j==N && fork()==0 ; i++ ) {
		std::cout << " i:j " << i << ":" << j << std::endl;
		for (int k=1; k<=i && j==N ; k++) {
			if ( fork() == 0) {
				j=0;
				std::cout << " k:j " << k << ":" << j << std::endl;
				while (true){}
			}
		}
	}
	
	while (wait(nullptr)!=-1){
		std::cout << "je suis  " << i-1 << "  et mes fils sont morts" << std::endl;
	}

	return 0;
}
