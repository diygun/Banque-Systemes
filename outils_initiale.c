#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>
#include "outils_initiale.h"


// 0 = erreur d'envoie et 1 -> Succes !
int envoie(int id_emetteur) {
    float solde_emetteur;
    int compte_receveur;
    int recveur_existe = 0;
    int somme_envoye;
    solde_emetteur = solde(id_emetteur);
    int ligne_emetteur, ligne_receveur;


    FILE *lecture_bdd;
    lecture_bdd = fopen ("bdd_u_passwd.txt", "r+");
    if (lecture_bdd == NULL) printf ("ERRO 404\n");
    int identif_lecteur, solde;



    char mdp_lecteur[32];
    
    // variable en memoire //
    char mdp_emmetteur[32];
    float solde_receveur;
    char mdp_recveur[32];
    // ---  fin  ---


    printf("Votre solde est de : %.2f\n", solde_emetteur);
    printf("Veuillez entrez le compte auquel vous souhaitez faire un virement : "); scanf("%d", &compte_receveur);
    if(compte_receveur == id_emetteur)
    {
        printf("Vous ne pouvez pas envoyer de l'argent a vous meme !\n");
        return 0;
    }
    //verifier si compte_receveuer existe.
    printf("Entrez la somme que souhaitez vous envoyer au compte %d : ", compte_receveur); scanf("%d", &somme_envoye);
    if (somme_envoye > solde_emetteur)
    {
        printf("\t > Votre solde est insuffisant. Veuillez approvisionner votre compte et reessayer ");
        return 0; 
    }
    if (somme_envoye <= solde_emetteur)
    {
        // verifier si compte receveur existe, si il n'existe pas on retourne 0; -> erreur d'envoie
        if( 0 == (compte_existe(compte_receveur)) ) return 0;

        // mettre en variable le compte qui envoie,
        while (fscanf(lecture_bdd, "id : %d, password : %s , solde : %f\n", &identif_lecteur, &mdp_lecteur, &solde) != EOF)
        {
            // printf("Le mot de passe lecture est : %s\n", mdp_lecteur);
            if(id_emetteur == identif_lecteur)
            {
                strcpy(mdp_emmetteur, mdp_lecteur);
                // printf("id : %d, password : %s , solde : %d\n", id_emetteur, mdp_emmetteur, solde_emetteur);
            }
            // mettre en variable le compte qui recois
            if(compte_receveur == identif_lecteur)
            {
                strcpy(mdp_recveur, mdp_lecteur);
                solde_receveur = solde;
            }
        }
        
        // majorer le solde receveur et dimiuer le  compte envoyeur 
        solde_emetteur = solde_emetteur - somme_envoye;
        solde_receveur = solde_receveur + somme_envoye;
        
        
        // effacer la ligne du compte envoyeur
        // effacer la ligne du compte receveur
        ligne_emetteur = num_ligne(id_emetteur);
        // printf("La ligne qui envoie  : %d", ligne_emetteur);
        ligne_receveur = num_ligne(compte_receveur);
        // printf("La ligne qui envoie  : %d", ligne_receveur);
        fclose(lecture_bdd);
        
        supprimer_ligne(ligne_emetteur); // Faire fct qui compte le numero ligne de l'utilisatuer
        supprimer_ligne(ligne_receveur);
        // ajouter les comptes mis en variable
        // ajout emmeteur



        FILE *ecrire_fin_bdd;
        ecrire_fin_bdd = fopen ("bdd_u_passwd.txt", "a+");
        if (ecrire_fin_bdd == NULL) printf ("ERRO 404\n");


        fprintf(ecrire_fin_bdd, "id : %d, password : %s , solde : %f\n", id_emetteur, mdp_emmetteur, solde_emetteur);
        fprintf(ecrire_fin_bdd, "id : %d, password : %s , solde : %f\n", compte_receveur, mdp_recveur, solde_receveur);
        fclose(ecrire_fin_bdd);
        // retourner 1 -> succes
        // retourner 0 -> pour erruer

        return 1;
    }
    // fclose(ecrire_fin_bdd);
    fclose(lecture_bdd);
    return 0;
}


// 0 = erreur d'envoie et 1 -> Succes !
int compte_existe(int compte_a_verifier) {
    FILE *lecture_bdd;
    lecture_bdd = fopen ("bdd_u_passwd.txt", "r+");
    if (lecture_bdd == NULL) printf ("ERRO 404\n");
    int identif_lecteur;
    float solde;
    char mdp_lecteur;
    while (fscanf(lecture_bdd, "id : %d, password : %s , solde : %f\n", &identif_lecteur, &mdp_lecteur, &solde) != EOF)
    {
        if (identif_lecteur == compte_a_verifier) 
        {
            fclose(lecture_bdd);
            return 1;
        }
    }
    fclose(lecture_bdd);
    return 0;
}


// fct retourne numero de ligne de l'utilisateur entree en parametre
int num_ligne(int identifiant_a_numeroter) {
    int num_de_ligne = 1;
    int identif_lecteur;
    float solde;
    char mdp_lecteur;
    FILE *lecture_bdd;
    lecture_bdd = fopen ("bdd_u_passwd.txt", "r");
    if (lecture_bdd == NULL) printf ("ERRO 404\n");


    // lire le fichier jusqu'a trouver le bon id
    // mettre un compteur dans la boucle qui lit pour compter le numero de ligne, le numero commence a 1
    // tant que c'est pas la fin du fichier biensur.
    while (fscanf(lecture_bdd, "id : %d, password : %s , solde : %f\n", &identif_lecteur, &mdp_lecteur, &solde) != EOF) {
        if (identifiant_a_numeroter != identif_lecteur) num_de_ligne++;
        else if (identifiant_a_numeroter == identif_lecteur)
        {
            fclose(lecture_bdd);
            return num_de_ligne;
        }   
    }
}


int copie_fichier(char fichier_source[], char fichier_copie[])
{
    int caractere;
    FILE *src_fichier, *copie_fichier; 
    src_fichier = fopen(fichier_source, "r");
    if (src_fichier == NULL) 
    {
        return 0;
        // printf("Erruer Fichier 1 !\n");
    }
    copie_fichier = fopen(fichier_copie, "w");
    if (copie_fichier == NULL)
    {
        fclose (src_fichier);
        // printf("Erruer Fichier 2 !\n");
        return 0;
    }    
    while ((caractere = fgetc(src_fichier)) != EOF)
    fputc (caractere, copie_fichier);
    fclose (src_fichier);
    fclose (copie_fichier);
    return 1;
}

// retourne 0 -> erreur et 1-> succes
int supprimer_ligne(int ligne_a_supprimer) {

    // printf("Entrez la ligne de l'utilisateur a supprimer : "); scanf("%d", &delete_line);
    FILE *fichier, *temp;
    char bdd_fichier[] = "bdd_u_passwd.txt"; // fixhier ou supprimer une ligne
    char temp_bdd_fichier[50];
    char stockage_donnee[2048]; // stocke les caractere lu pour copie

    strcpy(temp_bdd_fichier , "temp____");
    strcat(temp_bdd_fichier , bdd_fichier);
    
    // ouvrire le fichier orginale + le temporaire
    fichier = fopen(bdd_fichier, "r"); //ouvre la bdd en lecture

    temp = fopen(temp_bdd_fichier, "w");

    if(fichier == NULL || temp == NULL )  
    {
        printf("Erreur d'ouverture des fichier");
        return 0; // 0 -> erreur
    }

    bool keep_reading = true;
    int current_line = 1;

    do // on va lire le fichier orginale et on va ignorer la ligne a supprimer
    {
        fgets(stockage_donnee, 1000, fichier);
        // ca va lire et stocker dans stockage_donnee les chaine de carcatere
        if(feof(fichier)) keep_reading = false;
        // si la fin du fichier alors on stoppe la lecture et on quitte la boucle
        else if (current_line != ligne_a_supprimer) // si c'est pas la ligne a supp alors on l'ecris dans le fichier temporaire
        {
            fputs(stockage_donnee, temp);
            // ca ecrire dans le fichier temporaire la ligne lu et stocke dans le stockage_donnee
        }
        current_line++;
    } while (keep_reading); // tant que continuer la lecture est vrais on continue
    // a ce stade le fichier temporaire sera comme le fichier orginale sauf avec la ligne a supp manquante
    fclose(fichier);
    fclose(temp);
    // effacer le fichier orginale et renommer le temporaire en nom orginale
    remove(bdd_fichier);
    rename(temp_bdd_fichier, bdd_fichier);
    return 1;
}

// fonction qui permet de se connecter
int connexion() {
    printf("\n\t\t Bienvenur, veuillez vous connecter pour commencer.\n \t >> Pour une conection administrateur entrez 0 comme nom d'utilisateur.\n");
    // printf("\t Votre Identifiant : "); scanf("");

    FILE *lecture_bdd;
    lecture_bdd = fopen ("bdd_u_passwd.txt", "r");
    if (lecture_bdd == NULL) printf ("\t\t >>>>  Base de donnee manquante <<<< ! \n");
    

    int identif_lecteur;
    char mdp_lecteur[32];
    int entree_utilisateur;
    char entree_mdp[32];
    int comparateur_mdp = 0;
    int login_status = 0;
    int solde;

    // ECRAN DE CONNEXION
    printf("\t Veuillez entrez votre identifiant : "); scanf("%d", &entree_utilisateur);
    if (entree_utilisateur == 0)
    {
        return -1;
    }
    printf("\t Veuillez entrez votre mot de passe : "); scanf("%s", entree_mdp);

    // FIN DE L'ECRAN DE CONNEXION 

    while (fscanf(lecture_bdd, "id : %d, password : %s , solde : %d\n", &identif_lecteur, &mdp_lecteur, &solde) != EOF) {
        // printf("l'identifiant : %d | mot de passe : %s\n", identif_lecteur, mdp_lecteur);

        // TEST DE LA CONNECTION
        if (identif_lecteur == entree_utilisateur)
        {
            // printf("Utilisateur : %d trouve !\n", identif_lecteur);
            // printf("Appuier sur ENTER pour continuer la verfication du mot de passe. \n");
            // getchar(); // marquer une pause a l'ecran
            // Comparer les mdps
            comparateur_mdp = compare(mdp_lecteur, entree_mdp); // 1 = ok / 0 = faux
            if (comparateur_mdp == 1)
            {
                printf("\n\t > Vous etes connecte ! Le mot de passe est bon.\n");
                login_status = entree_utilisateur;
                fclose(lecture_bdd);
                return entree_utilisateur;
                // mettre le status login ok;

            }
            else
            {
                printf("\n\t --- Le mot de passe est faux ! ");
                fclose(lecture_bdd);
                return 0;
            }
            fseek(lecture_bdd, 0, SEEK_END);
            // deplacer le curseur a la fin du fichier etc...
        }
    }
    // if ( identif_lecteur != entree_utilisateur )
    // {
    //     printf("\n\t +++ Le mot de passe est faux ! ");
    // }

    // printf("L'utilisateur %d est connecte avec succes !", login_status);
    // si le mdp correspond alors faire fseek(lecteur_bdd, 0, SEEK_END); pour sortire de la boucle et mettre int login_status =  l'identifiant de l'utilisateur connecte.


}


//Connexion administrateur retourne 1 si mauvais et 0 si bon
int connexion_administrateur(char *id_administrateur) {
    FILE *lecture_administrateur;
    lecture_administrateur = fopen ("administrateur.txt", "r");
    if (lecture_administrateur == NULL) printf ("ERRO 404\n");
    
    
    // char *id_administrateur;
    char identif_lecteur[32];

    char mdp_lecteur[32];
    char entree_mdp[32];
    int comparateur_mdp = 0;
    float solde;
    
    // ECRAN DE CONNEXION
    printf("\t Veuillez entrez votre identifiant : "); scanf("%s", id_administrateur);
    printf("\t Veuillez entrez votre mot de passe : "); scanf("%s", entree_mdp);
    // FIN DE L'ECRAN DE CONNEXION 

    while (fscanf(lecture_administrateur, "id : %s , password : %s\n", &identif_lecteur, &mdp_lecteur) != EOF) {
        // TEST DE LA CONNECTION
        if ( (compare(identif_lecteur, id_administrateur)) == 1 )
        {
            if ( (compare(mdp_lecteur, entree_mdp)) == 1 )
            {
                printf("\n\t > Vous etes connecte ! Le mot de passe est bon.\n");
                return 0;
                fclose(lecture_administrateur);
            }
            else
            {
                printf("\n\t !!! > Le mot de passe est faux ! ");
                return 1;
                fclose(lecture_administrateur);
            }
        }
    }
}

// retourne le solde de l'id entree
float solde(int id_du_solde_a_check) {
    FILE *lecture_bdd;
    lecture_bdd = fopen ("bdd_u_passwd.txt", "r");
    if (lecture_bdd == NULL) printf ("ERRO 404\n");

    int identif_lecteur;
    char mdp_lecteur[32];

    float solde;
    int comparateur_mdp;
    while (fscanf(lecture_bdd, "id : %d, password : %s , solde : %f\n", &identif_lecteur, &mdp_lecteur, &solde) != EOF) {

        if (identif_lecteur == id_du_solde_a_check) 
        {
            printf("\n\t > Le sold de %d est : %.2f\n", identif_lecteur, solde);
            fclose(lecture_bdd);
            return solde;
        }
    }
}

// VEIFIER : 1 si l'utilisateur existe déjà, 2 si le mdp est safe, 3? faire une suite logique de id ??
void ecrire_fichier(){
    int identifiant;
    char passwd[32]; // declarer la cahine de caractere en tant que pointeur et utiliser &passwd pour scanf et printf
    char choix[32];
    int verif;
    float solde = 0;
    FILE* ajout_fin_bdd = NULL;
    ajout_fin_bdd = fopen("bdd_u_passwd.txt", "a"); // ouverture du fichier bdd.txt en mode ajout a la fin uniquement
    
    // Verification de l'ouverture de la base de donnee, si pointeur non NULL alors execution du code.
    if (ajout_fin_bdd == NULL)
    {
        printf("Impossible d'ouvrire la base de donne !");
        return;
    }

    do
    {
    printf("\n\n\n =======================\n\t > Ajout d'un/une utilisateur/utilisatrice !\n =======================\n\n\n");
    printf("Enterez votre identifiant : "); scanf("%d", &identifiant);
    printf("Entrez votre mot de passe : "); scanf("%s", &passwd);
    printf("Entrez le solde a initialiser : "); scanf("%f", &solde);
    //printf("\t > Vous avez entrez l'identifiant : %d \n\t > Vous avez entre le mot de passe : %s\n", identifiant, passwd);
    printf("\n");
    printf("Confirmez-vous votre choix ? Oui - Non :"); scanf("%s", choix);
    // si choix= O o Oui oui alors verif = 1 --> si non boucler
    verif = compare(choix, "Oui"); if (verif==1) break;
    verif = compare(choix, "oui"); if (verif==1) break;
    verif = compare(choix, "o"); if (verif==1) break;

    } while (verif!=1);

    
    printf("\n\t > Choix confirmé !\n");
    printf("\t > Ajout en cours...\n");
    fprintf(ajout_fin_bdd, "id : %d, password : %s , solde : %f\n", identifiant, passwd, solde);
    printf("\t > Ajout termine !\n\n\n");

    fclose(ajout_fin_bdd);
}


int compare(char mdp[], char checker[]) {
    int i;
    int j;
    int MAX_CHAR;
    int taille_mdp = strlen(mdp);
    int taille_checker= strlen(checker);
    if (taille_mdp > taille_checker) MAX_CHAR = taille_mdp;
    else if (taille_checker > taille_mdp) MAX_CHAR = taille_checker;
    else MAX_CHAR = taille_checker = taille_mdp; // Le cas ou ni mdp ni checker est plus grand que l'autre
    
    // Cette fonction verifie le mot de passe entree prp au chceker
    // Elle retourne 1 si l'acces est autorise ( le mdp est BON = 1)
    // Elle retourne 0 si l'acces est refuse ( le mdp est MAUVAIS = 0)
    
    if (taille_mdp != taille_checker) return 0;

    else if (taille_mdp == taille_checker)
    {
        
    for ( i = 0; i < MAX_CHAR; i++) // verification un par un des composant d'un mdp
    {
        if (mdp[i] != checker[i]) return 0;
    }

    return 1;
    }

    else printf("\n\n ERREUR ! #0x001 "); // CODE ERREUR ! #0x001 
    return 5;
}


void affiche_id_solde() {
    FILE *lecture_bdd;
    lecture_bdd = fopen ("bdd_u_passwd.txt", "r");
    if (lecture_bdd == NULL) printf ("ERRO 404\n");

    int identif_lecteur;
    char mdp_lecteur[32];

    float solde;
    int comparateur_mdp;
    while (fscanf(lecture_bdd, "id : %d, password : %s , solde : %f\n", &identif_lecteur, &mdp_lecteur, &solde) != EOF) {
            printf("\n\t > Le sold de %d est : %.2f\n", identif_lecteur, solde);
    }
    fclose(lecture_bdd);
}

void supprimer_utilisateur() {
    int utilisateur_a_supprimer;
    printf("\t > Entrez l'id de l'utilisateur a supprimer : ");
    scanf("%d", utilisateur_a_supprimer);
    if(supprimer_ligne((num_ligne(utilisateur_a_supprimer))) == 1)
    {
        printf("Utilisateur supprime !");
    }
    else
    {
        printf("Erreur de suppression !");
    }
}

