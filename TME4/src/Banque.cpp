#include "Banque.h"

#include <iostream>

using namespace std;

namespace pr {

bool Banque::transfert(size_t deb, size_t cred, unsigned int val) {
	Compte & debiteur = comptes[deb];
	Compte & crediteur = comptes[cred];
	//cout << "solde deb avant " << debiteur.getSolde() << " credicteur " << crediteur.getSolde() << endl;
	if (debiteur.debiter(val)) {
		crediteur.crediter(val);
		//cout << "solde deb " << debiteur.getSolde() << " credicteur " << crediteur.getSolde() << endl;
		return true;
	}
	else 
		return false; 
}
size_t Banque::size() const {
	return comptes.size();
}
bool Banque::comptabiliser (int attendu) const {
	int bilan = 0;
	int id = 0;
	for (const auto & compte : comptes) {
		if (compte.getSolde() < 0) {
			cout << "Compte " << id << " en négatif de : " << compte.getSolde() << endl;
		}
		else 
			cout << "Compte " << id << " en positif de : " << compte.getSolde() << endl;
		bilan += compte.getSolde();
		id++;
	}
	if (bilan != attendu) {
		cout << "Bilan comptable faux : attendu " << attendu << " obtenu : " << bilan << endl;
	}
	return bilan == attendu;
}
}
