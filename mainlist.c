#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "listMit.h"

int main() {
    donne etudiant[75];
    int index = 0;
    int checknumero[100];
    int count = 0;
    char date[20];

    time_t now = time(NULL);
    strftime(date, 20, "%H:%M:%S", localtime(&now));

    lire_etudiants(etudiant, &index);
    gerer_interactions(etudiant, index, checknumero, &count, date);
    enregistrer_presence(etudiant, index, checknumero, count, date);
	afficher_comptes(etudiant, index);
    return 0;
}
