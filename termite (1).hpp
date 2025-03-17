#ifndef TERMITE_HPP
#define TERMITE_HPP

#include "coord.hpp"
#include "grille.hpp"

using namespace std;

const float probaTourner = 0.1; // 10%
const int dureeSablier = 6;
const float densiteBrindille=0.1;
const int nbTermites=40;

class Termite {
	public:
		//Constructeurs
		Termite();
		Termite(int idT, Coord c);
		Termite(int idT, Coord c, int team);
		Termite(int idT, Direction d, Coord c);
		Termite(int idT, Direction d, Coord c, int team);
	
		//Méthodes
		
			//Accès
		string toString() const;
		Direction directionTermite() const;
		Coord devant() const;
	
		int getCompt() const;
		Coord getCoord() const;
		int getId() const;
	
			//Prédicats
		bool porteBrindille() const;
	
				//renvoie si la case devant le termite est libre
		bool laVoieEstLibre(Grille &g) const;
	
				//renvoie si la case devant le termite contient une brindille
		bool brindilleEnFace(Grille &g) const;

	
				//renvoie le nombre de cases libre autour du termite
		int voisinsLibre(Grille &g);
	
			//Modification
		void tourneADroite();
		void tourneAGauche();
		void tourneAleat();

				//avance le termite
		void avance(Grille &g);
	
				//déplace aléatoirement le termite
		void marcheAleatoire(Grille &g);
	
				//le termite prend une brindille
		void chargeBrindille(Grille &g);
	
				//le termite pose une brindille
		void dechargeBrindille(Grille &g);
	
				//algorithme du termite
		void vieTermite(Grille &g);
	
		//Nids
		int getTeam() const;
		bool neutreBrindille(Grille &g);
		bool equipeBrindille(Grille &g);
		bool nidBrindille(Grille &g);



	
	private:
		int id;
		Direction dir;
		Coord coor;
		bool brind;
		int compt;
		int team;
};


#endif