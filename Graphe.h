#ifndef GRAPHES_PJ_GRAPHE_H
#define GRAPHES_PJ_GRAPHE_H

#include <tuple>
#include <vector>
#include <string>
#include <fstream>

class Sommet {

public:

    Sommet();
    Sommet(unsigned int _valeur);
    ~Sommet() = default;

    int retournerValeur();

    bool operator==(const Sommet &rhs) const;

    bool operator!=(const Sommet &rhs) const;


private:

    unsigned int valeur;

};

struct Arc {

    Arc( Sommet& A, int _valeur, Sommet& B );

    Sommet& extremiteInitiale;
    Sommet& extremiteTerminale;

    int valeur;

    bool operator==(const Arc &rhs) const;

};

class Graphe {

public:

    Graphe() = default;
    ~Graphe() = default;


    void chargerDepuisFichier(std::string cheminFichier);

    void afficher();

    void trouverCheminLePlusCourt();


private:

    // Variables

    std::vector<Sommet> sommets;
    std::vector<Arc> arcs;

    // Méthodes privées

    void algorithmeDijkstra();
    void algorithmeBellman();

    void algorithmeDijkstra(int sommetDepart, int sommetArrivee);

    void algorithmeBellman(int sommetDepart);

    void algorithmeDijkstra(int sommetDepart);


};

typedef std::vector<std::vector<std::pair<int, int>>> TableauDijsktra;


#endif //GRAPHES_PJ_GRAPHE_H
