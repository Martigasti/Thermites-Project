// -*- coding: utf-8 -*-
#include "coord.hpp"

using namespace std;

//1. Les coordonnées
Coord::Coord() : lig {} {}

Coord::Coord(int x, int y) {
    if ((x>tailleGrille) or (y>tailleGrille) or (x<-1) or (y<-1)) {
        throw invalid_argument("Les coordonnees ne sont pas dans la grille");
    }
    lig=x;
    col=y;
}


ostream& operator<<(ostream& out, Coord c) {
    out << "(" << c.getLig() << "," << c.getCol() << ")" << endl;
    return out;
}

bool operator==(Coord c1, Coord c2) {
    if ((c1.getLig() != c2.getLig()) or (c1.getCol() != c2.getCol())) {
        return false;
    }
    return true;
}

bool operator!=(Coord c1, Coord c2) {
	if (c1 == c2)
		return false;
	return true;
}


//2. Direction
ostream& operator<<(ostream& out, Direction d) {
    string res;
    switch (d) {
        case Direction::N: res = "Nord"; break;
        case Direction::NE : res = "Nord-Est"; break;
        case Direction::E: res = "Est"; break;
        case Direction::SE: res = "Sud-Est"; break;
        case Direction::S: res = "Sud"; break;
        case Direction::SW: res = "Sud-Ouest"; break;
        case Direction::W: res = "Ouest"; break;
        case Direction::NW: res = "Nord-Ouest"; break;
        default: res = "direction invalide";
    }
    out << res;
    return out;
}



Direction aGauche(Direction d) {
    Direction res;
    switch(d) {
        case Direction::N: res = Direction::NW; break;
        case Direction::NE: res = Direction::N; break;
        case Direction::E: res = Direction::NE; break;
        case Direction::SE: res = Direction::E; break;
        case Direction::S: res = Direction::SE; break;
        case Direction::SW: res = Direction::S; break;
        case Direction::W: res = Direction::SW; break;
        case Direction::NW: res = Direction::W; break;
        default: throw invalid_argument("Direction incorrecte");
    }
    return res;
}

Direction aDroite(Direction d) {
    Direction res;
    switch(d) {
        case Direction::N: res = Direction::NE; break;
        case Direction::NE: res = Direction::E; break;
        case Direction::E: res = Direction::SE; break;
        case Direction::SE: res = Direction::S; break;
        case Direction::S: res = Direction::SW; break;
        case Direction::SW: res = Direction::W; break;
        case Direction::W: res = Direction::NW; break;
        case Direction::NW: res = Direction::N; break;
        default: throw invalid_argument("Direction incorrecte");;
    }
    return res;
}

Coord devantCoord(Coord c, Direction d) {
    int x = c.getLig();
    int y = c.getCol();
    switch(d) {
        case Direction::N: x--; break;
        case Direction::NE: x--; y++; break;
        case Direction::E: y++; break;
        case Direction::SE: x++; y++; break;
        case Direction::S: x++; break;
        case Direction::SW: x++; y--; break;
        case Direction::W: y--; break;
        case Direction::NW: x--; y--; break;
        default: throw invalid_argument("Direction incorrecte");
    }
    return Coord(x,y);
}
