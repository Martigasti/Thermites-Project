// -*- coding: utf-8 -*-
#include "coord.hpp"
#include "grille.hpp"
#include "termite.hpp"
#include <cstdlib>

Grille creeUneGrilledeTest(vector<Termite>& termites) {
	Grille g;
	g.placerNid(Coord(0, 0), 1);
	g.placerNid(Coord(0, tailleGrille-1), 2);
	g.placerNid(Coord(tailleGrille-1, 0), 3);
	g.placerNid(Coord(tailleGrille-1, tailleGrille-1), 4);
	int c1 = 0;
	int c2 = 0;
	int nbBrindilles = densiteBrindille * tailleGrille*tailleGrille;
	if (tailleGrille*tailleGrille <= nbTermites+nbBrindilles) {
		throw invalid_argument("Trop d'entités dans la grille");
	}
	while (c1 < nbBrindilles) {
		int r1 = rand() % tailleGrille;
		int r2 = rand() % tailleGrille;
		if (g.estVide(Coord(r1,r2))) {
			g.poseBrindille(Coord(r1,r2));
			c1++;
		}
	}
	int team = 1;
	int compt = 0;
	while (c2 < nbTermites) {
		if(compt == nbTermites/4) {
			team +=1;
			compt = 0;
		}
		int r1 = rand() % tailleGrille;
		int r2 = rand() % tailleGrille;
		if (g.estVide(Coord(r1,r2))) {
			termites.push_back(Termite(c2+1, Coord(r1, r2), team));
			g.poseTermite(Coord(r1,r2), c2+1);
			c2++;
			compt++;
		}
	}
	return g;
}



void afficheGrille(Grille g, vector<Termite> termites) {
	for (int i=0; i < tailleGrille; i++) {
		for(int j = 0; j < tailleGrille; j++) {
			int n = g.getObj(i, j);
			switch(n) {
				case 0 : cout << "   " ; break;
				case -1: {
					int b = g.getTeamBrind(Coord(i,j));
					switch(b) {
						case -1: cout << " * " ; break;
						case 1: cout << "\033[31;1m" << " * " << "\033[0m"; break;
						case 2: cout << "\033[32;1m" << " * " << "\033[0m"; break;
						case 3: cout << "\033[35;1m" << " * " << "\033[0m"; break;
						case 4: cout << "\033[34;1m" << " * " << "\033[0m"; break;
						default: throw invalid_argument("Equipe de brindille incorrect!"); break;
					} break;
				}
					
				default: {
					for (Termite t : termites) {
						if (t.getId() == n) {
							int team = t.getTeam();
							switch(team) {
								case 1: cout << "\033[31;1m" << t.toString() << "\033[0m"; break;
								case 2: cout << "\033[32;1m" << t.toString() << "\033[0m"; break;
								case 3: cout << "\033[35;1m" << t.toString() << "\033[0m"; break;
								case 4: cout << "\033[34;1m" << t.toString() << "\033[0m"; break;
								default: throw invalid_argument("Equipe de termite incorrect!"); break;
							} 
						}
					}
					break;
				}
			}
		}
	cout << endl;
	}
}

void TestCoherence(Grille g, vector<Termite> termites) {
	for (Termite t: termites) {
		if (g.numeroTermite(t.getCoord()) != t.getId()) {
			throw invalid_argument("Termite dans tableau et grille dans des differents coordonnées");
		}
	}
	for (int i = 0; i < tailleGrille; i++) {
		for (int j = 0; j < tailleGrille; j++) {
			if (g.contientTermite(Coord(i,j))) {
				Termite t = termites[g.numeroTermite(Coord(i,j)) - 1];
				if (t.getCoord() != Coord(i,j)) {
					throw invalid_argument("Termite dans tableau et grille dans des differents coordonnées");
				}
			}
		}
	}
}

bool jeufini2(vector<Termite> termites) {
	int compt = 0;
	for(Termite t: termites) {
		if (t.porteBrindille())
			compt++;
	}
	if (compt == 0) {
		return true;
	} else {
		return false;
	}
}


int main() {
    srand((unsigned) time(NULL));
	
	int tour = 1;
	vector<Termite> termites;
    Grille g = creeUneGrilledeTest(termites);
	cout << endl;
    string c;
    afficheGrille(g, termites);
    cout << "Début jeu: " << endl;
	do {
		cout << "Tour: " << tour << endl;
		for (int i = 0; i < nbTermites; i++) {
		   termites[i].vieTermite(g);
		}
		afficheGrille(g, termites);
		tour++;
		TestCoherence(g, termites);
		cout << "Appuyez sur Entrée pour continuer ou '.' pour quitter: ";
		c = getchar();
	} while (c != "." && tour <= 1000 && (not(g.jeufini()) || not(jeufini2(termites))));
	g.afficheVainqueur();

    return 0;
}


