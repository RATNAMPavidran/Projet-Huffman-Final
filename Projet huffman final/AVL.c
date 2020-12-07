#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"
#include <string.h>

void add_noeud_avl(Noeud **avl, Noeud *noeud)
{
    if ((*avl) ==NULL)
    {

        (*avl)=noeud;
    }
    else
    {

        if ((*avl)->lettre > noeud->lettre)
        {
            add_noeud_avl(&((*avl)->gauche) , noeud);
        }
        else if((*avl)->lettre < noeud->lettre)
        {


            add_noeud_avl(&((*avl)->droite), noeud);
        }
    }

}


int depth(Noeud* tree)
{
    if(tree == NULL){
        return 0;//Attention définition. -1 ou 0
    }
    else{
        int depth_left = depth(tree->gauche);
        int depth_right = depth(tree->droite);
        if(depth_left > depth_right){
            return 1 + depth_left;
        }
        else{
            return 1 + depth_right;
        }
    }
}


int bf(Noeud* tree)
{
    if(tree == NULL) {
        return 0;
    }
    else{
        return depth(tree->droite) - depth(tree->gauche);
    }
}

void right_rotation(Noeud** tree){
    if (*tree != NULL){
        Noeud* temp = (*tree)->gauche;
        (*tree)->gauche = temp->droite;
        temp->droite = *tree;
        *tree = temp;
    }
}

void left_rotation(Noeud** tree){
    if (*tree != NULL){
        Noeud* temp = (*tree)->droite;
        (*tree)->droite = temp->gauche;
        temp->gauche = *tree;
        *tree = temp;
    }
}

void balance(Noeud** tree){
    if (*tree != NULL){
        balance(&((*tree)->gauche));// Postfix
        balance(&((*tree)->droite));

        int balance_factor = bf(*tree);
        if (balance_factor <= -2){// Cas Gauche - ??
            if(bf((*tree)->gauche) > 0){// Gauche - Droite
                left_rotation(&((*tree)->gauche));
            }
            right_rotation(tree);// Gauche - Gauche
        }
        else if (balance_factor >= 2){// Cas Droite - ??
            if(bf((*tree)->droite) < 0){// Droite - Gauche
                right_rotation(&((*tree)->droite));
            }
            left_rotation(tree);// Droite - Droite
        }
    }
}

Noeud* creer_avl(Noeud**tab, int taille )
{
    Noeud *avl=malloc(sizeof(Noeud));
    avl=NULL;
    for(int i=0;i<taille;i++)
    {
        //printf("%c est la carac  %d est i \n",tab[i]->lettre,i);
        add_noeud_avl(&avl,tab[i]);
        balance(&avl);
    }
    return(avl);
}
