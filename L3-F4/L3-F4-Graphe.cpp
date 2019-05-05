#include <iostream>
#include <limits>
#include <algorithm>
#include "L3-F4-Graphe.h"

#include <limits>
#include <cstring>
#include <cmath>

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

void Graphe::chargerDepuisFichier(string numGraphe) {

    stringstream ss ;

    ss << "L3-F4-" << numGraphe << ".txt" ;

    size_t position_tiret = ss.str().find_last_of("-");
    size_t position_point;

    numeroGraphe = ss.str().substr(position_tiret + 1);

    position_point = numeroGraphe.find_last_of(".");

    numeroGraphe = numeroGraphe.substr(0, position_point);

    ifstream fichier(ss.str(), ios::in);

    if (!fichier) // Si le fichier n'a pas été ouvert
        return;

    sommets.clear();
    arcs.clear();
    sommetsFixes.clear();

    int nombreSommets;
    int nombreArcs;
    int extremiteInitiale;
    int valeur;
    int extremiteTerminale;

    fichier >> nombreSommets;
    fichier >> nombreArcs;

    unsigned int i;

    for(i = 0; i < nombreSommets; i++) { // On remplit la liste de sommets

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
    cout << endl << endl;

    unsigned int i;

    if(!tableauResultat.empty()) {

        std::vector<unsigned long long int> maxParColonne;

        unsigned long long int tmp(0);

        // On trouve la taille du tableau la plus grande afin d'afficher toutes les cases proportionnellement

        for(i = 0; i < tableauResultat[0].size(); i++) {

            maxParColonne.emplace_back(0);

            for (int j = 0; j < tableauResultat.size(); j++) {

                tmp = tableauResultat[j][i].size();

                if(tmp > maxParColonne[i])
                    maxParColonne[i] = tmp;
            }
        }

        // On parcourt le tableau de résultat créé par un des algorithmes

        for(unsigned int I = 0; I < tableauResultat.size() * 2; I++) {

            i = I / 2;

            if(I % 2 == 0) { // Une ligne sur deux, on affiche une ligne du tableau...

                for (int j = 0; j < tableauResultat[i].size(); j++) {

                    unsigned long long int espaces = maxParColonne[j] + 4; // Taille d'une case du tableau

                    if(j == 0)
                        cout << '+';

                    for (int k = 0; k < espaces; ++k)
                        cout << '-';

                    cout << "+";


                }

                cout << endl;

           }

            else { //... et l'autre fois on affiche le contenu de ses cases

                for(int j = 0; j < tableauResultat[i].size(); j++) {

                    // Taille d'une case du tableau à laquelle on soustrait la taille du contenu de la case :
                    // On obtient donc le nombre d'espaces à afficher autour du contenu de la case

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

        for (int j = 0; j < tableauResultat[i].size(); j++) { // Affichage de la dernière ligne du tableau

            unsigned long long int espaces = maxParColonne[j] + 4;

            if(j == 0)
                cout << '+';

            for (int k = 0; k < espaces; ++k)
                cout << '-';

            cout << "+";


        }

        cout << endl << endl;

        afficherMatriceDAdjacence(cout);
    }

}

void Graphe::saveInFile(int sommetDepart) {

    stringstream ss ;

    ss << "L3-F4-trace" << numeroGraphe << "_" << sommetDepart << ".txt" ;

    ofstream file(ss.str().c_str());

    if (file.is_open()){

        file << "Nombre de sommets : " << sommets.size() << endl;
        file << "Nombre d\'arcs : " << arcs.size() << endl;
        file << endl << endl;

        unsigned int i;

        if(!tableauResultat.empty()) {

            file << "Resultat de l\'algorithme de ";

            switch (algorithmeUtilise) {

                case Algorithme::Dijkstra:

                    file << "Dijkstra :\n";

                    break;

                case Algorithme::Bellman:

                    file << "Bellman :\n";

                    break;

            }

            file << endl;

            std::vector<unsigned long long int> maxParColonne;

            unsigned long long int tmp(0);

            // On trouve la taille du tableau la plus grande afin d'afficher toutes les cases proportionnellement

            for(i = 0; i < tableauResultat[0].size(); i++) {

                maxParColonne.emplace_back(0);

                for (int j = 0; j < tableauResultat.size(); j++) {

                    tmp = tableauResultat[j][i].size();

                    if(tmp > maxParColonne[i])
                        maxParColonne[i] = tmp;
                }
            }

            // On parcourt le tableau de résultat créé par un des algorithmes

            for(unsigned int I = 0; I < tableauResultat.size() * 2; I++) {

                i = I / 2;

                if(I % 2 == 0) { // Une ligne sur deux, on affiche une ligne du tableau...

                    for (int j = 0; j < tableauResultat[i].size(); j++) {

                        unsigned long long int espaces = maxParColonne[j] + 4; // Taille d'une case du tableau

                        if(j == 0)
                            file << '+';

                        for (int k = 0; k < espaces; ++k)
                            file << '-';

                        file << "+";


                    }

                    file << endl;

                }

                else { //... et l'autre fois on affiche le contenu de ses cases

                    for(int j = 0; j < tableauResultat[i].size(); j++) {

                        // Taille d'une case du tableau à laquelle on soustrait la taille du contenu de la case :
                        // On obtient donc le nombre d'espaces à afficher autour du contenu de la case

                        unsigned long long int espaces = maxParColonne[j] + 4 - tableauResultat[i][j].size();

                        if(j == 0)
                            file << '|';

                        if(espaces % 2 != 0) {

                            for (int k = 0; k < espaces / 2; k++) {
                                file << " ";
                            }

                            file << tableauResultat[i][j];

                            for (int k = 0; k < (espaces / 2) +1  ; k++) {
                                file << " ";
                            }



                        }

                        else {

                            for (int k = 0; k < espaces / 2; k++) {
                                file << " ";
                            }

                            file << tableauResultat[i][j];

                            for (int k = 0; k < espaces / 2  ; k++) {
                                file << " ";
                            }

                        }


                        file << '|';
                    }
                }




                if(I % 2 != 0)
                    file << endl;
            }

            for (int j = 0; j < tableauResultat[i].size(); j++) { // Affichage de la dernière ligne du tableau

                unsigned long long int espaces = maxParColonne[j] + 4;

                if(j == 0)
                    file << '+';

                for (int k = 0; k < espaces; ++k)
                    file << '-';

                file << "+";


            }

            file << endl << endl;
        }
        
        afficherMatriceDAdjacence(file);
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

        cout << "Il existe un arc avec une valeur negative dans le graphe." << endl;
        cout << "On execute donc l\'algorithme de Bellman" << endl;
        cout << "Donnez le sommet de depart"<<endl;
        cin >> leSommet;

        algorithmeBellman(leSommet);

    } else {

        cout << "Pas de valeur negative dans les arcs du graphe." << endl;

        while(choix != 1 && choix != 2) {

            cout << "Donnez le sommet de depart"<<endl;
            cin>> leSommet ;


            cout << "Quel algorithme souhaitez-vous executer ?" << endl;
            cout << "1) Algorithme de Dijsktra" << endl;
            cout << "2) Algorithme de Bellman" << endl;

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
                cout << "Erreur" << endl;
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

    TableauDePaires tableauDijsktra; // Tableau dans lequel seront effectués les calculs
    vector<pair<int, int>> retenues;

    sommetsFixes.clear();
    tableauResultat.clear();

    bool fini(false);

    algorithmeUtilise = Algorithme::Dijkstra;

    // Initialisation & remplissage de la première ligne du tableau

    tableauDijsktra.emplace_back();
    auto& premiereLigne = tableauDijsktra[0];

    sommetsFixes.push_back(sommetDepart);

    for( int i = 0; i < sommets.size(); i++ ) {

        premiereLigne.emplace_back();

        if(i == sommetDepart)
            continue;

        premiereLigne[i].first = std::numeric_limits<int>::max(); // On initialise a +inf (ici inf est la limite d'un entier)
        premiereLigne[i].second = 0;

        for(Arc arc : arcs) {

            // On initialise chaque case avec l'arc correspondant

            if(arc.extremiteInitiale.retournerValeur() == sommetDepart && arc.extremiteTerminale.retournerValeur() == i) {

                premiereLigne[i].first = arc.valeur;
                premiereLigne[i].second = sommetDepart;


            }
        }
    }


    pair<int, int> min;
    bool minInit(false);
    int minIndex(0);

    // On trouve le minimum de la ligne

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

    bool minValide(false);

    for(Arc a : arcs) {
        if(find(sommetsFixes.begin(), sommetsFixes.end(), a.extremiteInitiale.retournerValeur()) != sommetsFixes.end() &&
           a.extremiteTerminale.retournerValeur() == minIndex) {
            minValide = true;
        }
    }

    if(!minValide) {
        fini = true;
    }

    else {

        retenues.emplace_back(min.first, min.second);
        sommetsFixes.push_back(minIndex); // On ajoute le sommet correspondant au minimum aux sommets fixés
    }

    unsigned long long int nbSommetsFixes = sommetsFixes.size() - 1;

    // Boucle

    for(int j = 1; j < sommets.size() && !fini; j++) {

        tableauDijsktra.emplace_back();
        auto& derniereLigne = tableauDijsktra[tableauDijsktra.size() - 1];

        if(nbSommetsFixes == sommetsFixes.size()) { // Si l'on a pas ajouté de sommet depuis le dernier tour de boucle
            break; // alors on quitte la boucle (algorithme fini)
        }

        else {
            nbSommetsFixes = sommetsFixes.size();
        }

        for( int i = 0; i < sommets.size(); i++ ) { // Ajout et parcout des cases de la nouvelle ligne du tableau

            derniereLigne.emplace_back();

            int dernierSommetFixe = sommetsFixes[sommetsFixes.size() - 1];

            // Par défaut la nouvelle ligne prend les valeurs de la ligne précédente

            derniereLigne[i].first = tableauDijsktra[tableauDijsktra.size() - 2][i].first;
            derniereLigne[i].second = tableauDijsktra[tableauDijsktra.size() - 2][i].second;

            if(find(sommetsFixes.begin(), sommetsFixes.end(), i) != sommetsFixes.end()) // Le sommet actuel a déja été fixé on saute ce tour de boucle
                continue;


            for(Arc arc : arcs) {

                // Si l'arc part du dernier sommet fixé et va vers le sommet de la case actuelle

                if(arc.extremiteInitiale.retournerValeur() == dernierSommetFixe && arc.extremiteTerminale.retournerValeur() == i) {

                    if(j > 1) { // Si on est au moins a la ligne 2

                        if(arc.valeur + retenues[retenues.size() - 1].first < derniereLigne[i].first) { // Si la valeur est moins élevée on la garde

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

        // On trouve le minimum dans la ligne

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

        // On ajoute le minimum trouvé aux sommets fixés

        if(find(sommetsFixes.begin(), sommetsFixes.end(), minIndex) == sommetsFixes.end()) {
            sommetsFixes.push_back(minIndex);
        }

    }

    // On forme un tableau avec les résultats

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

    TableauDePaires tableauBellman;

    tableauResultat.clear();

    algorithmeUtilise = Algorithme::Bellman;

    int sommePoids(0);

    for (Arc arc : arcs) {
        sommePoids += arc.valeur;
    }

    if(sommePoids < 0) {
        cout << "Le circuit est absorbant. On n\'execute donc pas l'algorithme de Bellman." << endl;
        return;
    }

    // Initialisation

    tableauBellman.emplace_back();

    auto& premiereLigne = tableauBellman[0];

    for (int i = 0; i < sommets.size(); ++i) {

        premiereLigne.emplace_back();

        auto& paire = premiereLigne[premiereLigne.size() - 1];

        paire.first = std::numeric_limits<int>::max();
        paire.second = 0;
    }

    premiereLigne[sommetDepart].first = 0;
    premiereLigne[sommetDepart].second = 0;

    // Boucle

    for (int i = 1; i < sommets.size(); ++i) {

        tableauBellman.emplace_back();

        auto& derniereLigne = tableauBellman[tableauBellman.size() - 1];

        for (int j = 0; j < sommets.size(); ++j) {

            derniereLigne.emplace_back();

            // La nouvelle ligne prend les valeurs de la ligne précédente par défaut

            derniereLigne[j].first = tableauBellman[tableauBellman.size() - 2][j].first;
            derniereLigne[j].second = tableauBellman[tableauBellman.size() - 2][j].second;

            for(Arc arc : arcs) {

                if(arc.extremiteTerminale.retournerValeur() == j) { // Si l'arc est en direction du sommet de la case actuelle du tableau

                    // Si cet arc permet un chemin plus court vers ce sommet

                    if(tableauBellman[tableauBellman.size() - 2][arc.extremiteInitiale.retournerValeur()].first !=  std::numeric_limits<int>::max() &&
                       arc.valeur + tableauBellman[tableauBellman.size() - 2][arc.extremiteInitiale.retournerValeur()].first < derniereLigne[j].first) {

                        derniereLigne[j].first = arc.valeur + tableauBellman[tableauBellman.size() - 2][arc.extremiteInitiale.retournerValeur()].first;
                        derniereLigne[j].second = arc.extremiteInitiale.retournerValeur();
                    }
                }
            }
        }
    }

    // On forme le tableau de résultat

    tableauResultat.emplace_back();

    for (int l = 0; l < sommets.size() + 1; ++l) {
        stringstream ss;
        ss << (l - 1);
        if(l == 0)
            tableauResultat[0].emplace_back(" ");
        else
            tableauResultat[0].emplace_back(ss.str());
    }


    for( int i = 0; i < tableauBellman.size(); i++ ) {

        tableauResultat.emplace_back();

        stringstream ss;

        ss << i + 1;

        tableauResultat[i+1].emplace_back();

        tableauResultat[i+1][0] = ss.str();

        for( int j = 0; j < tableauBellman[i].size(); j++ ) {

            tableauResultat[i+1].emplace_back();

            if(tableauBellman[i][j].first == std::numeric_limits<int>::max())
                tableauResultat[i+1][j+1] = "+";

            else {

                stringstream ss;

                ss << tableauBellman[i][j].first <<"(" << tableauBellman[i][j].second << ") ";

                tableauResultat[i+1][j+1] = ss.str();

            }
        }
    }

    saveInFile(sommetDepart);
}


void Graphe::afficherMatriceDAdjacence(ostream& out) {

    int tab[sommets.size()][sommets.size()];

    out << "Matrice d\'adjacence : " << endl << endl;


    for (auto & ligne : tab)
        for(auto& col : ligne)
            col = 0;

    for(Arc arc : arcs){
        int sommetSrc = arc.extremiteInitiale.retournerValeur();
        int sommetDest = arc.extremiteTerminale.retournerValeur();
        tab[sommetSrc][sommetDest] = 1;
    }

    for (int j = 0; j <= sommets.size(); ++j) {

        if(j == 0)
            out << "+";

        out << "-----+";
    }

    out << endl;

    out << "|     |";

    for (int i = 0; i < sommets.size(); i++){
        out << "  " << i << "  |";
    }

    out << endl;

    for (int I = 0; I < sommets.size() * 2; I++){

        int i = I / 2;

        if(I % 2 == 0) {

            for (int j = 0; j <= sommets.size(); ++j) {

                if(j == 0)
                    out << "+";

                out << "-----+";
            }
        }

        else {

            int l = static_cast<int>(log10(i));

            if(l == 0 || i == 0) {
                out << "|  " << i << "  |";
            }

            else if(l == 1) {
                out << "| " << i << "  |";
            }

            for (int j = 0; j < sommets.size(); j++){

                out << "  " << tab[i][j] << "  |";
            }
        }

        out << endl;
    }

    for (int j = 0; j <= sommets.size(); ++j) {

        if(j == 0)
            out << "+";

        out << "-----+";
    }

    out << endl;
}



