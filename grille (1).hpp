#ifndef GRILLE_HPP
#define GRILLE_HPP

#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "coord.hpp"




using namespace std;

struct Case {
    //Numéro du termite ou 0 si vide ou -1 si brindille
    int obj;
	//nides
	int brind; //-1 neutre, 0 vide, 1 si team1, 2 si team2, etc... 
	bool nid;
	
	Case();
	Case(int n);
    
};

class Grille {
	public:
    // Constructeur
	Grille();

	//Méthode
	
	//Acceder à l'objet dedans la case de la Grille
	int getObj(int i, int j) const { return cases[i][j].obj; };

	

	void poseBrindille(Coord c);
	void enleveBrindille(Coord c);
	bool contientBrindille(Coord c) const;
	void poseTermite(Coord c, int idT);
	void enleveTermite(Coord c);
	int numeroTermite(Coord c) const;
	bool contientTermite(Coord c) const;
	bool estVide(Coord c) const;
	
	bool dehors(Coord c) const;

	//nids
	int getTeamBrind(Coord c) const {return cases[c.getLig()][c.getCol()].brind; };
	bool getNid(Coord c) const {return cases[c.getLig()][c.getCol()].nid; };
	
	void changeTeamBrind(Coord c, int t);
	void placerNid(Coord c, int t);
	bool jeufini() const;
	void afficheVainqueur() const;

    
	private:
		vector<vector<Case>> cases;
};

ostream& operator<<(ostream& out, Grille g);

#endif