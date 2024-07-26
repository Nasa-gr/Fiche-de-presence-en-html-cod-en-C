typedef enum {
    OUI,
    NON,
    PERSO,
    ABS
} utilisation;

typedef struct {
    char nom[100];
    char prenom[100];
    int numero;
    utilisation machine;
} donne;

void lire_etudiants(donne etudiant[], int *index);
void enregistrer_presence(donne etudiant[], int index, int checknumero[], int count, char date[]);
void gerer_interactions(donne etudiant[], int index, int checknumero[], int *count, char date[]);
void afficher_comptes(donne etudiant[], int index);
