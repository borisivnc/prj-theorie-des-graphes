#include <iostream>
#include "Graphe.h"
#include <fstream>

int main() {


   // std :: fstream file;

    Graphe g;



    g.chargerDepuisFichier("L3-F4-6.txt");

    g.trouverCheminLePlusCourt();

    g.afficher();

    return 0;

}