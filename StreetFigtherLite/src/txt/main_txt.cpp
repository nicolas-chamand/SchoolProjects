#include "txtJeu.h"
#include <iostream>

int main()
{
	// Choix du mode
	std::cout << "Choisissez le mode : " << std::endl;
	std::cout << "1. Un joueur" << std::endl;
	std::cout << "2. Deux joueurs" << std::endl;
	
	txtJeu JeuTXT;
	JeuTXT.txtInit();
	JeuTXT.txtBoucle();
	return 0;
}