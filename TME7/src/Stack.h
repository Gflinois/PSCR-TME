#pragma once
#include <mutex>
#include <semaphore.h>
#include <cstring> // size_t,memset
#include <iostream>

namespace pr {

#define STACKSIZE 100

template<typename T>
class Stack {
	T tab [STACKSIZE];
	size_t sz;	
	sem_t empty_sm;
	sem_t full_sm;
	mutable std::mutex l;
public :
	Stack () : sz(0) { sem_init(&empty_sm, 1, 0);sem_init(&full_sm, 1, STACKSIZE);memset(tab,0,sizeof tab) ;}

	T pop () {
		// bloquer si vide
		sem_wait(&empty_sm);
		l.lock();
		T toret = tab[--sz];
		l.unlock();
		sem_post(&full_sm);
		return toret;
	}
	void pushWithName(T name,T elt){
		sem_wait(&full_sm);
		l.lock();
		tab[sz++] = name;
		tab[sz++] = elt;
		l.unlock();
		sem_post(&empty_sm);
		sem_post(&empty_sm);
	}
	void push(T elt) {
		//bloquer si plein
		sem_wait(&full_sm);
		l.lock();
		tab[sz++] = elt;
		l.unlock();
		sem_post(&empty_sm);
	}

	bool isEmpty(){return sz==0;}
};

}
