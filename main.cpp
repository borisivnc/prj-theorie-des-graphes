#include <iostream>
#include "Graphe.h"
#include <fstream>
#include <limits>

using namespace std;


int main() {

    Graphe g;
    string choix;

    cout <<"\t \t +----------------------------+"<<endl;
    cout <<"\t \t | Projet Theorie des Graphes |"<<endl;
    cout <<"\t \t +----------------------------+\n"<<endl;

    while(choix != "2") {

        cout << "1. Choisir un graphe" << endl;
        cout << "2. Quitter"  << endl << endl;

        cin >> choix;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');

        if(choix == "1") {

            string choixGraphe;

            cout << "Quel graphe voulez vous ?" << endl;

            cin >> choixGraphe;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');

            g.chargerDepuisFichier(choixGraphe);
            g.trouverCheminLePlusCourt();
            g.afficher();
        }

        cout << endl << endl;
    }

    return 0;

}