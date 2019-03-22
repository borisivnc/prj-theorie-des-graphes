#include <iostream>
#include "Graphe.h"

int main() {

    Graphe g;

    g.chargerDepuisFichier("graphe.txt");
    //g.trouverCheminLePlusCourt();
    g.afficher();

    return 0;

}