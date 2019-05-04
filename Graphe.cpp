#include <iostream>
#include <limits>
#include <algorithm>
#include "Graphe.h"

#include <limits>
#include <cstring>

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

void Graphe::chargerDepuisFichier(string numeroGraphe2) {

    stringstream ss ;

    ss << "L3-F4-" << numeroGraphe2 << ".txt" ;

    numeroGraphe = numeroGraphe2 ;

    size_t found = ss.str().find_last_of("-");
    numeroGraphe = ss.str().substr(found+1);
    size_t found2 = numeroGraphe.find_last_of(".");
    numeroGraphe = numeroGraphe.substr(0,found2);


    ifstream fichier(ss.str(), ios::in);

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

    cout << endl << endl;

    if(!tableauResultat.empty()) {

        std::vector<unsigned long long int> maxParColonne;

        unsigned long long int tmp(0);

        for(i = 0; i < tableauResultat[0].size(); i++) {

            maxParColonne.emplace_back(0);

            for (int j = 0; j < tableauResultat.size(); j++) {

                tmp = tableauResultat[j][i].size();

                if(tmp > maxParColonne[i])
                    maxParColonne[i] = tmp;
            }
        }

        for(unsigned int I = 0; I < tableauResultat.size() * 2; I++) {

            i = I / 2;

            if(I % 2 == 0) {

                for (int j = 0; j < tableauResultat[i].size(); j++) {

                    unsigned long long int espaces = maxParColonne[j] + 4;

                    if(j == 0)
                        cout << '+';

                    for (int k = 0; k < espaces; ++k)
                        cout << '-';

                    cout << "+";


                }

                cout << endl;

           }

            else {

                for(int j = 0; j < tableauResultat[i].size(); j++) {

                    unsigned long long int espaces = maxParColonne[j] + 4 - tableauResultat[i][j].size();

                    if(j == 0)
                        cout << '|';

                    if(espaces % 2 != 0) {

                        for (int k = 0; k < espaces / 2; k++) {
                            cout << " ";
                        }

                        cout << tableauResultat[i][j];

                        for (int k = 0; k < (espaces / 2) +1  ; k++) {
                            cout << " ";
                        }



                    }

                    else {

                        for (int k = 0; k < espaces / 2; k++) {
                            cout << " ";
                        }

                        cout << tableauResultat[i][j];

                        for (int k = 0; k < espaces / 2  ; k++) {
                                cout << " ";
                            }

                    }


                    cout << '|';
                }
            }




            if(I % 2 != 0)
                cout << endl;
        }

        for (int j = 0; j < tableauResultat[i].size(); j++) {

            unsigned long long int espaces = maxParColonne[j] + 4;

            if(j == 0)
                cout << '+';

            for (int k = 0; k < espaces; ++k)
                cout << '-';

            cout << "+";


        }

        cout << endl;
    }

}

void Graphe::saveInFile(int sommetDepart ) {

    stringstream ss ;

    ss << "L3-F4-trace"<< numeroGraphe <<"_"<< sommetDepart <<".txt" ;

    ofstream myfile(ss.str().c_str());

    if (myfile.is_open()){


        unsigned int i;

    for (i = 0; i < arcs.size(); i++) {

        myfile  << arcs[i].extremiteInitiale.retournerValeur() << " -- " << arcs[i].valeur << " --> "
             << arcs[i].extremiteTerminale.retournerValeur() << endl;

    }

        myfile  << endl << endl;

    if (!tableauResultat.empty()) {

        std::vector<unsigned long long int> maxParColonne;

        unsigned long long int tmp(0);

        for (i = 0; i < tableauResultat[0].size(); i++) {

            maxParColonne.emplace_back(0);

            for (int j = 0; j < tableauResultat.size(); j++) {

                tmp = tableauResultat[j][i].size();

                if (tmp > maxParColonne[i])
                    maxParColonne[i] = tmp;
            }
        }

        for (unsigned int I = 0; I < tableauResultat.size() * 2; I++) {

            i = I / 2;

            if (I % 2 == 0) {

//                for (int j = 0; j < tableauResultat[i].size(); j++) {
//
//                    unsigned long long int espaces = maxParColonne[j] + 2;
//
//                    if(j == 0)
//                        cout << '+';
//
//                    for (int k = 0; k < espaces; ++k)
//                        cout << '-';
//
//                    cout << '+';
//
//                }

            } else {

                for (int j = 0; j < tableauResultat[i].size(); j++) {

                    unsigned long long int espaces = maxParColonne[j] + 2 - tableauResultat[i][j].size();

                    if (j == 0)
                        myfile  << '|';

                    if (tableauResultat[i][j].size() % 2 != 0) {

                        for (int k = 0; k < espaces / 2; ++k) {
                            myfile  << " ";
                        }

                        myfile  << tableauResultat[i][j];

                        for (int k = 0; k < (espaces / 2) + 1; ++k) {
                            myfile  << " ";
                        }


                    } else {

                        for (int k = 0; k < espaces / 2; ++k) {
                            myfile  << " ";
                        }

                        myfile  << tableauResultat[i][j];

                        for (int k = 0; k < espaces / 2; ++k) {
                            myfile  << " ";
                        }
                    }


                    myfile  << '|';
                }
            }


            if (I % 2 != 0)
                myfile  << endl;
        }
    }
    }
    else
        cout << "Unable to open file";

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
    int leSommet = 0;

    if( valeurNegative ){

        cout << " Il existe un arc avec une valeur negative dans le graphe." << endl;
        cout << " Algorithme de Djisktra non applicable car circuit absorbant." << endl;
        cout << " On execute donc l\'algorithme de Bellman" << endl;
        cout << " Donnez le sommet de départ"<<endl;
        cin >> leSommet;

        algorithmeBellman(leSommet);

    } else {

        cout << " Pas de valeur negative dans les arcs du graphe." << endl;

        while(choix != 1 && choix != 2) {

            cout << " Donnez le sommet de depart"<<endl;
            cin>> leSommet ;


            cout << " Quel algorithme souhaitez-vous executer ?" << endl;
            cout << " 1) Algorithme de Dijsktra" << endl;
            cout << " 2) Algorithme de Bellman" << endl;

            cin >> choix;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');

        }

        int ret;

        switch(choix) {

            case 1:

                algorithmeDijkstra(leSommet);
                break;

            case 2:

                algorithmeBellman(leSommet);
                break;

            default:
                cout << " Erreur" <<endl;
                break;

        }



    }

}


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
    vector<pair<int, int>> retenues;

    sommetsFixes.clear();
    tableauResultat.clear();

    bool fini(false);

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

    unsigned long long int nbSommetsFixes = sommetsFixes.size() - 1;

    // Boucle

    for(int j = 1; j < sommets.size() && !fini; j++) {

        tableauDijsktra.emplace_back();
        auto& derniereLigne = tableauDijsktra[tableauDijsktra.size() - 1];

        if(nbSommetsFixes == sommetsFixes.size()) {
            break;
        }

        else {
            nbSommetsFixes = sommetsFixes.size();
        }

        for( int i = 0; i < sommets.size(); i++ ) {

            derniereLigne.emplace_back();


            int dernierSommetFixe = sommetsFixes[sommetsFixes.size() - 1];

            derniereLigne[i].first = tableauDijsktra[tableauDijsktra.size() - 2][i].first;
            derniereLigne[i].second = tableauDijsktra[tableauDijsktra.size() - 2][i].second;

            if(find(sommetsFixes.begin(), sommetsFixes.end(), i) != sommetsFixes.end())
                continue;


            for(Arc arc : arcs) {

                if(arc.extremiteInitiale.retournerValeur() == dernierSommetFixe && arc.extremiteTerminale.retournerValeur() == i) {

                    if(j > 1) {

                        if(arc.valeur + retenues[retenues.size() - 1].first < derniereLigne[i].first) {

                            derniereLigne[i].first = arc.valeur + retenues[retenues.size() - 1].first;
                            derniereLigne[i].second = dernierSommetFixe;
                        }
                    }

                    else {

                        derniereLigne[i].first = arc.valeur + retenues[retenues.size() - 1].first;
                        derniereLigne[i].second = dernierSommetFixe;
                    }

                }
            }

        }

        minInit = false;
        minIndex = 0;

        for( int k = 0; k < sommets.size(); k++ ){

            if(find(sommetsFixes.begin(), sommetsFixes.end(), k) == sommetsFixes.end() /*&& derniereLigne[k].second == sommetsFixes[sommetsFixes.size() - 1]*/){

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

        bool minValide(false);

        for(Arc a : arcs) {
            if(find(sommetsFixes.begin(), sommetsFixes.end(), a.extremiteInitiale.retournerValeur()) != sommetsFixes.end() &&
               a.extremiteTerminale.retournerValeur() == minIndex) {
                minValide = true;
            }
        }

        if(!minValide) {
            break;
        }

        if(!findPair(retenues, min)) {
            retenues.emplace_back(min.first, min.second);
        }

        if(find(sommetsFixes.begin(), sommetsFixes.end(), minIndex) == sommetsFixes.end()) {
            sommetsFixes.push_back(minIndex);
        }

    }

    tableauResultat.emplace_back();

    for (int l = 0; l < sommets.size() + 1; ++l) {
        stringstream ss;
        ss << (l - 1);
        if(l == 0)
            tableauResultat[0].emplace_back(" ");
        else
            tableauResultat[0].emplace_back(ss.str());
    }


    for( int i = 0; i < tableauDijsktra.size(); i++ ) {

        tableauResultat.emplace_back();

        stringstream ss;

        for (int k = 0; k <= i; ++k) {
            ss << sommetsFixes[k];
        }

        tableauResultat[i+1].emplace_back();

        tableauResultat[i+1][0] = ss.str();

        for( int j = 0; j < tableauDijsktra[i].size(); j++ ) {

            tableauResultat[i+1].emplace_back();

            if(tableauDijsktra[i][j].first == std::numeric_limits<int>::max())
                tableauResultat[i+1][j+1] = "+";


            else {

                if (i> 0 && tableauDijsktra[i][j].first == 0) {

                    tableauDijsktra[i][j].first = tableauDijsktra[i-1][j].first ;
                    tableauDijsktra[i][j].second = tableauDijsktra[i-1][j].second ;
                }

                if (i >= 2 &&
                    tableauDijsktra[i][j].first == tableauDijsktra[i - 1][j].first && tableauDijsktra[i][j].second == tableauDijsktra[i - 1][j].second &&
                    tableauDijsktra[i - 1][j].first == tableauDijsktra[i - 2][j].first && tableauDijsktra[i - 1][j].second == tableauDijsktra[i - 2][j].second)
                    tableauResultat[i+1][j+1] = "=";


                else {

                    stringstream ss;

                    ss << tableauDijsktra[i][j].first <<"(" << tableauDijsktra[i][j].second << ") ";

                    tableauResultat[i+1][j+1] = ss.str();
                }
            }
        }
    }

    saveInFile(sommetDepart);
}


void Graphe::algorithmeBellman(int sommetDepart) {

}




