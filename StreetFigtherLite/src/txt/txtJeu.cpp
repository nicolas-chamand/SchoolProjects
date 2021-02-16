
#include "txtJeu.h"
#include <iostream>

void txtJeu::txtInit()
{
  // Initialisation de l'environnement
  // (DIMX, DIMY, hauteurSol, epaisseurBordure, gravite, saut, vitesse, delai);
  #ifdef _WIN32
    jeu.initEnvironnement(45, 15, 14, 0, 1.5, -3.0, 1.0, 5.0);
  #else
    jeu.initEnvironnement(45, 15, 14, 0, 1.5, -3.0, 1.0, 0.05);
  #endif // WIN32
 
  //Initialisation des personnages
  jeu.joueur1.init(2, 2, 2, 3, make_vec2(15, jeu.env.hauteurSol));
  jeu.joueur2.init(2, 2, 2, 3, make_vec2(30, jeu.env.hauteurSol));

  //Initialisation des projectiles
  jeu.joueur1.projectile.init(1);
  jeu.joueur2.projectile.init(1);

  //Initilise le clock de delai pour affichage du round
  jeu.delayDebut = clock();

  int choix;
  std::cin >> choix;
  while(!(choix>0 && choix<3))
  {
    std::cout << "Erreur : entrez un nombre entre 1 et 2." << std::endl;
    std::cin.clear(); // Supprime l'état de fail du cin
    std::cin.ignore();
    std::cin >> choix;
  }

  if(choix == 1)
    jeu.mode = true;
  else if(choix == 2)
    jeu.mode = false;
}

void txtJeu::ecouteClavier(bool & ok)
{
  // recupere la premiere entree clavier
  int c = win.getCh();

  // Si le round à commencer
  if(!jeu.debut)
  {
    switch (c) 
    {
      // Joueur 1
      case 'q': // deplacement a gauche
        jeu.actionClavier('w');
        break;
      case 'd': // deplacement a droite
        jeu.actionClavier('d');
        break;
      case 'z': // saut
        jeu.actionClavier(' ');
        break;
      case 's': // accroupi
        jeu.actionClavier('x');
        break;
      case 'c': // coup de poing
        jeu.actionClavier('e');
        break;
      case 'v': // coup de pied joueur 1
        jeu.actionClavier('r');
        break;
      case 'e': // parade
        jeu.actionClavier('a'); 
        break;
      case 'r': // hadoken
        jeu.actionClavier('z');
        break;

      // Joueur 2
      if(!jeu.mode)
      {
        case 'k': // deplacement a gauche
          jeu.actionClavier('k');
          break;
        case 'm': // deplacement a droite
          jeu.actionClavier('l');
          break;
        case 'o': // saut
          jeu.actionClavier('m');
          break;
        case 'l': // accroupi
          jeu.actionClavier('b');
          break;
        case ',': // coup de poing
          jeu.actionClavier('p');
          break;
        case 'n': // coup de pied joueur 2
          jeu.actionClavier('o');
          break;
        case 'i': // parade
          jeu.actionClavier('y');
          break;
        case 'u': // hadoken
          jeu.actionClavier('h'); 
          break;
      }
      case '\e': // quitter le jeu
        ok = false;
        break;
    }
    // Joueur 2 IA
    if(jeu.mode)
        jeu.comportementAutoJoueur2();
  }
}

void txtJeu::txtBoucle()
{
  bool ok = true;
  while(ok) // boucle du programme
  {
    // Associe les événements claviers à des actions
    ecouteClavier(ok);
    
    // MAJ JEU
    jeu.update();
    // AFFICHAGE
    txtAfficher();

    #ifdef _WIN32
      Sleep(40);
    #else
      usleep(100000);
        #endif // WIN32
  }
}

void txtJeu::dessineTerrain(WinTXT  &win) const
{
  for(int i = 0; i < jeu.env.DIMX; i++)
    win.print(i,jeu.env.DIMY-1,'_');
  for(int i = 3; i < jeu.env.DIMY; i++)
  {
    win.print(0,i,'|');
    win.print(jeu.env.DIMX-1, i,'|');
  }
}

void txtJeu::animationCoupPoing(WinTXT &win, Personnage &psng) const
{
  int posX = (int) psng.getPosition().x; // garde la partie entiere du float pour 
  int posY = (int) psng.getPosition().y; // correspondre aux indices du tableau 2D
  win.print(posX-1,posY,'/'); // dessine la jambe gauche
  win.print(posX+1,posY,'\\'); // dessine la jambe droite
  win.print(posX,posY-1,'|');  // dessine le buste
  win.print(posX,posY-2,'@'); // dessine la tete
  if(psng.regardeDroite)
  {
    win.print(posX+1,posY-2,'_'); // dessine le debut du bras
    win.print(posX+2,posY-2,'_'); // dessine la fin du bras
    win.print(posX+3,posY-2,'.'); // dessine le poing
  }
  else
  {
    win.print(posX-1,posY-2,'_'); // dessine le debut du bras
    win.print(posX-2,posY-2,'_'); // dessine la fin du bras
    win.print(posX-3,posY-2,'.'); // dessine le poing
  }
  psng.animationActionEnCoursTerminee();
}

void txtJeu::animationCoupPied(WinTXT &win, Personnage &psng) const
{
  int posX = (int) psng.getPosition().x; // garde la partie entiere du float pour 
  int posY = (int) psng.getPosition().y; // correspondre aux indices du tableau 2D
  win.print(posX,posY-1,'|'); // dessine le buste
  win.print(posX,posY-2,'@'); // dessine la tete
  if(psng.regardeDroite)
  {
    win.print(posX-1,posY-1,'/'); // dessine le bras gauche
    win.print(posX+1,posY-2,'_'); // dessine le bras droit
    win.print(posX-1,posY,'/'); // dessine la jambe gauche
    win.print(posX+1,posY-1,'_'); // dessine le debut de la jambe droite
    win.print(posX+2,posY-1,'_'); // dessine lafin de la jambe droite
    win.print(posX+3,posY-1,','); // dessine le pied de la jambe droite
  }
  else
  {
    win.print(posX+1,posY-1,'\\'); // dessine le bras droit
    win.print(posX-1,posY-2,'_'); // dessine le bras gauche
    win.print(posX+1,posY,'\\'); // dessine la jambe droite
    win.print(posX-1,posY-1,'_'); // dessine le debut de la jambe gauche
    win.print(posX-2,posY-1,'_'); // dessine lafin de la jambe gauche
    win.print(posX-3,posY-1,','); // dessine le pied de la jambe gauche
  }
  psng.animationActionEnCoursTerminee();
}

void txtJeu::animationParade(WinTXT &win, Personnage &psng) const
{
  int posX = (int) psng.getPosition().x; // garde la partie entiere du float pour 
  int posY = (int) psng.getPosition().y; // correspondre aux indices du tableau 2D
  win.print(posX,posY-2,'@'); // dessine la tete
  win.print(posX,posY-1,'|'); // dessine le buste
  win.print(posX-1,posY,'/'); // dessine la jambe gauche
  win.print(posX+1,posY,'\\'); // dessine la jambe droite
  if(psng.regardeDroite)
    win.print(posX+1,posY-1,'X'); // dessine le bras droit/gauche
  else
    win.print(posX-1,posY-1,'X'); // dessine le bras gauche/droit
}

void txtJeu::animationAccroupi(WinTXT &win, Personnage &psng) const
{
  int posX = (int) psng.getPosition().x; // garde la partie entiere du float pour 
  int posY = (int) psng.getPosition().y; // correspondre aux indices du tableau 2D
  win.print(posX,posY-1,'@'); // dessine la tete
  if(psng.regardeDroite)
  {
    win.print(posX+1,posY-1,','); // dessine les poing
    win.print(posX+2,posY-1,','); // dessine les poing
    win.print(posX-1,posY,'/'); // dessine le jambe gauche
    win.print(posX+1,posY,'\\'); // dessine le jambe droite
  }
  else
  {
    win.print(posX-1,posY-1,','); // dessine les poing
    win.print(posX-2,posY-1,','); // dessine les poing
    win.print(posX-1,posY,'/'); // dessine le jambe gauche
    win.print(posX+1,posY,'\\'); // dessine le jambe droite
  }
}

void txtJeu::animationCoupPoingAccroupi(WinTXT &win, Personnage &psng) const
{
  int posX = (int) psng.getPosition().x; // garde la partie entiere du float pour 
  int posY = (int) psng.getPosition().y; // correspondre aux indices du tableau 2D
  win.print(posX-1,posY,'/'); // dessine la jambe gauche
  win.print(posX+1,posY,'\\'); // dessine la jambe droite
  win.print(posX,posY-1,'@'); // dessine la tete
  if(psng.regardeDroite)
  {
    win.print(posX+1,posY-1,'_'); // dessine le debut du bras
    win.print(posX+2,posY-1,'_'); // dessine la fin du bras
    win.print(posX+3,posY-1,'.'); // dessine le poing
  }
  else
  {
    win.print(posX-1,posY-1,'_'); // dessine le debut du bras
    win.print(posX-2,posY-1,'_'); // dessine la fin du bras
    win.print(posX-3,posY-1,'.'); // dessine le poing
  }
  psng.animationActionEnCoursTerminee(true);
}

void txtJeu::animationCoupPiedAccroupi(WinTXT &win, Personnage &psng) const
{
  int posX = (int) psng.getPosition().x; // garde la partie entiere du float pour 
  int posY = (int) psng.getPosition().y; // correspondre aux indices du tableau 2D
  win.print(posX,posY-1,'@'); // dessine la tete
  win.print(posX,posY, 'v'); // dessine le buste
  if(psng.regardeDroite)
  {
    win.print(posX-1,posY,'/'); // dessine la jambe d'appuis
    win.print(posX+1,posY,'-'); // dessine le debut de la jambe
    win.print(posX+2,posY,'-'); // dessine le mileu de la jambe
    win.print(posX+3,posY,'-'); // dessine la fin de la jambe
    win.print(posX+4,posY,'\''); // dessine le pied
  }
  else
  {
    win.print(posX+1,posY,'/'); // dessine la jambe d'appuis
    win.print(posX-1,posY,'-'); // dessine le debut de la jambe
    win.print(posX-2,posY,'-'); // dessine le mileu de la jambe
    win.print(posX-3,posY,'-'); // dessine la fin de la jambe
    win.print(posX-4,posY,'\''); // dessine le pied
  }
  psng.animationActionEnCoursTerminee(true);
}

void txtJeu::animationParadeAccroupi(WinTXT &win, Personnage &psng) const
{
  int posX = (int) psng.getPosition().x; // garde la partie entiere du float pour 
  int posY = (int) psng.getPosition().y; // correspondre aux indices du tableau 2D
  win.print(posX,posY-1,'@'); // dessine la tete
  if(psng.regardeDroite)
  {
    win.print(posX+1,posY-1,'x'); // dessine les poing
    win.print(posX-1,posY,'/'); // dessine le jambe gauche
    win.print(posX+1,posY,'\\'); // dessine le jambe droite
  }
  else
  {
    win.print(posX-1,posY-1,'x'); // dessine les poing
    win.print(posX-1,posY,'/'); // dessine le jambe gauche
    win.print(posX+1,posY,'\\'); // dessine le jambe droite
  }
}

void txtJeu::animationDeboutInactif(WinTXT &win, Personnage &psng) const
{
  int posX = (int) psng.getPosition().x; // garde la partie entiere du float pour 
  int posY = (int) psng.getPosition().y; // correspondre aux indices du tableau 2D
  win.print(posX-1,posY,'/'); // dessine la jambe gauche
  win.print(posX+1,posY,'\\'); // dessine la jambe droite
  win.print(posX-1,posY-1,'/'); // dessine le bras gauche
  win.print(posX,posY-1,'|'); // dessine le buste
  win.print(posX+1,posY-1,'\\'); // dessine le bras droit
  win.print(posX,posY-2,'@'); // dessine la tete
  psng.animationActionEnCoursTerminee();
}

void txtJeu::animationSaut(WinTXT &win, Personnage &psng) const
{
  int posX = (int) psng.getPosition().x; // garde la partie entiere du float pour 
  int posY = (int) psng.getPosition().y; // correspondre aux indices du tableau 2D
  win.print(posX-1,posY,'/'); // dessine la jambe gauche
  win.print(posX+1,posY,'\\'); // dessine la jambe droite
  win.print(posX-1,posY-1,'/'); // dessine le bras gauche
  win.print(posX,posY-1,'|'); // dessine le buste
  win.print(posX+1,posY-1,'\\'); // dessine le bras droit
  win.print(posX,posY-2,'@'); // dessine la tete
  if(posY == jeu.env.hauteurSol)
    psng.animationActionEnCoursTerminee();
}

void txtJeu::animationHadoken(WinTXT &win, Personnage &psng) const
{
  int posX = (int) psng.getPosition().x; // garde la partie entiere du float pour 
  int posY = (int) psng.getPosition().y; // correspondre aux indices du tableau 2D
  win.print(posX-1,posY,'/'); // dessine la jambe gauche
  win.print(posX+1,posY,'\\'); // dessine la jambe droite
  win.print(posX,posY-1,'|'); // dessine le buste
  win.print(posX,posY-2,'@'); // dessine la tete
  if(psng.regardeDroite)
    win.print(posX+1,posY-1,'('); // dessine les bras
  else
    win.print(posX-1,posY-1,'(');
  psng.animationActionEnCoursTerminee();
  psng.projectile.vivant = true;
}

void txtJeu::animationWin(WinTXT &win, Personnage &psng) const
{
  int posX = (int) psng.getPosition().x; // garde la partie entiere du float pour 
  int posY = (int) psng.getPosition().y; // correspondre aux indices du tableau 2D
  win.print(posX-1,posY,'/'); // dessine la jambe gauche
  win.print(posX+1,posY,'\\'); // dessine la jambe droite
  win.print(posX-1,posY-2,'\\'); // dessine le bras gauche
  win.print(posX,posY-1,'|'); // dessine le buste
  win.print(posX+1,posY-2,'/'); // dessine le bras droit
  win.print(posX,posY-2,'@'); // dessine la tete
}

void txtJeu::animationKO(WinTXT &win, Personnage &psng) const
{
  int posX = (int) psng.getPosition().x; // garde la partie entiere du float pour 
  int posY = (int) psng.getPosition().y; // correspondre aux indices du tableau 2D
  if(psng.regardeDroite)
  {
    win.print(posX-2,posY,'@'); // dessine la tete
    win.print(posX-1,posY,'\\'); // dessine la tete
    win.print(posX,posY,'_'); // dessine la tete
    win.print(posX+1,posY,'_'); // dessine la tete
    win.print(posX+2,posY,','); // dessine la tete
  }
  else
  {
    win.print(posX+2,posY,'@'); // dessine la tete
    win.print(posX+1,posY,'\\'); // dessine la tete
    win.print(posX,posY,'_'); // dessine la tete
    win.print(posX-1,posY,'_'); // dessine la tete
    win.print(posX-2,posY,','); // dessine la tete
  }
}

void txtJeu::dessinePersonnage(WinTXT &win, Personnage &psng) const
{
  if(psng.currentAction == 1) // posture "coup de poing"
    animationCoupPoing(win,psng);
  else if(psng.currentAction == 2)
    animationCoupPied(win,psng);
  else if(psng.currentAction == 3) // posture parade
    animationParade(win,psng);
  else if(psng.currentAction == 10) // posture accroupi
    animationAccroupi(win,psng);
  else if(psng.currentAction == 11) // posture "coup de poing accroupi”
    animationCoupPoingAccroupi(win,psng);
  else if(psng.currentAction == 12) // posture "coup de pied accroupi”
    animationCoupPiedAccroupi(win,psng);
  else if(psng.currentAction == 13) // posture accroupi parade
    animationParadeAccroupi(win,psng);
  else if(psng.currentAction == 20)
    animationSaut(win,psng);
  else if(psng.currentAction == 4)
    animationHadoken(win,psng);
  else if (psng.currentAction == 99)
    animationKO(win,psng);
  else if (psng.currentAction == 100)
    animationWin(win,psng);
  else // posture "standard"
    animationDeboutInactif(win,psng);
}

void txtJeu::ecrire(WinTXT &win, const string &str, unsigned int posX, unsigned int posY) const
{
  for(unsigned int i = 0; i < str.length(); i++)
    win.print(posX+i,posY,str[i]);
}
      
void txtJeu::dessineHUD(WinTXT &win) const
{
  // affichage de la barre de vie du joueur 1
  for(int i = 2; i < (int)(jeu.joueur1.vie/10) + 2; i++)
    win.print(i,3,'#');
  ecrire(win,"JOUEUR 1",2,4);
  // affichage de la barre de vie du joueur 2
  for(int i = 2; i < (int)(jeu.joueur2.vie/10) + 2; i++)
    win.print(jeu.env.DIMX-1-i,3,'#');
  ecrire(win,"JOUEUR 2", jeu.env.DIMX-10,4);

  // affichage des vainqueurs
  if(jeu.joueur1.currentAction == 100)
    ecrire(win,"JOUEUR 1 WINS",(jeu.env.DIMX/2)-6,jeu.env.DIMY/2);
  else if(jeu.joueur2.currentAction == 100)
    ecrire(win,"JOUEUR 2 WINS",(jeu.env.DIMX/2)-6,jeu.env.DIMY/2);

  // affichage des debuts de rounds
  if(jeu.delayDebut != 0 && (float(clock()-jeu.delayDebut)/CLOCKS_PER_SEC) < jeu.env.maxDelay/2)
    ecrire(win,"ROUND "+std::to_string(jeu.winJ1+jeu.winJ2+1),(jeu.env.DIMX/2)-3,jeu.env.DIMY/2);
  else if(jeu.delayDebut != 0 && (float(clock()-jeu.delayDebut)/CLOCKS_PER_SEC) <= jeu.env.maxDelay)
    ecrire(win,"FIGHT !",(jeu.env.DIMX/2)-3,jeu.env.DIMY/2);
}

void txtJeu::dessineProjectile(WinTXT  &win, Projectile & projectile) const
{
  win.print(projectile.position.x,projectile.position.y+1,'O');
}

void txtJeu::txtAfficher()
{
  // efface le buffer de caracteres
  win.clear();
  // dessine le terrain dans le buffer
  dessineTerrain(win);
  // dessine les projectiles dans le buffer
  if(jeu.joueur1.projectile.vivant)
    dessineProjectile(win, jeu.joueur1.projectile);
  if(jeu.joueur2.projectile.vivant)
    dessineProjectile(win, jeu.joueur2.projectile);
  // dessine les personnages dans le buffer
  dessinePersonnage(win, jeu.joueur1); 
  dessinePersonnage(win, jeu.joueur2); 
  // dessine le HUD
  dessineHUD(win);
  // nouvel affichage
  win.draw();
}