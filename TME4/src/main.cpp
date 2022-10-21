#include "Banque.h"
#include <iostream>

using namespace std;
bool gg (pr::Banque &banque){
	for (int c =1 ; c<=1000;c++){
		size_t i = rand() %10;
		size_t j = rand() %10;
		unsigned int m = rand() % 100+1 ;
		banque.transfert(i,j,m);
		this_thread::sleep_for (chrono::milliseconds(rand()%20));
		
	}
	return 1;
}
const int NB_THREAD = 10;
int main () {
	pr::Banque SOGE (10,10000);
	vector<thread> threads;
	for (int i=0;i<=NB_THREAD;i++) {
		threads.emplace_back(gg,ref(SOGE));
	}

	for (auto & t : threads) {
		t.join();
	}
	bool comptaOk = SOGE.comptabiliser(10000*10);
	if (comptaOk)
		cout<<"Bilan comptable  juste" << endl;


	// TODO : tester solde = NB_THREAD * JP
	return 0;
}
