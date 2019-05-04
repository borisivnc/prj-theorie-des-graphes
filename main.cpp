#include <iostream>
#include "Graphe.h"
#include <fstream>

using namespace std;


int main() {

    Graphe g;
    string choix;

    cout <<"\t \t +----------------------------+"<<endl;
    cout <<"\t \t | Projet Theorie des Graphes |"<<endl;
    cout <<"\t \t +----------------------------+\n"<<endl;


    cout<<" Quel graphe voulez vous ?"<<endl;
    cin >> choix;
    g.chargerDepuisFichier(choix);
    g.trouverCheminLePlusCourt();
    g.afficher();

    return 0;

}