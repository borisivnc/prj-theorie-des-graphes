#include <iostream>
#include <limits>
#include <algorithm>
#include "Graphe.h"

using namespace std;


Sommet::Sommet() = default;
Sommet::Sommet(unsigned int _valeur) : valeur(_valeur){

}

int Sommet::retournerValeur() {
    return valeur;
}

bool Sommet::operator==(const Sommet &rhs) const {
    return valeur == rhs.valeur;
}

bool Sommet::operator!=(const Sommet &rhs) const {
    return !(rhs == *this);
}

Arc::Arc(Sommet &A, int _valeur, Sommet &B) : extremiteInitiale(A), valeur(_valeur), extremiteTerminale(B) {

}

bool Arc::operator==(const Arc &rhs) const {
    return extremiteInitiale == rhs.extremiteInitiale &&
           extremiteTerminale == rhs.extremiteTerminale &&
           valeur == rhs.valeur;
}

void Graphe::chargerDepuisFichier(std::string cheminFichier) {

    ifstream fichier(cheminFichier.c_str(), ios::in);

    if (!fichier)
        return;

    int nombreSommets;
    int nombreArcs;
    int extremiteInitiale;
    int valeur;
    int extremiteTerminale;

    fichier >> nombreSommets;
    fichier >> nombreArcs;

    unsigned int i;

    for(i = 0; i < nombreSommets; i++) {

        sommets.emplace_back( i );

    }

    for(i = 0; i < nombreArcs; i++) {

        fichier >> extremiteInitiale >> valeur >> extremiteTerminale;

        arcs.emplace_back( sommets[extremiteInitiale], valeur, sommets[extremiteTerminale] );

    }

    fichier.close();

}

void Graphe::afficher() {

    cout << "Nombre de sommets : " << sommets.size() << endl;
    cout << "Nombre d\'arcs : " << arcs.size() << endl;
    cout << endl;

    unsigned int i;

    for(i = 0; i < arcs.size(); i++) {

        cout << arcs[i].extremiteInitiale.retournerValeur() << " -- " << arcs[i].valeur << " --> " << arcs[i].extremiteTerminale.retournerValeur() << endl;

    }

}

void Graphe::trouverCheminLePlusCourt() {

    bool valeurNegative = false;

    for(auto arc : arcs) {

        if (arc.valeur < 0) {
            valeurNegative = true;
            break;
        }

    }

    int choix = 0;

    if( valeurNegative ){

        cout << "Il existe un arc avec une valeur negative dans le graphe." << endl;
        cout << "On execute donc l\'algorithme de Bellman" << endl;

        algorithmeBellman(0);

    } else {

        cout << "Pas de valeur negative dans les arcs du graphe." << endl;

        while(choix != 1 && choix != 2) {

            cout << "Quel algorithme souhaitez-vous executer ?" << endl;
            cout << "1) Algorithme de Dijsktra" << endl;
            cout << "2) Algorithme de Bellman" << endl;

            cin >> choix;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');

        }

        int ret;

        switch(choix) {

            case 1:
                algorithmeDijkstra();
                break;

            case 2:
                algorithmeBellman(0);
                break;

            default:
                break;

        }



    }

}

void Graphe::algorithmeBellman(int sommetDepart) {

    vector<int> sommetsTraites;

    unsigned long long int nbrSommets = sommets.size();

    vector<vector<int>> weightArray;
    vector<bool> calculated;

    sommetsTraites.push_back(sommetDepart);

    while(sommetsTraites.size() < nbrSommets) {

        weightArray.emplace_back();
        calculated.clear();

        for(int i = 0; i < nbrSommets; i++) {

            weightArray[weightArray.size() - 1].emplace_back(0);
            calculated.emplace_back(false);
        }

        for( int i = 0; i < nbrSommets; i++ ) {

            if(find(sommetsTraites.begin(), sommetsTraites.end(), i) == sommetsTraites.end()) {

                if(weightArray.size() == 1) {

                    for(Arc arc : arcs) {

                        if(arc.extremiteInitiale.retournerValeur() == *(sommetsTraites.end() - 1) && arc.extremiteTerminale.retournerValeur() == i) {

                            weightArray[weightArray.size() - 1][i] = arc.valeur;
                            calculated[i] = true;
                            break;
                        }
                    }
                }

                else {

                    for(Arc arc : arcs) {

                        if(arc.extremiteInitiale.retournerValeur() == *(sommetsTraites.end() - 1) && arc.extremiteTerminale.retournerValeur() == i) {

                            weightArray[weightArray.size() - 1][i] = arc.valeur + weightArray[weightArray.size() - 2][i];
                            calculated[i] = true;
                            break;
                        }
                    }

                    if(!calculated[i]) {

                        for(int j = static_cast<int>(sommetsTraites.size() - 2); j > 0 && weightArray[weightArray.size() - 1][i] == 0; j--) {

                            if(weightArray[j][i] != 0) {

                                weightArray[weightArray.size() - 1][i] = weightArray[j][i];
                                calculated[i] = true;
                                break;
                            }
                        }
                    }
                }
            }
        }

        // La ligne a ete remplie
        // Ajouter le sommet avec le poids le plus faible aux sommets traites

        int sommetLePlusFaible = []() -> int { return 0; };

    }


    for(int i = 0; i < weightArray.size(); i++) {

        for(int j = 0; j < sommetsTraites.size(); j) {

            cout << weightArray[i][j] << " ";
        }

        cout << endl;
    }


}

void Graphe::algorithmeDijkstra() {

}


