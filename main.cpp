#include <iostream>
#include "Graphe.h"

int main() {

    Graphe g;

    g.chargerDepuisFichier("exemple.txt");
    //g.matriceDAdjacence();
    g.trouverCheminLePlusCourt();
    //g.afficher();

    return 0;

}