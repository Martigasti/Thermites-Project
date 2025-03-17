// -*- coding: utf-8 -*-
#include "grille.hpp"
#include "coord.hpp"
#include "termite.hpp"

using namespace std;

Case::Case() : obj{0} {}

Case::Case(int n) : obj{n} {
	if (n < -1)
		throw invalid_argument("Entier impossible:");
}

Grille::Grille() : cases(tailleGrille, vector<Case>(tailleGrille)) {
	// Initialisation de chaque case
	for (int i = 0; i < tailleGrille; i++) {
		for (int j = 0; j < tailleGrille; j++) {
			cases[i][j].obj = 0;
			cases[i][j].brind = 0;
			cases[i][j].nid = false;
		}
	}
}





void Grille::poseBrindille(Coord c) {
	if (not(estVide(c))) 
		throw invalid_argument("Il y a déjà un objet dans la Case!");
	cases[c.getLig()][c.getCol()].obj = -1;
	cases[c.getLig()][c.getCol()].brind = -1;
}

void Grille::enleveBrindille(Coord c) {
	if (cases[c.getLig()][c.getCol()].obj != -1)
		throw invalid_argument("Il n'y a pas de brindille dans la Case!");
	cases[c.getLig()][c.getCol()].obj = 0;
	cases[c.getLig()][c.getCol()].brind = 0;
}
bool Grille::contientBrindille(Coord c) const {
	if (dehors(c)) { //si les coordonnes n'appartiennent pas a la case, ça returne false
		return false;
	} else {
		if(cases[c.getLig()][c.getCol()].obj == -1)
			return true;
		return false;
	}
}

void Grille::poseTermite(Coord c, int idT) {
	if (idT <= 0)
		throw invalid_argument("Le numéro de termite doit être supérieur à 0");
	if (not(estVide(c))) 
		throw invalid_argument("Il y a déjà un objet dans la Case!");
	cases[c.getLig()][c.getCol()].obj = idT;
}

void Grille::enleveTermite(Coord c) {
	if (estVide(c) || contientBrindille(c) ) 
		throw invalid_argument("Il n'y a pas une termite dans la Case");
	cases[c.getLig()][c.getCol()].obj = 0;
}

int Grille::numeroTermite(Coord c) const {
	if (estVide(c) || contientBrindille(c)) 
		throw invalid_argument("Il n'y a pas une termite dans la Case!");
	return cases[c.getLig()][c.getCol()].obj;
}

bool Grille::estVide(Coord c) const {
	if (dehors(c)) { //si les coordonnes n'appartiennent pas a la case, ça returne false
		return false;
	} else {
		if(cases[c.getLig()][c.getCol()].obj == 0)
			return true;
		return false;
	}
}

bool Grille::contientTermite(Coord c) const {
	if (not(estVide(c)) && not(contientBrindille(c)))
		return true;
	return false;
}

bool Grille::dehors(Coord c) const {
	if ((c.getLig() == -1 || c.getLig() == tailleGrille || c.getCol() == -1 || c.getCol() == tailleGrille))
		return true;
	return false;
}



// ostream& operator<<(ostream& out, Grille g) {
// 	string cas;
// 	for (int i=0; i < tailleGrille; i++) {
// 		for(int j = 0; j < tailleGrille; j++) {
// 			int n = g.getObj(i, j);
// 			switch(n) {
// 				case 0 : cas = "   "; break;
// 				case -1: cas = " * "; break;
// 				default: 
// 					Termite t = Termite(g.numeroTermite(Coord(i,j)), Coord(i,j), g.);
// 					cas = t.toString(); 
// 					break;
// 			}
// 			out << cas;
// 		}
// 		out << endl;
// 	}
// 	return out;
// }


//Nids
void Grille::changeTeamBrind(Coord c, int t) {
	cases[c.getLig()][c.getCol()].brind = t;
}

void Grille::placerNid(Coord c, int t) {
	cases[c.getLig()][c.getCol()].obj = -1;
	cases[c.getLig()][c.getCol()].brind = t;
	cases[c.getLig()][c.getCol()].nid = true;
}

bool Grille::jeufini() const {
	int compt = 0;
	for (int i=0; i < tailleGrille; i++) {
		for(int j = 0; j < tailleGrille; j++) {
			Coord c{i, j};
			if (contientBrindille(c)) {
				if (getTeamBrind(c) == -1)
					compt++;
			}
		}
	}
	if (compt == 0)
		return true;
	else
		return false;
}

void Grille::afficheVainqueur() const {
	int compt1 = 0;
	int compt2 = 0;
	int compt3 = 0;
	int compt4 = 0;
	for (int i=0; i < tailleGrille; i++) {
		for(int j = 0; j < tailleGrille; j++) {
			Coord c{i, j};
			if (contientBrindille(c)) {
				if (getTeamBrind(c) == 1) {
					compt1++;
				} else if (getTeamBrind(c) == 2) {
					compt2++;
				} else if (getTeamBrind(c) == 3) {
					compt3++;
				} else if (getTeamBrind(c) == 4) {
					compt4++;
				}
			}
		}
	}
	cout << "Equipe 1 a finit avec: " << compt1 << " brindilles." << endl;
	cout << "Equipe 2 a finit avec: " << compt2 << " brindilles." << endl;
	cout << "Equipe 3 a finit avec: " << compt3 << " brindilles." << endl;
	cout << "Equipe 4 a finit avec: " << compt4 << " brindilles." << endl;
}
