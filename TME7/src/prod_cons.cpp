#include "Stack.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <vector>


using namespace std;
using namespace pr;

void producteur (Stack<char> * stack,char &name) {
	char c ;
	while (cin.get(c)) {
		//stack->pushWithName(name,c);
		stack->push(c);
	}
}

void consomateur (Stack<char> * stack) {
	while (true) {
		char c = stack->pop();
		cout << c << flush ;
		if (stack->isEmpty()) {cout<<endl;}
	}
}

int main () {
	void* charedmem = mmap(NULL/*adress*/ , sizeof(Stack<char>), PROT_READ|PROT_WRITE,MAP_ANONYMOUS|MAP_SHARED,-1,0);
	Stack<char> * s = new (charedmem)Stack<char>();

	pid_t pp = fork();
	if (pp==0) {
		char name = '1' ;
		producteur(s,name);
		return 0;
	}
	
	pid_t pp2= fork();
	if (pp2==0) {
		char name = '2' ;
		producteur(s,name);
		return 0;
	}

	pid_t pc = fork();
	if (pc==0) {
		consomateur(s);
		return 0;
	}

	wait(0);
	wait(0);

	munmap(charedmem, sizeof(Stack<char>));

	delete s;
	return 0;
}

