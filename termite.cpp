// -*- coding: utf-8 -*-
#include "coord.hpp"
#include "grille.hpp"
#include "termite.hpp"


// Class Termite (à faire)

// Faire tests


Termite::Termite(int idT, Coord c) : id{idT}, coor{c} {
	brind = false; 
	compt = 0;
	int r = rand() % 8;
	dir = Direction(r);
	team = 1;
}

Termite::Termite(int idT, Coord c, int t) : id{idT}, coor{c}, team{t} {
	brind = false; 
	compt = 0;
	int r = rand() % 8;
	dir = Direction(r);
}

Termite::Termite(int idT, Direction d, Coord c) : id{idT}, dir{d}, coor{c} {
	brind = false;
	compt = 0; 
	team = 1;
}

Termite::Termite(int idT, Direction d, Coord c, int t) : id{idT}, dir{d}, coor{c}, team{t} {
	brind = false;
	compt = 0;
}



string Termite::toString() const {
	string s;
	 switch(dir) {
		case Direction::N: case Direction::S: s = " | "; break;
		case Direction::NE: case Direction::SW: s = " / "; break;
		case Direction::NW: case Direction::SE: s = " \\ "; break;
		case Direction::E: case Direction::W: s = " - "; break;
		default: throw invalid_argument("Direction incorrecte");
	}
	return s;
}


Direction Termite::directionTermite() const {
	return dir;
}
Coord Termite::devant() const {
	return devantCoord(coor, dir);
}
bool Termite::porteBrindille() const {
	return brind;
}

void Termite::tourneADroite() {
	dir = aDroite(dir);
	// cout << "droite" << endl;
}
void Termite::tourneAGauche() {
	dir = aGauche(dir);
	// cout << "gauche" << endl;
}

void Termite::tourneAleat() {
	int n = rand() % 2;
	if (n == 0) {
		tourneADroite();
		// cout << "rdroite" << endl;
	}
	else {
		tourneAGauche();
		// cout << "rgauche" << endl;
	}
}

int Termite::getCompt() const {
	return compt;
}

Coord Termite::getCoord() const {
	return coor;
}

int Termite::getId() const {
	return id;
}

int Termite::getTeam() const {
	return team;
}

bool Termite::laVoieEstLibre(Grille &g) const {
	if (g.estVide(devant())) 
		return true;
	return false;
}

bool Termite::brindilleEnFace(Grille &g) const {
	if (g.contientBrindille(devant()))
		return true;
	return false;
}

int Termite::voisinsLibre(Grille &g) {
	int c = 0;
	for (int i = 0; i < 8; i++) {
		dir = aDroite(dir);
		if (g.estVide(devant()))
			c++;
	}
	return c;
}

bool Termite::neutreBrindille(Grille &g) {
	if (g.getTeamBrind(devant()) == -1) 
		return true;
	return false;
}

bool Termite::equipeBrindille(Grille &g) {
	if (g.getTeamBrind(devant()) == team)
		return true;
	return false;
}

bool Termite::nidBrindille(Grille &g) {
	if (g.getNid(devant()))
		return true;
	return false;
}

void Termite::avance(Grille &g) {
	devant();
	// cout << "av" << endl;
	if (not(g.estVide(devant()))) 
		throw invalid_argument("La case de devant n'est pas vide!");
	if (g.dehors(devant())) {
		throw invalid_argument("La case de devant est dehors de la grille!");
	}
	g.poseTermite(devant(), id);
	g.enleveTermite(coor); 
	coor = devant();
	compt--;
	// cout << "avf" << endl;
}

void Termite::marcheAleatoire(Grille &g) {
	int r = rand() % 100;
	// cout << "m1" << endl;
	if (r < probaTourner * 100) {
		tourneAleat();
	}
	if (laVoieEstLibre(g)) {
		avance(g);
	}
}

void Termite::chargeBrindille(Grille &g) {
	if (not(g.contientBrindille(devant()))) {
		throw invalid_argument("Il n'y a pas de brindille devant la termite!");
	} else if(not(neutreBrindille(g))) {
		throw invalid_argument("La brindille de devant n'est pas neutre");
	} else if (nidBrindille(g)) {
		throw invalid_argument("La brindille est un nid!");
	}
	if (compt > 1) 
		throw invalid_argument("Le compteur est supérieur à 0!");

	// cout << "dedanschargeBrindille" << endl;
	g.enleveBrindille(devant());
	g.changeTeamBrind(devant(), 0);
	brind = true;
	compt = dureeSablier;
}

void Termite::dechargeBrindille(Grille &g) {
	if (not(brind)) 
		throw invalid_argument("La termite ne contient pas de brindille!");
	if (not(g.estVide(devant())))
		throw invalid_argument("La case de devant n'est pas vide!");
	if (compt > 1) 
		throw invalid_argument("Le compteur est supérieur à 0!");
	// if (not(equipeBrindille(g)))
	// 	throw invalid_argument("La brindille devant n'est pas du même equipe!");
	if (voisinsLibre(g) < 2)
		throw invalid_argument("Moins de 2 cases libres autour!");
	g.poseBrindille(devant());
	g.changeTeamBrind(devant(), team);
	brind = false;
	compt = dureeSablier;
}

void Termite::vieTermite(Grille &g) {
	// cout << brind << endl;
    if (not (porteBrindille())) { // cas ou le termite porte rien
        // si la case devant elle contient une brindille, elle la prend
        if (brindilleEnFace(g) && compt < 1 && neutreBrindille(g) && not(nidBrindille(g))) {
			// cout << "a" << endl;
            chargeBrindille(g);
        }
        // si la voie est libre elle avance si possible (inclus si la voie n'est pas dehors de la grille)
        else if (laVoieEstLibre(g)) {
            marcheAleatoire(g);
        }
        // sinon, elle tourne aléatoirement
        else {
            tourneAleat();
        }
    }
    else{ // cas ou le termite porte une brindille
    // si le sablier est écoulé et elle a une brindille devant, elle tourne jusqu'a pouvoir la laisser
		if (compt < 1 && brindilleEnFace(g) && equipeBrindille(g) && voisinsLibre(g) >= 2) {
			while (not(g.estVide(devant()))) {
				tourneAleat();
			}
			dechargeBrindille(g);
		} else if (laVoieEstLibre(g)){
			marcheAleatoire(g);
		} else {
			tourneAleat();
		}
	}
}

