#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

struct element {
    int valor_peca;
    struct element *prox;
};

typedef struct element Element;

Lista* criar_lista(){
    Lista *l;
    l=(Lista*)malloc(sizeof(Lista));
    if(l!=NULL){
        *l=NULL;
    }
    return l;
}

void destruir_lista(Lista *l){
    if(l!=NULL){
        Element *aux;
        while(*l!=NULL){
            aux=*l;
            *l=(*l)->prox;
            free(aux);
        }
    }
}

int tamanho_lista(Lista *l){
    if(vazia_lista(l))return 0;
    else{
        int cont=0;
        Element *aux=*l;
        while(aux!=NULL){
            cont++;
            aux=aux->prox;
        }
        return cont;
    }
}

int vazia_lista(Lista *l){
    if(l==NULL)return 1;
    else if(*l==NULL)return 1;
    else return 0;
}

int inserirMeio(Lista *l, int peca){
    if(l==NULL)return 0;
    else{
        Element *novo=(Element*)malloc(sizeof(Element));
        if(novo==NULL)return 0;
        novo->valor_peca=peca;
        if(vazia_lista(l) || (*l)->valor_peca > novo->valor_peca){
            novo->prox=*l;
            *l=novo;
        }
        else{
            Element *ant=*l;
            Element *aux=ant->prox;
            while(aux!=NULL && aux->valor_peca < novo->valor_peca){
                ant=aux;
                aux=aux->prox;
            }
            ant->prox=novo;
            novo->prox=aux;
        }
        return 1;
    }
}

int removerMeio(Lista *l, int peca){
    if(vazia_lista(l))return 0;
    else if((*l)->valor_peca == peca){
        Element *aux=*l;
        *l=aux->prox;
        free(aux);
        return 1;
    }
    else{
        Element *ant=*l;
        Element *aux=ant->prox;
        while(aux!=NULL && aux->valor_peca != peca){
            ant=aux;
            aux=aux->prox;
        }
        if(aux==NULL) return 0;
        ant->prox = aux->prox;
        free(aux);
        return 1;
    }
}

int acessarValor(Lista *l, int v, int *peca){
    if(vazia_lista(l))return 0;
    else{
        Element *aux=*l;
        while(aux!=NULL && aux->valor_peca != v){
            aux=aux->prox;
        }
        if(aux==NULL) return 0;
        *peca=(*l)->valor_peca;
        return 1;
    }
}

int acessarIndice(Lista *l, int pos, int *peca){
    if (vazia_lista(l))return 0;
    else if (pos < 0)return 0;
    else {
        int cont = 0;
        Element *aux = *l;
        while (aux != NULL && pos != cont) {
            aux = aux->prox;
            cont++;
        }
        if (aux == NULL) return 0;
        *peca = aux->valor_peca;
        return 1;
    }
}
