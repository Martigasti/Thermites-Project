#ifndef COORD_HPP
#define COORD_HPP

#include <exception>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


//1. Les coordonnées
const int tailleGrille = 25;

class Coord {
    
    public:
    
        //* Constructeur par défaut
        Coord ();
        
        //*  creer une paire de coordonnées Coord
        //*  @param[in] lig : numéro de ligne
        //*  @param[in] col : numéro de colonne
        //*  si les coordonnées ne sont pas dans la grille, leve une exception 
        //*  @return paire de type Coord initialisée
        //*       à la coordonnée (lig, col)
        Coord (int x, int y);
    
        int getLig() const { return lig; };
        int getCol() const { return col; };
    
    private : 
        int lig;
        int col;
};


std::ostream& operator<<(std::ostream& out, Coord c);

bool operator==(Coord c1, Coord c2);

bool operator!=(Coord c1, Coord c2);



//2. Direction
enum class Direction {N, NE, E, SE, S, SW, W, NW};

ostream& operator<<(ostream& out, Direction d);

Direction aGauche(Direction d);

Direction aDroite(Direction d);

//retourne la coordonnée devant une coordonnée donnée dans une direction donnée. Pour les cas où l'on est sur le bord de la grille, ne rien faire de particulier, on va laisser se propager l'exception levée par le constructeur.
Coord devantCoord(Coord c, Direction d);


#endif
