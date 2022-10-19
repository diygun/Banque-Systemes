#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>
#include "outils_initiale.h"
#include "outils_initiale.c"
/*
Je pourrais utiliser des aray[][][] pour stocker le nom et mdp ... (peut etre re-convertir le type du solde en int et char pour la lecture, ecriture)
*/
int main() {

    int utilisateur_connecte;
    char administrateur_conectee[32];
    int verifier_administrateur;
    int redemander = 0;
    do
    {
        utilisateur_connecte = connexion();
        // -1 -> administrateur / 0 -> erreur donc redemander / >0 si utilisatuer (son id)

        if (utilisateur_connecte == -1) // Connexion administrateur
        {
            printf("Partie administrateur. \n");
            if (connexion_administrateur(administrateur_conectee) == 0)
                {
                   // CONNEXION ADMINISTRATEUR BON
                   printf("\t > Administrateur acctuellement connecte : %s\n", administrateur_conectee );
                        // si un administrateur est connecte 
                        // printf("\t > Utilisateur acctuellement connecte : %d", utilisateur_connecte);
                        char choix_administrateur = 0;
                        while (choix_administrateur != '9')
                        {
                            if (utilisateur_connecte == 0) break;
                            if (utilisateur_connecte > 0) break;
                            
                            //
                            fflush(stdin);
                            printf("\n\n");
                            printf("Que voulez vous faire :\n");
                            printf("1 - Afficher les utilisateurs et leur solde\n"); // afficher id et solde
                            printf("2 - Effacer un utilisateur\n");
                            printf("3 - Ajouter un utilisateur\n");
                            printf("4 - Modifier le solde d'un compte\n"); // Modifier le solde d'un compte OU Modifier un utilisateur
                            printf("5 - Verifier les journaux\n");
                            printf("9 - Pour se deconnecter\n");        
                            printf("Entrez le numdeo de l'action a realiser :"); scanf("%c",&choix_administrateur);
                            printf("\n");
                        
                            switch (choix_administrateur)
                            {
                            case '1':
                                ESPACE
                                affiche_id_solde();
                                break;
                            case '2':
                                // modifier solde utilisateur
                                break;
                            case '3':
                                ecrire_fichier();
                                break;
                            case '9':
                                printf("Deconnexion... Bonne journee %d !\n", utilisateur_connecte);
                                utilisateur_connecte = 0;
                                ESPACE
                                break;
                            default:
                                printf("\nVous avez entrez un mauvais nombre\n");
                                break;
                            }
                        }

                   //
                   //
                   //
                    // mettre utilisateur_connecte = -2; pour re permettre de demander si deconnexion
                }
            else
                {
                    printf("Tantative de connexion de la part de %s", administrateur_conectee);
                }
        }

        else if (utilisateur_connecte > 0) // partie utilisateur :
        {

            // si un utilisateur est connecte 
            printf("\t > Utilisateur acctuellement connecte : %d", utilisateur_connecte);
            char choix = 0;
            while (choix != '9')
            {
                if (utilisateur_connecte == 0) break;
                if (utilisateur_connecte < 0) break;
                
                //
                fflush(stdin);
                printf("\n\n");
                printf("Que voulez vous faire :\n");
                printf("1 - Voir le solde de votre compte\n");
                printf("2 - Faire un envoie\n");
                printf("3 - ...\n");
                printf("9 - Pour se deconnecter\n");        
                printf("Entrez le numdeo de l'action a realiser :"); scanf("%c",&choix);
                printf("\n");
            
                switch (choix)
                {
                case '1':
                    ESPACE
                    solde(utilisateur_connecte);
                    // printf("Le numero de ligne est : %d", num_ligne(utilisateur_connecte));
                    break;
                case '2':
                    envoie(utilisateur_connecte);
                    break;
                case '3':
                    // ecrire_fichier();
                    printf("\n...\t...\t...\n");
                    break;
                case '9':
                    printf("Deconnexion... Bonne journee %d !\n", utilisateur_connecte);
                    utilisateur_connecte = 0;
                    ESPACE
                    break;
                default:
                    printf("\nVous avez entrez un mauvais nombre\n");
                    break;
                }
            }
        }

        else if (utilisateur_connecte == 0)// non connecté donc a redemander
        {
            redemander = 0;
        }

    } while (redemander == 0);
    
    return 0;
}

