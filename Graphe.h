#ifndef GRAPHES_PJ_GRAPHE_H
#define GRAPHES_PJ_GRAPHE_H

#include <tuple>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>


enum class Algorithme {
    Dijkstra,
    Bellman
};

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


    void chargerDepuisFichier(std::string numeroGraphe2);

    void afficher();

    void saveInFile(int sommetDepart);

    void trouverCheminLePlusCourt();


private:

    // Variables

    std::vector<Sommet> sommets;
    std::vector<Arc> arcs;
    std::vector<int> sommetsFixes;

    std::vector<std::vector<std::string>> tableauResultat;

    std::string numeroGraphe;

    Algorithme algorithmeUtilise;

    // Méthodes privées


    void algorithmeBellman(int sommetDepart);

    void algorithmeDijkstra(int sommetDepart);

    void afficherMatriceDAdjacence(std::ostream &out);
};

typedef std::vector<std::vector<std::pair<int, int>>> TableauDePaires;




#endif //GRAPHES_PJ_GRAPHE_H
