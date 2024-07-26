#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "listMit.h"
void lire_etudiants(donne etudiant[], int *index) {
    FILE *file = fopen("/home/mit/listL1/list.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Erreur d'ouverture de liste.txt\n");
        exit(1);
    }

    char line[256];
    *index = 0;

    while (fgets(line, sizeof(line), file) != NULL && *index < 75) {
        char *c = strchr(line, '\n');
        if (c != NULL)
            *c = '\0';

        char *nom = strtok(line, ":");
        char *prenom = strtok(NULL, ":");

        if (nom != NULL && prenom != NULL) {
            strcpy(etudiant[*index].nom, nom);
            strcpy(etudiant[*index].prenom, prenom);
            etudiant[*index].numero = *index + 1;
            etudiant[*index].machine = ABS;

            (*index)++;
        }
    }

    fclose(file);
}

void enregistrer_presence(donne etudiant[], int index, int checknumero[], int count, char date[]) {
	int compte_oui=0, compte_non=0, compte_abs=0, compte_perso=0;
    FILE *f = fopen("/home/mit/listL1/presence.html", "w");
    if (f == NULL) {
        fprintf(stderr, "Erreur d'ouverture de presence.txt\n");
        exit(1);
    }
	fprintf(f, "<html>\n<head>\n<title>FICHE DE PRESENCE</title>\n<style>\ntable{");
	fprintf(f, "border-collapse: collapse;\nwidth: 50px\n}\n");
	fprintf(f, "th,td{\nborder: 1px solid black;\npadding: 8px;\ntext-align: center;\n}\n");
	fprintf(f,"th {\nbackground-color: #f2f2f2;\n}\nbody {\nbackground-color: #c2c6c9;\n}\n</style>\n</head>\n");
	fprintf(f, "<body background-color: #C2C4C9;>\n<header><img src=\"/home/mit/mit.png\" alt=\"Image\" class=\"top-left-image\">\n<main>\n<center>\n<h2>FICHE DE PRESENCE DES ETUDIANTS MIT</h2>\n<table>\n<tr>\n");
	fprintf(f, "<th>NUMERO</th>\n");
	fprintf(f, "<th>NOM</th>\n");
	fprintf(f, "<th>PRENOM</th>\n");
	fprintf(f, "<th>DATE</th>\n<th>HEURE</th>\n");
	fprintf(f, "<th>PRESENCE MACHINE</th>\n</tr>\n");
    for (int i = 0; i < index; i++) {
		fprintf(f, "<tr>\n");
        fprintf(f, "<td>%d</td>\n", etudiant[i].numero);
        fprintf(f, "<td>%s</td>\n", etudiant[i].nom);
		fprintf(f, "<td>%s</td>\n", etudiant[i].prenom);
		fprintf(f, "<td style=\"color: orange\">%s</td>\n", __DATE__);
		fprintf(f, "<td style= \"color: purple\">%s</td>\n", date);	
        switch (etudiant[i].machine) {
            case OUI:
                fprintf(f, "<td style=\"color: green\">\n<center>OUI</center>\n</td>\n");
                compte_oui++;
                break;
            case NON:
                fprintf(f, "<td style=\"color: red\">\n<center>NON</center>\n</td>\n");
                compte_non++;
                break;
            case PERSO:
                fprintf(f, "<td style=\"color: blue\">\n<center>PERSO</center></td>\n");
                compte_perso++;
                break;
            default:
                fprintf(f, "<td style=\"color: black\"><center>ABS</center></td>\n");
                compte_abs++;
                break;
        }
        fprintf(f, "</tr>\n");
    }
    fprintf(f, "</table>\n</center>\n");
    fclose(f);
}

void gerer_interactions(donne etudiant[], int index, int checknumero[], int *count, char date[]) {
    while (1) {
        int choix = 0;
			printf("Quelle recherche voulez-vous faire?\n");
			printf("1) - à partir du numero\n");
			printf("2) - à partir d'un nom ou un prenom\n");
			printf("3) - pour quitter le programme\n==> ");
			scanf("%d", &choix);

			if (choix == 3)
				break;
			else if (choix == 1) {
				int numero;
				printf("Entrer le numero de l'etudiant ( 0 pour quitter le programme ) : ");
				scanf("%d", &numero);
				if (numero == 0)
					break;
				if (numero > index) {
					printf("Numero hors de liste, réessayer\n");
					continue;
				}

				int numero_deja_entrer = 0;
				for (int i = 0; i < *count; i++) {
					if (checknumero[i] == numero - 1) {
						numero_deja_entrer = 1;
						break;
					}
				}

				if (numero_deja_entrer) {
					printf("Le numero est déjà tapez, saisir une autre\n");
					continue;
				}

				checknumero[*count] = numero - 1;
				(*count)++;

				printf("Entrez la présence pour %s %s (OUI, NON, PERSO) : ", etudiant[numero - 1].nom, etudiant[numero - 1].prenom);
				char presence[10];
				scanf("%s", presence);

				if (strcmp(presence, "OUI") == 0) {
					etudiant[numero - 1].machine = OUI;
				} else if (strcmp(presence, "NON") == 0) {
					etudiant[numero - 1].machine = NON;
				} else if (strcmp(presence, "PERSO") == 0) {
					etudiant[numero - 1].machine = PERSO;
				} else {
					printf("Présence invalide.\n");
				}
			} else if (choix == 2) {
				char recherche_nom[100];
				int mot_trouve = 0;
				printf("Entrer un nom ou un prenom : ");
				scanf("%s", recherche_nom);

				for (int i = 0; i < index; i++) {
					if (strstr(etudiant[i].nom, recherche_nom) != NULL || strstr(etudiant[i].prenom, recherche_nom) != NULL) {
						printf("Entrez la présence pour %s %s (OUI, NON, PERSO) : ", etudiant[i].nom, etudiant[i].prenom);
						mot_trouve = 1;

						char presence[10];
						scanf("%s", presence);

						if (strcmp(presence, "OUI") == 0) {
							etudiant[i].machine = OUI;
						} else if (strcmp(presence, "NON") == 0) {
							etudiant[i].machine = NON;
						} else if (strcmp(presence, "PERSO") == 0) {
							etudiant[i].machine = PERSO;
						} else {
							printf("Présence invalide.\n");
						}
					}
				}

				if (!mot_trouve) {
					printf("Aucun étudiant trouvé avec ce nom ou prénom.\n");
				}
			} else {
				printf("Choix invalide, tapez 1 ou 2 ou 3\n");
		}
	}
}
void afficher_comptes(donne etudiant[], int index)
{
	FILE *f = fopen("/home/mit/listL1/presence.html", "a");
    int compte_OUI = 0, compte_NON = 0, compte_PERSO = 0, compte_ABS = 0;
	if(f==NULL){
		fprintf(f, "Erreur d'ouverture détécté");
		exit(1);
	}
    for (int i = 0; i < index; i++) {
        switch (etudiant[i].machine) {
            case OUI:
                compte_OUI++;
                break;
            case NON:
                compte_NON++;
                break;
            case PERSO:
                compte_PERSO++;
                break;
            default:
                compte_ABS++;
                break;
        }
    }
    fprintf(f, "<center>\n<h2>\nTOTALE D'UTILISATION MACHINE</h2>\n");
	fprintf(f, "<table style=\"color: red\">\n<tr>\n");
	fprintf(f, "<th>OUI</th>\n");
	fprintf(f, "<th>NON</th>\n");
	fprintf(f, "<th>PERSO</th>\n");
	fprintf(f, "<th>ABSENT</th>\n</tr>\n");
    fprintf(f, "<tr>\n<td>%d</td>\n", compte_OUI);
    fprintf(f, "<td>%d</td>\n", compte_NON);
    fprintf(f, "<td>%d</td>\n", compte_PERSO);
    fprintf(f, "<td>%d</td>\n</table>\n</center>\n</main>\n</body>\n</html>", compte_ABS);
    fclose(f);
}
