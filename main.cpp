#include <iostream>
#include "Graphe.h"
#include <fstream>

int main() {


   // std :: fstream file;

    Graphe g;



    g.chargerDepuisFichier("exemple.txt");

    g.trouverCheminLePlusCourt();

    //g.afficher();

    return 0;

}