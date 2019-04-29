#include <iostream>
#include <limits>
#include <algorithm>
#include "Graphe.h"

#include <limits>

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

        algorithmeBellman();

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
                algorithmeDijkstra(0);
                break;

            case 2:
                algorithmeBellman();
                break;

            default:
                break;

        }



    }

}



/*void Graphe::algorithmeBellman(int sommetDepart) {

    vector<Arc> chemin;
    vector<int> sommetsParcourus;

    int sommetCourant = sommetDepart;

    while(sommetsParcourus.size() != sommets.size()){

        vector<pair<int, int>> poids;

        for( Arc& a : arcs ) {

            if(a.extremiteInitiale.retournerValeur() == sommetCourant && find(chemin.begin(), chemin.end(), a) == chemin.end()) {

                poids.emplace_back(a.extremiteTerminale.retournerValeur(), a.valeur);
            }
        }

        auto comparePairs = [](pair<int, int>& a, pair<int, int> & b) {
            return a.second < b.second;
        };

        pair<int, int> poidsLePlusFaible = *min_element(poids.begin(), poids.end(), comparePairs);


        chemin.push_back(*find_if(arcs.begin(), arcs.end(), [&poidsLePlusFaible, &sommetCourant](Arc& a) {
            return (a.extremiteInitiale.retournerValeur() == sommetCourant && a.extremiteTerminale.retournerValeur() == poidsLePlusFaible.first);
        }));

        sommetsParcourus.push_back(sommetCourant);
        sommetCourant = poidsLePlusFaible.first;
    }

    for(Arc a : chemin) {

        cout << a.extremiteInitiale.retournerValeur() << " -- " <<  a.valeur <<  " --> " << a.extremiteTerminale.retournerValeur() << endl;
    }

}*/

/*
void Graphe::algorithmeDijkstra(int sommetDepart) {

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

        auto & wArray = weightArray[weightArray.size() - 1];
        int min(0);
        int minIndex(0);
        bool firstValueAssigned(false);

        for(int k = 0; k < wArray.size(); k++) {

            if(!firstValueAssigned) {

                if(calculated[k]) {

                    firstValueAssigned = true;
                    min = wArray[k];
                    minIndex = k;
                }

            }

            else {

                if(wArray[k] < min) {
                    min = wArray[k];
                    minIndex = k;
                }
            }
        }

        long long int sommetLePlusFaible = minIndex;

        cout << "Sommet le plus faible : " << sommetLePlusFaible << endl;

        sommetsTraites.push_back(sommetLePlusFaible);

    }


    for(int i = 0; i < weightArray.size(); i++) {

        for(int j = 0; j < sommetsTraites.size(); j++) {

            cout << weightArray[i][j] << " ";
        }

        cout << endl;
    }


}
*/

template <typename A, typename B>
bool findPair(vector<pair<A,B>>& pairArray, pair<A,B>& pair1) {

    bool result(false);
    for_each(pairArray.begin(), pairArray.end(), [&pair1, &result](pair<A,B>& pair2) -> bool {

        if(pair1.first == pair2.first && pair1.second == pair2.second)
            result = true;
    });

    return result;

}


void Graphe::algorithmeDijkstra(int sommetDepart) {

    TableauDijsktra tableauDijsktra;
    vector<int> sommetsFixes;
    vector<pair<int, int>> retenues;

    // Initialisation

    tableauDijsktra.emplace_back();
    auto& premiereLigne = tableauDijsktra[0];

    sommetsFixes.push_back(sommetDepart);

    for( int i = 0; i < sommets.size(); i++ ) {

        premiereLigne.emplace_back();

        if(i == sommetDepart)
            continue;

        premiereLigne[i].first = std::numeric_limits<int>::max();
        premiereLigne[i].second = 0;

        for(Arc arc : arcs) {

            if(arc.extremiteInitiale.retournerValeur() == sommetDepart && arc.extremiteTerminale.retournerValeur() == i) {

                premiereLigne[i].first = arc.valeur;
                premiereLigne[i].second = sommetDepart;
            }
        }
    }


    pair<int, int> min;
    bool minInit(false);
    int minIndex(0);

    for( int k = 0; k < sommets.size(); k++ ){

        if(find(sommetsFixes.begin(), sommetsFixes.end(), k) == sommetsFixes.end()){

            if(!minInit) {
                minInit = true;
                min.first = premiereLigne[k].first;
                min.second = premiereLigne[k].second;
                minIndex = k;
            }

            else {

                if( min.first > premiereLigne[k].first ) {

                    min.first = premiereLigne[k].first;
                    min.second = premiereLigne[k].second;
                    minIndex = k;
                }
            }
        }
    }

    retenues.emplace_back(min.first, min.second);
    sommetsFixes.push_back(minIndex);

    // Boucle

    for(int j = 1; j < sommets.size(); j++) {

        tableauDijsktra.emplace_back();
        auto& derniereLigne = tableauDijsktra[tableauDijsktra.size() - 1];

        for( int i = 0; i < sommets.size(); i++ ) {

            derniereLigne.emplace_back();

            if(find(sommetsFixes.begin(), sommetsFixes.end(), i) != sommetsFixes.end())
                continue;

            int dernierSommetFixe = sommetsFixes[sommetsFixes.size() - 1];

            derniereLigne[i].first = tableauDijsktra[tableauDijsktra.size() - 2][i].first;
            derniereLigne[i].second = tableauDijsktra[tableauDijsktra.size() - 2][i].second;

            for(Arc arc : arcs) {

                if(arc.extremiteInitiale.retournerValeur() == dernierSommetFixe && arc.extremiteTerminale.retournerValeur() == i) {

                    derniereLigne[i].first = arc.valeur + retenues[retenues.size() - 1].first;
                    derniereLigne[i].second = dernierSommetFixe;
                }
            }
        }


        minInit = false;
        minIndex = 0;

        for( int k = 0; k < sommets.size(); k++ ){

            if(find(sommetsFixes.begin(), sommetsFixes.end(), k) == sommetsFixes.end()){

                if(!minInit) {
                    minInit = true;
                    min.first = derniereLigne[k].first;
                    min.second = derniereLigne[k].second;
                    minIndex = k;
                }

                else {

                    if( min.first > derniereLigne[k].first ) {

                        min.first = derniereLigne[k].first;
                        min.second = derniereLigne[k].second;
                        minIndex = k;
                    }
                }
            }
        }

        if(!findPair(retenues, min)) {
            retenues.emplace_back(min.first, min.second);
        }

        if(find(sommetsFixes.begin(), sommetsFixes.end(), minIndex) == sommetsFixes.end()) {
            sommetsFixes.push_back(minIndex);
        }

    }


    for(auto it : sommetsFixes){
        cout << it << endl;
    }

    cout << endl << endl;


    for( int i = 0; i < sommets.size(); i++ ) {

        for( int j = 0; j < sommets.size(); j++ ) {

            cout << tableauDijsktra[i][j].first << "(" << tableauDijsktra[i][j].second << ") ";
        }

        cout << endl;
    }

}


void Graphe::algorithmeBellman() {

}


