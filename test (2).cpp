// -*- coding: utf-8 -*-
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "coord.hpp"
#include "grille.hpp"
#include "termite.hpp"

TEST_CASE("Test coord") {
    Coord a = {3,4};
    Coord b = {3,4}; // ici j'utilise des parentheses pour verifier le fonctionnement de mon constructeur
    CHECK(a == b);
    Coord c = {1,4};
    Coord d = {3,19};
    CHECK_FALSE(a == c);
    CHECK_FALSE(b == d);
    CHECK_THROWS_AS(Coord  bug1(3,tailleGrille+1), invalid_argument);
    CHECK_THROWS_AS(Coord bug2(tailleGrille+1,14), invalid_argument);
}


TEST_CASE("Test aGauche/aDroite") {
    CHECK(aGauche(Direction::N) == Direction::NW);
    CHECK(aDroite(Direction::N) == Direction::NE);
    CHECK(aDroite(aGauche(Direction::N)) == Direction::N);
    CHECK(aGauche(aDroite(Direction::N)) == Direction::N);
    Direction d = Direction::N;
    for (int i = 0; i < 8; i++) {
        d = aGauche(d);
    }
    CHECK(d == Direction::N);
    
    d = Direction::S;
    for (int i = 0; i < 8; i++) {
        d = aDroite(d);
    }
    CHECK(d == Direction::S);
}

TEST_CASE("Test devantCoord") {
	CHECK(devantCoord(Coord(2,4), Direction::N) == Coord(1,4));
	CHECK(devantCoord(Coord(0,0), Direction::SE) == Coord(1,1));
	CHECK(devantCoord(Coord(14,12), Direction::W) == Coord(14,11));
	CHECK_THROWS_AS(devantCoord(Coord(-1,-1), Direction::N), invalid_argument);
	CHECK_THROWS_AS(devantCoord(Coord(tailleGrille,13), Direction::S), invalid_argument);
	CHECK_THROWS_AS(devantCoord(Coord(0,tailleGrille), Direction::NE), invalid_argument);
	//Question 21.
	Coord c = {5,5};
	Direction d = Direction::N;
	c = devantCoord(c, d);
	for(int i = 0; i < 4; i++) {
		d = aDroite(d);
	}
	CHECK(devantCoord(c, d) == Coord(5,5));
}

TEST_CASE("Test Dehors") {
	Grille g = Grille();
	CHECK(g.dehors(Coord(tailleGrille, 0)));
	CHECK(g.dehors(Coord(-1, 0)));
	CHECK(g.dehors(Coord(-1, 5)));
	CHECK(g.dehors(Coord(5, -1)));
	CHECK(g.dehors(Coord(0, tailleGrille)));
	CHECK_FALSE(g.dehors(Coord(0,19)));
	CHECK_FALSE(g.dehors(Coord(19,0)));
}

TEST_CASE("Test Brindilles") {
	Grille g = Grille();
	g.poseBrindille(Coord(0,0));
	g.poseBrindille(Coord(1,0));
	CHECK(g.contientBrindille(Coord(0,0)));
	g.enleveBrindille(Coord(0,0));
	CHECK_FALSE(g.contientBrindille(Coord(0,0)));
	CHECK_THROWS_AS(g.enleveBrindille(Coord(0,0)), invalid_argument);
	CHECK_THROWS_AS(g.poseBrindille(Coord(1,0)), invalid_argument);
}

TEST_CASE("Test Termites") {
	Grille g = Grille();
	g.poseTermite(Coord(0,0), 1);
	g.poseTermite(Coord(1,0), 2);
	CHECK(g.contientTermite(Coord(0,0)));
	CHECK(g.contientTermite(Coord(1,0)));
	CHECK_FALSE(g.contientTermite(Coord(2,0)));
	CHECK_FALSE(g.estVide(Coord(1,0)));
	CHECK_THROWS_AS(g.enleveTermite(Coord(0,2)), invalid_argument);
	g.enleveTermite(Coord(0,0));
	CHECK(g.estVide(Coord(0,0)));
	CHECK(g.numeroTermite(Coord(1,0)) == 2);
	CHECK_THROWS_AS(g.poseTermite(Coord(0,3), 0), invalid_argument);
	CHECK_THROWS_AS(g.numeroTermite(Coord(0,0)), invalid_argument);
}

TEST_CASE("Test Comportement Termites") {
	Grille g = Grille();
	// Ajout d'une brindille pour tester porteBrindille() à true
	g.poseBrindille(Coord(0, 0));
    Termite t = Termite(1, Coord(1,0));
	g.poseTermite(t.getCoord(), t.getId());
	CHECK(g.numeroTermite(Coord(1,0)) == 1);
	CHECK(t.getCompt() == 0);
	while(t.devant() != Coord(0,0))
		t.tourneAGauche();
	CHECK(t.brindilleEnFace(g));
	t.chargeBrindille(g);
	CHECK(t.porteBrindille());
	CHECK(t.getCompt() == 6);
	t.tourneADroite();
	t.tourneADroite();
	CHECK(t.devant() == Coord(1,1));
	CHECK(t.laVoieEstLibre(g));
	CHECK_THROWS_AS(t.dechargeBrindille(g), invalid_argument);
	for (int i = 0; i < 6; i++) {
		t.avance(g);
	}
	CHECK(t.getCoord() == Coord(1, 6));
	t.dechargeBrindille(g);
	CHECK_FALSE(t.porteBrindille());
	CHECK(t.brindilleEnFace(g));
	CHECK(t.voisinsLibre(g) == 7);
	// Test de la fonction directionTermite()
	Termite t2 = Termite(2, Coord(2,0));
	while (t2.devant() != Coord(1,0))
		t2.tourneAGauche();
	CHECK(t2.directionTermite() == Direction::N);
	// // Test de la fonction devant()
	Termite t3 = Termite(3, Coord(3,0));
	while(t3.directionTermite() != Direction::N)
		t3.tourneADroite();
	CHECK(t3.devant() == Coord(2,0));
	// // Test de la fonction porteBrindille()
	Termite t4 = Termite(4, Coord(2,0));
	CHECK_FALSE(t4.porteBrindille());
}

TEST_CASE("Tests vector/grille ") { 
	vector <Termite> termites = {Termite(1, Direction::SE, Coord(0,0)), Termite(2, Direction::N, Coord(2,2))};
	Grille g;
	Coord c1{0,0};
	Coord c2{2,2};
	g.poseTermite(c1, 1);
	g.poseTermite(c2, 2);
	for (size_t i = 0; i < termites.size(); i++) {
		termites[i].avance(g);
	}
	CHECK(g.numeroTermite(Coord(1,1)) != 0);
	CHECK(termites[0].getCoord() == Coord(1,1));
	CHECK(g.numeroTermite(Coord(1,2)) != 0);
	CHECK(termites[1].getCoord() == Coord(1,2));
	
	g.poseBrindille(Coord(2,2));
	g.poseBrindille(Coord(0,2));
	termites[0].chargeBrindille(g);
	CHECK(termites[0].porteBrindille());
	CHECK_FALSE(g.contientBrindille(Coord(2,2)));
	for (int i = 0; i < 6; i++) {
		termites[0].avance(g);
	}
	termites[0].dechargeBrindille(g);
	CHECK(g.numeroTermite(Coord(7,7)) != 0);
	CHECK(termites[0].getCoord() == Coord(7,7));
	CHECK(g.contientBrindille(Coord(8,8)));
	CHECK_FALSE(termites[0].porteBrindille());
	for (int i = 0; i < 10; i++) {
		termites[0].vieTermite(g);
		CHECK(g.numeroTermite(termites[0].getCoord()) != 0);
	}
		
}

TEST_CASE("Tests Nids") {
	Grille g;
	g.placerNid(Coord(1,1), 1);
	g.poseTermite(Coord(2,2), 1);
	Termite t = Termite(1, Direction::SE, Coord(2,2), 1);
	Termite t2 = Termite(2, Direction::S, Coord(0,1), 2);
	Termite t3 = Termite(3, Direction::SE, Coord(0,0), 1);
	CHECK_THROWS_AS(t3.chargeBrindille(g), invalid_argument);
	g.poseBrindille(Coord(3,3));
	t.chargeBrindille(g);
	CHECK(t.porteBrindille());
	//On fait que la termite avance pour reduire son compteur
	for (int i = 0; i < 4; i++) {
		t.avance(g);
	}
	for (int i = 0; i < 4; i++) {
		t.tourneADroite();
	}
	CHECK(t.directionTermite() == Direction::NW);
	for (int i = 0; i < 3; i++) {
		t.avance(g);
	}
	//On est a nouveau face a la brindille
	t.dechargeBrindille(g);
	CHECK_FALSE(t.porteBrindille());
	CHECK_THROWS_AS(t2.chargeBrindille(g), invalid_argument);
	
}

int main(int argc, const char **argv) {
  doctest::Context context(argc, argv);
  int test_result = context.run();
  if (context.shouldExit()) return test_result;
      
  Coord t = {1,2}; 
  cout << "On affiche les coordonnées (1,2): " << t;
  Direction d = Direction::N;
  cout << "On affiche la Direction Nord : " << d <<endl;


  return 0;
}
