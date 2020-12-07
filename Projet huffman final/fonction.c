#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"
#include <string.h>

/// PARTIE 1
void trad_fichier_ascii(FILE *f)
{
    FILE* trad = fopen("Traduction.txt","w+");
    char caractereActuel;
    char* traduction = malloc(sizeof (char)*9);
    if (f != NULL)
    {
        do
        {
            caractereActuel = fgetc(f); // on récupère un caractère du fichier
            traduction=binaire(caractereActuel);  // on traduit en binaire
            if (caractereActuel!=-1) //c'est EOF mais correspond sur certaines machines a -1
                fputs(traduction,trad);
            free(traduction);
        } while (caractereActuel != EOF);

    }
    fclose(trad);
}

char *binaire(char a) //Convertie les lettres en binaire
{
    int i = 0;
    char* octet = malloc(9);
    for (i=0;i<8;i++)
    {
        int puissance=1;
        for(int p=7-i;p>0;p--)//On commence par 2^7 jusqu'a 2^1
        {
            puissance=2*puissance;  // puissance de 2
        }

        if (a-puissance>=0)  //Si la valeur ASCII - la puissance est positif ou = 0 (ex : cas du 2^0-1) on a 1
        {
            a=a-puissance;
            octet[i]='1';

        }
        else
            octet[i]='0';

    }
    octet[8]='\0';

    return octet;
}

int nombre_caractere_fich_txt (FILE *f)
{
    int nombre=0; // on enleve le NULL ‡ la fin du texte
    char caractereActuel;
    do
    {
        caractereActuel = fgetc(f);
        if (caractereActuel!=-1)
        {
             nombre++;
        }

    } while (caractereActuel != EOF);// REGLER LE -1 A LA FIN

    return nombre;
}


///PARTIE 2

Element* compter_occurrence(FILE *f)
{
    Element* lsc;
    lsc=malloc(sizeof(Element));

    char lettre;
    Element* temp=lsc;

    if (f != NULL)
    {
        lettre=fgetc(f);
        if (lettre != EOF)// condition pour lorsqu'on a un fichier vide
        {
            lsc->lettre= lettre ;  //On stock la 1 ere lettre dans la structure
            lsc->nombre = 1;
            lsc->suivant = NULL;
        }
        else
        {
            lsc=NULL;
            return lsc;
        }

        while (lettre != EOF)
        {
            lettre = fgetc(f);  // on stock le caractère suiv


            if (lettre!=EOF)
            {
                int trouve=0;
                temp=lsc;
                if (lettre!=-1)
                {
                    while ((temp!=NULL)&&trouve!=1) // Boucle pour chercher le caractère existant
                    {
                        if (lettre==temp->lettre)   // CAS ou on a déja rencontré le caractère
                        {
                            temp->nombre++;
                            trouve=1;
                        }
                        temp=temp->suivant;

                    }
                    if (trouve==0)// CAS ou on a jamais encore rencontrer le caractere
                    {
                        temp=lsc;
                        Element* nouveau=malloc(sizeof(Element));
                        while (temp->suivant!=NULL) // arrive jusqu'à la fin pour ajouter le nv caractère à la liste
                        {
                            temp=temp->suivant;
                        }
                        nouveau->lettre=lettre;
                        nouveau->nombre=1;
                        nouveau->suivant =NULL;
                        temp->suivant=nouveau;

                    }
                }

            }
            else
            {
                while (temp->suivant!=NULL)
                {
                    temp=temp->suivant;
                }
                temp->suivant=NULL;
            }
        } // REGLER LE -1 A LA FIN
    }


    //afficherListe(lsc);
    return lsc;
}


void afficherListe(Element *liste)
{
    Element* temp=liste;

    while (temp != NULL)
    {
        printf("'%c' = ",temp->lettre);
        printf("%d -> ", temp->nombre);
        temp = temp->suivant;
    }
    printf("NULL\n");
}

void creer_liste(L_Noeud**l_nd,Element* l) // CREER une liste de noeuds
{
    Element*lect=l; //lect pour lecture
    L_Noeud *temp=*l_nd; // l_nd liste de noeud

    Noeud *n= malloc(sizeof(Noeud));

    n->poids=lect->nombre;
    n->lettre=lect->lettre;
    n->gauche=NULL;
    n->droite=NULL;
    //printf("%c est tara\n",n->lettre);

    temp->n=n;
    lect=lect->suivant;

    //printf("%c est la lettre lue\n",lect->lettre);


    while (lect!= NULL)
    {
        L_Noeud* nouv_el=malloc(sizeof(L_Noeud));
        Noeud *n= malloc(sizeof(Noeud));

        n->poids=lect->nombre;
        n->lettre=lect->lettre;
        n->gauche=NULL;
        n->droite=NULL;
        //printf("%c",n->lettre);

        nouv_el->n=n;
        //printf("%c est le cara\n",temp->n->lettre);
        temp->suivant=nouv_el;

        lect=lect->suivant;

        temp=temp->suivant;


    }

    temp->suivant=NULL;

}

void afficherListe_Noeud(L_Noeud *liste)
{
    L_Noeud* temp=liste;
    //printf("VOICI la liste des noeuds : \n");
    while (temp != NULL)
    {
        printf("'%c' = ",temp->n->lettre);
        printf("%d -> ", temp->n->poids);
        temp = temp->suivant;

    }

}


void Add_Liste_Noeud(L_Noeud **l,Noeud *n)
{
    L_Noeud*temp=*l;
    int trie=0;
    if (n->poids<temp->n->poids) //add element au debut de la liste
    {
        L_Noeud *swap=malloc(sizeof(L_Noeud)); // allouer le nouvel element
        swap->n=n;
        swap->suivant=temp;
        *l=swap;
        trie=1;

    }
    else
    {
        while ((temp->suivant!=NULL)&&(trie==0))// millieu de liste
        {
            if (n->poids < (temp->suivant->n->poids))
            {
                L_Noeud *swap=malloc(sizeof(L_Noeud));
                swap->n=n;
                swap->suivant=temp->suivant;
                temp->suivant=swap;
                trie=1;
            }
            else
                temp=temp->suivant;

        }
        if (temp->suivant==NULL) // Add l'element en fin de liste
        {
            L_Noeud *swap=malloc(sizeof(L_Noeud));
            swap->n=n;
            temp->suivant=swap;
            swap->suivant=NULL;

        }

    }


}



void trie_liste(Element * * liste){
    Element * temp = * liste;
    int boucle;
    int permut_nbr ;
    char permut_char;

    if(temp == NULL){
        return;
    }
    do{
        boucle = 0;
        temp = * liste;

        while(temp->suivant != NULL){                   //parcours toute la liste
            if(temp->nombre > temp->suivant->nombre){    // compare avec le suiv

                permut_nbr = temp->nombre;                   // on stock le suiv si il est plus petit
                permut_char = temp->lettre;

                temp->nombre = temp->suivant->nombre;
                temp->lettre = temp->suivant->lettre;

                temp->suivant->nombre = permut_nbr;
                temp->suivant->lettre = permut_char;
                boucle = 1;                             //sera = à 1 jusqu'à qu'il n'y a plus de valeur à changer

            }
            temp = temp->suivant;
        }

    }while(boucle != 0);

}

void Arbre_Huff(Element* l)
{

    L_Noeud *l_nd =malloc(sizeof(struct L_Noeud));
    creer_liste(&l_nd,l);

    L_Noeud *temp=l_nd;
    Noeud *prem=malloc(sizeof(struct Noeud));

    while (temp->suivant!=NULL)
    {
        Noeud *n= malloc(sizeof(struct Noeud));// création noeud pour le poid
        n->poids=temp->n->poids+temp->suivant->n->poids;// création noeud pour le poid
        n->lettre='\0';
        n->gauche=temp->n;
        n->droite=temp->suivant->n;
        Add_Liste_Noeud(&temp,n);// on ajoute n à la liste de noeud
        temp=temp->suivant->suivant;

        if (temp->suivant==NULL)
        {
            prem=n;
        }

    }


    //print_tree(prem);

    FILE *dico = fopen("dico.txt","w+");

    char code [30]="";

    creer_code(prem,code,dico);


    fclose(dico);
}


void print_tree(Noeud* tree)
{
    if(tree!=NULL)
    {
        printf("[%d][%c] -> [%s]\n", tree->poids, tree->lettre,tree->code);

        print_tree(tree->gauche);
        print_tree(tree->droite);

    }
}


void creer_code(Noeud *Arbre, char* code, FILE* dico) // Création du dictionnaire à partir d'un arbre donné
{
    char copie[30];

    if (Arbre!=NULL)
    {
        if ((Arbre->droite==NULL)&&(Arbre->gauche==NULL))  //feuille
        {
           printf("%s est la chaine binaire\n",code);
            fprintf(dico,"%c : %s\n",Arbre->lettre,code); // écrire dans le fichier dico le chemin
        }

        else
        {
            strcpy(copie,code);          // copie = code
            strcat(code, "0");           //concaténer les contenus de deux chaînes de caractères
            creer_code(Arbre->gauche,code,dico);         //On va à gauche = 0
            strcat(copie, "1");                          // On va à droite = 1
            creer_code(Arbre->droite,copie,dico);
        }
    }
}


void dico_binaire(FILE* dico, char caractere, char* trad,int taille)// traduire un caractere en binaire a partir du dico
{
    char caractereActuel;
    int i=0;
    if (dico != NULL)
    {
        rewind(dico);


        while ( caractere!=caractereActuel ) //on recherche le caractère dans le dico
        {
            caractereActuel = fgetc(dico);

        }
        while ((caractereActuel!='0')&&(caractereActuel!='1'))
        {
            caractereActuel=fgetc(dico);
        }
        do
        {
            trad[i]=caractereActuel;// on place le chiffre dans le tableau
            caractereActuel=fgetc(dico);
            i++;

        }while (caractereActuel!='\n');
        trad[i]='\0';
    }
}

void encodage(FILE* dico, FILE* f)// Traduire le fichier f(texte) à partir du fichier dico dans le fichier Traduction_dico(binaire)
{
    FILE* trad = fopen("Traduction_dico.txt","w+");
    char caractereActuel;

    if (f != NULL)
    {
        do
        {
            int taille=1;
            char traduction[30]="\0";
            caractereActuel = fgetc(f);

           // printf("%c est caractere actuel",caractereActuel);
            if (caractereActuel!=EOF)
            {
                dico_binaire(dico,caractereActuel,&traduction,taille);  // traduction va contenir le binaire compressé

                fputs(traduction,trad); // on écrit dans le fichier Traduction_dico

            }

        } while (caractereActuel != EOF);

    fclose(trad);
    }

}



///PARTIE 3

int is_empty(Queue* q)
{
    if(q->liste_noeud == NULL){
        return 1;
    }
    else{
        return 0;
    }
}


void enqueue(Queue * q , Noeud * val)
{

    L_Noeud * nouv_el = malloc(sizeof(L_Noeud));
    nouv_el->n = val;
    nouv_el->suivant = NULL;

    L_Noeud * temp;
    if(is_empty(q) == 0)
    {
        temp= q->liste_noeud;
        while((temp->suivant !=NULL)&&(nouv_el->n->poids)> q->liste_noeud->n->poids)
        {
            temp=temp->suivant;
        }
        nouv_el->suivant=temp->suivant;
        temp->suivant = nouv_el;
    }
    else
    {
        q->liste_noeud = nouv_el;
    }



}


Noeud* fusionner_deux_noeuds(Noeud*n1,Noeud*n2)
{
    Noeud* nouv_noeud=malloc(sizeof(Noeud));
    nouv_noeud->poids = n1->poids+ n2->poids;
    nouv_noeud->lettre='\0';
    nouv_noeud->code[0]='\0';
    nouv_noeud->gauche=n2;
    nouv_noeud->droite=n1;

    return (nouv_noeud);
}


Noeud * dequeue(Queue * q)
{

    if(is_empty(q)==0)
    {
        L_Noeud * old = q->liste_noeud;
        q->liste_noeud = q->liste_noeud->suivant;
        Noeud * res = old->n;
        free(old);
        return res;

    }
    return (NULL);
}

Noeud* Arb_Huff_queue(Noeud **tab,int taille)
{
    Queue* q1 = malloc(sizeof(Queue));
    q1->liste_noeud = Tab_to_L_Noeud(tab,taille);

    Queue* q2 = malloc(sizeof(Queue));
    q2->liste_noeud=malloc(sizeof(L_Noeud));
    q2->liste_noeud=NULL;
    Noeud* noeud_1 = malloc(sizeof(Noeud));
    Noeud* noeud_2 = malloc(sizeof(Noeud));

    //CREER LE premier Noeud
    noeud_1=dequeue(q1);
    noeud_2=dequeue(q1);


    enqueue(q2,fusionner_deux_noeuds(noeud_2,noeud_1));

    while ((is_empty(q1)!=1)||((q2->liste_noeud->suivant)!=NULL))
    {

        if ((is_empty(q1)!=1)&&(q1->liste_noeud->n->poids) <= (q2->liste_noeud->n->poids)) // On sait ici que le premier noeud de la 2eme file est plus petit
        {
            noeud_1=dequeue(q1);

            if (is_empty(q1)==0)
            {
                if ((is_empty(q1)!=1)&&(q1->liste_noeud->n->poids) <= (q2->liste_noeud->n->poids))
                {
                    noeud_2 = dequeue(q1);
                }
                else
                {
                    noeud_2 = dequeue(q2);
                }
            }
            else
                noeud_2 = dequeue(q2);
        }
        else
        {
            noeud_1=dequeue(q2);
            if (is_empty(q2)==0)
            {
                if ((is_empty(q1)!=1)&&( (q1->liste_noeud->n->poids) <= (q2->liste_noeud->n->poids)))
                {
                    noeud_2 = dequeue(q1);

                }
                else
                {
                    noeud_2 = dequeue(q2);
                }
            }
            else
                noeud_2=dequeue(q1);
        }

        enqueue(q2,fusionner_deux_noeuds(noeud_2,noeud_1));
    }
    //print_tree(q2->liste_noeud->n);

    free(q1);
    return (q2->liste_noeud->n);


}


void creer_code_v2(Noeud *Arbre, char* code,Noeud**tab) // Création du dictionnaire à partir d'un arbre donné
{
    char copie[30]="";

    if (Arbre!=NULL)
    {
        if ((Arbre->droite==NULL)&&(Arbre->gauche==NULL))  //feuille
        {
            strcpy(Arbre->code,code);// ecrire le code binaire dans la struture noeud

        }
        else
        {
            strcpy(copie,code);          // copie = code
            strcat(code, "0");           //concaténer les contenus de deux chaînes de caractères
            creer_code_v2(Arbre->gauche,code,(tab));   //On va à gauche = 0
            strcat(copie, "1");                          // On va à droite = 1
            creer_code_v2(Arbre->droite,copie,(tab));
        }
    }
}


Noeud** tab_swipe(Noeud** tab,int taille_min,int pos)
{
    for( pos--; pos>taille_min; pos--)
    {

        (tab[pos])=(tab[pos-1]);


    }
    return(tab);

}

Noeud* creer_noeud(Noeud * noeud,char lettre)
{
    (noeud)=malloc(sizeof(Noeud));
    noeud->droite=NULL;
    noeud->gauche=NULL;
    (noeud)->lettre=lettre;
    (noeud)->poids=1;

    return (noeud);
}

Noeud ** creer_2_premiers_noeud (Noeud** tab,int* taille,FILE* f) // PROBLEME 0 CARACTERE
{

    char lettre;
    lettre=fgetc(f);

    if(lettre != EOF)
    {

(*taille)=1;
tab= realloc( tab, (*taille) * sizeof(Noeud*) );

    tab[0]=creer_noeud(tab[0],lettre);
    while ((*taille)!=2)
    {
        lettre=fgetc(f);

        if (lettre==tab[0]->lettre)
        {
            tab[0]->poids++;
        }
        else
        {
            (*taille)++;

            tab= realloc( tab, (*taille) * sizeof(Noeud*) );
            if (lettre<tab[0]->lettre)
            {
                tab_swipe(tab,0,*taille);
                tab[0]=creer_noeud(tab[0],lettre);
            }
            else
            {

                tab[1]=creer_noeud(tab[1],lettre);

            }
        }


    }
    }


    return (tab);
}


Noeud** creer_tab_occur(FILE* f,int *taille)
{

    Noeud **tab = malloc(sizeof(Noeud*)*(*taille));
    char lettre;
    if (f != NULL)
    {
        tab=creer_2_premiers_noeud(tab,taille,f);
        do
        {
            lettre = fgetc(f);

            if (lettre!=-1)// Evitez le dernier carac vide du fichier
            {
                int pos=(*taille)/2; // regarde la moitie du tableau
                if (lettre >= tab[pos]->lettre)
                {
                    while ((lettre>tab[pos]->lettre)&&(pos<(*taille)-1)) // Tant que la lettre est plus grande que le carac du tab et tant que l'on ne dépasse pas le tab
                    {
                        pos++;
                    }
                    if (tab[pos]->lettre==lettre)// Si la lettre existe deja dans le tableau
                    {
                        tab[pos]->poids++;
                    }
                    else
                    {
                        (*taille)++;
                        tab= realloc( tab, (*taille) * sizeof(Noeud*) ); // Ajoute une place dans le tab afin d'ajouter un nouveau noeud
                        if (lettre>tab[pos]->lettre)
                        {
                            pos++;
                        }
                        else
                        {
                            tab=tab_swipe(tab,pos,*taille);// déplacer le tab afin d'insérer au milieu un nouveua noeud
                        }
                        tab[pos]=creer_noeud(tab[pos],lettre);// creer le noeud
                    }
                }
                else
                {
                    while ((lettre<tab[pos]->lettre)&&(pos>0))// même conditions que la premiere boucle while mais inverse vu qu'on s'interresse ici à la gauche du tab
                    {
                        pos--;
                    }
                    if (tab[pos]->lettre==lettre)
                    {
                        tab[pos]->poids++;
                    }
                    else
                    {
                        (*taille)++;
                        tab= realloc( tab, (*taille) * sizeof(Noeud*) );
                        if (lettre>tab[pos]->lettre)
                        {
                            pos++;
                        }
                        tab=tab_swipe(tab,pos,*taille);// déplacer le tab afin d'insérer au milieu un nouveua noeud
                        tab[pos]=creer_noeud(tab[pos],lettre);
                    }
                }
            }
        } while (lettre != EOF);

    }
    return(tab);

}


void quick_sort(Noeud*** tab, int debut, int fin)
{
   int i;
   int j;
   int pivot;
   Noeud* temp = NULL;

    if (debut < fin)
    {
        pivot = debut;
        i = debut;
        j = fin;

        //on va faire en sorte que tous les éléments sous le pivot soit < et le reste >
        //la plus grande valeur deviendra le pivot
        while (i < j)
        {
            while ((*tab)[i]->poids <= (*tab)[pivot]->poids && (i < fin)){
                i++;
            }
            while ((*tab)[j]->poids > (*tab)[pivot]->poids)
            {
                j--;
            }
            if (i < j){
                temp = (*tab)[i];
                (*tab)[i] = (*tab)[j];
                (*tab)[j] = temp;
            }
        }
        temp = (*tab)[pivot];
        (*tab)[pivot] = (*tab)[j];
        (*tab)[j] = temp; //le pivot a été déplacé


        quick_sort(tab, debut,j-1);
        quick_sort(tab,j+1, fin);
    }
}


void Afficher_tab(int taille, Noeud**tab)
{
    int i=0;
    int somme=0;
    while (i<taille)
    {
        printf("tab [%d] : %c = ",i,tab[i]->lettre);
        printf("%d\n", tab[i]->poids);
        somme=somme+ tab[i]->poids;
        i++;
    }
    printf("%d est la somme",somme);
}



L_Noeud * Tab_to_L_Noeud(Noeud ** tab , int nbre_chara_diff )
{
    L_Noeud* list =NULL;
    L_Noeud * temp=NULL;
    int i=0;



    if(tab[i]!=NULL)
    {
        list= malloc(sizeof(L_Noeud));
        temp=list;
        while(i<nbre_chara_diff-1)
        {
            temp->n = tab[i];
            temp->suivant = malloc(sizeof(L_Noeud));
            temp=temp->suivant;
            i++;
        }
        temp->n=tab[i];



  }
  temp->suivant=NULL;
    return (list);
}


char* code_dans_avl (char lettre, Noeud*avl)
{
    if (lettre==avl->lettre)
    {
        //printf("%s est le code renvoye\n",avl->code);
        return (avl->code);
    }
    else
    {
        if (lettre<avl->lettre)
            code_dans_avl(lettre,avl->gauche);
        else
            code_dans_avl(lettre,avl->droite);
    }

}

void encodage_avl(FILE* f, Noeud*avl)
{
    FILE* trad = fopen("Traduction_dico.txt","w+");
    char caractereActuel;
   // printf("ENCODAGE");
    if (f != NULL)
    {
        do
        {
            char traduction[30]="\0";
            caractereActuel = fgetc(f);
           // printf("%c est caracatere\n",caractereActuel);
           // printf("ENCODAGE");
            if (caractereActuel!=EOF)
            {
                strcpy(traduction,code_dans_avl(caractereActuel,avl));
                fputs(traduction,trad);
                free(trad);

            }

        } while (caractereActuel != EOF);

    fclose(trad);
    }

}

void free_tree(Noeud** tree){
    if(tree != NULL){
        free_tree((*tree)->gauche);
        free_tree((*tree)->droite);
        free(*tree);
    }
}

void decodage_avl(Noeud*avl)
{
    FILE* trad = fopen("Decodage.txt","w+");
    FILE* f = fopen("Traduction_dico.txt","r");
    if (trad != NULL)
    {
        char caractereActuel;
        char* traduction=malloc(sizeof(char)*30);
        traduction[0]='\0';
        int i=0;
        char lettre='\0';
        do
        {

            caractereActuel= fgetc(f) ;

            if (caractereActuel!=EOF)
            {

                traduction[i] = caractereActuel;
                i++;
                traduction[i]='\0';
                if (chercher_lettre_avl(avl,traduction,&lettre)==1)
                {
                    fputc(lettre,trad);
                    i=0;
                    free(traduction);

                }
            }




        }while (caractereActuel!=EOF);


    }

    fclose(f);
    fclose(trad);
}


int chercher_lettre_avl(Noeud *avl,char* code, char* lettre)
{

    if (avl!=NULL)
    {
        if (strcmp(code,avl->code)==0)
        {
            (*lettre)=avl->lettre;
            return 1;
        }
        else
        {
                return (chercher_lettre_avl(avl->gauche,code,lettre)||chercher_lettre_avl(avl->droite,code,lettre));


        }
    }
    else
        return 0;
}
