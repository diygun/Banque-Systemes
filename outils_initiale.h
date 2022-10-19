#ifndef OUTILS_INITIALE_H
#define OUTILS_INITIALE_H

#define TAILLE_MDP 32
#define TAILLE_LECTURE 1000
//#define ESPACE printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
#define ESPACE printf("\n\n\n\n");

void ecrire_fichier();

// retourne : 1 -> OK / 0 -> Faux
int compare(char mdp[], char checker[]);

// retourne l'id de l'utilisateur connecte
int connexion();

// connexion administrateur retourne 1 si mauvais et 0 si bon
int connexion_administrateur(char *id_administrateur);

// affiche le solde de l'utilisateur connecte
float solde(int id_du_solde_a_check);

// mouvmente le solde d'un compte vers un autre
int envoie(int id_emetteur);

int supprimer_ligne(int ligne_a_supprimer);

int copie_fichier(char fichier_source[], char fichier_copie[]);

int compte_existe(int compte_a_verifier);

int num_ligne(int identifiant_a_numeroter);


// admin

void affiche_id_solde();


#endif