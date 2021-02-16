#ifndef _TXTJEU_H_
#define _TXTJEU_H_

#include "winTxt.h"
#include "Jeu.h"
#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // WIN32

class txtJeu
{
	private:
		Jeu jeu;
		WinTXT win;
		
		/**
	    * @brief Procédure d'affichage des elements graphiques de la partie.
	    */
		void txtAfficher();
		
		/**
	    * @brief Procédure d'écriture de la chaine de caractere str dans la WinTXT a partir de posX,posY.
	    */
		void ecrire(WinTXT &win, const string &str, unsigned int posX, unsigned int posY) const;
		
		/**
	    * @brief Procédure qui dessine le terrain.
	    * @details Sous-procédure de la procédure txtAfficher
	    */
		void dessineTerrain(WinTXT  &win) const;
		
		/**
	    * @brief Procédure qui dessine le Personnage psng passé en deuxième paramètre en posture coup de poing dans la fenêtre win.
	    * @details Sous-procédure de la procédure dessinePersonnage
	    */
		void animationCoupPoing(WinTXT &win, Personnage &psng) const;
		
		/**
	    * @brief Procédure qui dessine le Personnage psng passé en deuxième paramètre en posture coup de pied dans la fenêtre win.
	    * @details Sous-procédure de la procédure dessinePersonnage
	    */
		void animationCoupPied(WinTXT &win, Personnage &psng) const;
		
		/**
	    * @brief Procédure qui dessine le Personnage psng passé en deuxième paramètre en posture parade dans la fenêtre win.
	    * @details Sous-procédure de la procédure dessinePersonnage
	    */
		void animationParade(WinTXT &win, Personnage &psng) const;
		
		/**
	    * @brief Procédure qui dessine le Personnage psng passé en deuxième paramètre en posture accroupi dans la fenêtre win.
	    * @details Sous-procédure de la procédure dessinePersonnage
	    */
		void animationAccroupi(WinTXT &win, Personnage &psng) const;
		
		/**
	    * @brief Procédure qui dessine le Personnage psng passé en deuxième paramètre en posture coup de poing accroupi dans la fenêtre win.
	   	* @details Sous-procédure de la procédure dessinePersonnage
	    */
		void animationCoupPoingAccroupi(WinTXT &win, Personnage &psng) const;
		
		/**
	    * @brief Procédure qui dessine le Personnage psng passé en deuxième paramètre en posture coup de pied accroupi dans la fenêtre win.
	    * @details Sous-procédure de la procédure dessinePersonnage
	    */
		void animationCoupPiedAccroupi(WinTXT &win, Personnage &psng) const;
		
		/**
	    * @brief Procédure qui dessine le Personnage psng passé en deuxième paramètre en posture parade accroupi dans la fenêtre win.
	    * @details Sous-procédure de la procédure dessinePersonnage
	    */
		void animationParadeAccroupi(WinTXT &win, Personnage &psng) const;
		
		/**
	    * @brief Procédure qui dessine le Personnage psng passé en deuxième paramètre en posture debout dans la fenêtre win.
	    * @details Sous-procédure de la procédure dessinePersonnage
	    */
		void animationDeboutInactif(WinTXT &win, Personnage &psng) const;
		
		/**
	    * @brief Procédure qui dessine le Personnage psng passé en deuxième paramètre en posture saut dans la fenêtre win.
	    * @details Sous-procédure de la procédure dessinePersonnage
	    */
		void animationSaut(WinTXT &win, Personnage &psng) const;
		
		/**
	    * @brief Procédure qui dessine le Personnage psng passé en deuxième paramètre en posture coup special dans la fenêtre win.
	    * @details Sous-procédure de la procédure dessinePersonnage
	    */
		void animationHadoken(WinTXT &win, Personnage &psng) const;
		
		/**
	    * @brief Procédure qui dessine le Personnage psng passé en deuxième paramètre en posture vainqueur dans la fenêtre win.
	    * @details Sous-procédure de la procédure dessinePersonnage
	    */
		void animationWin(WinTXT &win, Personnage &psng) const;
		
		/**
	    * @brief Procédure qui dessine le Personnage psng passé en deuxième paramètre en posture KO dans la fenêtre win.
	    * @details Sous-procédure de la procédure dessinePersonnage
	    */
		void animationKO(WinTXT &win, Personnage &psng) const;

		/**
	    * @brief Procédure qui dessine le personnages.
	    * @details Postcondition : Le personnage passé en paramètre est dessiné.
	    * @param WinTXT &win : La fenêtre du terminal.
	    * @param Personnage const &psng : un Personnage.
	    */
		void dessinePersonnage(WinTXT &win, Personnage &psng) const;
		
		/**
	    * @brief Procédure qui dessine le HUD.
	    * @details Sous-procédure de la procédure txtAfficher
	    * @param WinTXT &win : La fenêtre du terminal.
	    */
		void dessineHUD(WinTXT &win) const;
		
		/**
	    * @brief Procédure qui dessine le Projectile projectile passé en deuxième paramètre.
	   	* @details Sous-procédure de la procédure txtAfficher
	    */
		void dessineProjectile(WinTXT &win, Projectile & projectile) const;

		/**
	    * @brief Procédure récupère les entrées claviers et effectue des actions.
	   	* @details Elle est activé en fonction du delai laissé au début et à 
	   	* la fin du round et elle prend en compte les modes 1 joueur/2 joueurs.
	   	* @param bool & ok : booléen qui permet de sortir de la boucle quand on 
	   	* souhaite quitter le jeu.
	    */
		void ecouteClavier(bool & ok);

		public:
		/**
	    * @brief Procédure qui initialise le jeu.
	    * @details Postcondition : Les personnages sont initialisés pour le mode texte.
	    */
		void txtInit();

		/**
	    * @brief Procédure de boucle d'affichage.
	    * @details Postcondition : Permet l'affichage du jeu en mode texte et l'écoute d'évenements clavier.
	    */
		void txtBoucle();
};
#endif