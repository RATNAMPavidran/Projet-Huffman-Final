#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED




typedef struct Element Element;
struct Element
{
    char lettre;
    int nombre;
    Element *suivant;
};


typedef struct Noeud Noeud;
struct Noeud
{
    int poids;
    char lettre;

    char code[30];
    Noeud *droite;
    Noeud *gauche;
};


typedef struct L_Noeud L_Noeud;
struct L_Noeud
{
    Noeud* n;
    L_Noeud *suivant;
};

typedef struct Queue Queue;
struct Queue
{
    L_Noeud* liste_noeud;
};


//PART 1
char *binaire(char a);
void print_tree(Noeud* tree);
void trad_fichier_ascii(FILE *f);
int nombre_caractere_fich_txt (FILE *f);

//PART2
void creer_liste(L_Noeud**l_nd,Element* l);
Noeud** tab_swipe(Noeud** tab,int taille_min,int pos);
void Arbre_Huff(Element* l);
void encodage(FILE* dico, FILE* f);
void dico_binaire(FILE* dico, char caractere, char* trad,int taille);
void creer_code(Noeud *Arbre, char* code, FILE* dico);
void afficherListe_Noeud(L_Noeud *liste);
Element* compter_occurrence(FILE *f);
void trie_liste(Element * * liste);

//PART3
//Tableau
Noeud **creer_tab_occur(FILE* f,int *taille);
Noeud ** creer_2_premiers_noeud (Noeud** tab,int* taille,FILE* f);
L_Noeud * Tab_to_L_Noeud(Noeud ** tab , int nbre_chara_diff );
void quick_sort(Noeud*** tab, int debut, int fin);
void Afficher_tab(int taille, Noeud**tab);
char* code_dans_avl (char lettre, Noeud*avl);

//Encodage
void encodage_avl(FILE* f, Noeud*avl);
void decodage_avl(Noeud*avl);


//Arbre
Noeud* fusionner_deux_noeuds(Noeud*n1,Noeud*n2);
Noeud* Arb_Huff_queue(Noeud **tab,int taille);
void free_tree(Noeud** tree);

//Dictionnaire
void creer_code_v2(Noeud *Arbre, char* code,Noeud**tab);
int chercher_lettre_avl(Noeud *avl,char* code, char* lettre);

//PART AVL
void add_noeud_avl (Noeud**avl,Noeud*noeud);
int depth(Noeud* tree);
int bf(Noeud* tree);
void right_rotation(Noeud** tree);
void left_rotation(Noeud** tree);
void balance(Noeud** tree);
Noeud* creer_avl(Noeud**tab, int taille);

#endif // FONCTION_H_INCLUDED
