#include <iostream>
#include "Graphe.h"

int main() {

    Graphe g;

    g.chargerDepuisFichier("exemple.txt");
    g.trouverCheminLePlusCourt();

    return 0;

}