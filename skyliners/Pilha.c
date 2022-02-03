#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"

struct elemento{
    int pec;
    struct elemento *prox;
};

typedef struct elemento Elemento;

Pilha* criar_pilha(){
    Pilha *p;
    p=(Pilha*)malloc(sizeof(Pilha));
    if(p!=NULL){
        *p=NULL;
    }
    return p;
}

void destruir_pilha(Pilha *p){
    if(p!=NULL){
        Elemento *aux;
        while(*p!=NULL){
            aux=*p;
            *p=(*p)->prox;
            free(aux);
        }
    }
}

int tamanho_pilha(Pilha *p){
    if(vazia_pilha(p))return 0;

    int cont=0;
    Elemento *aux=*p;
    while(aux!=NULL){
        cont++;
        aux=aux->prox;
    }
    return cont;
}

int vazia_pilha(Pilha *p){
    if(p==NULL)return 1;
    else if(*p==NULL)return 1;
    else return 0;
}

int inserir_pilha(Pilha *p, int nova_pec){
    if(p==NULL)return 0;
    else{
        Elemento *novo=(Elemento*)malloc(sizeof(Elemento));
        if(novo==NULL)return 0;
        novo->pec=nova_pec;
        novo->prox=*p;
        *p=novo;
        return 1;
    }
}

int remover_pilha(Pilha *p){
    if(vazia_pilha(p))return 0;
    else{
        Elemento *aux=*p;
        *p=aux->prox;
        free(aux);
        return 1;
    }
}

int acessar_pilha(Pilha *p, int *pec){
   if(vazia_pilha(p))return 0;
    else{
        *pec=(*p)->pec;
        return 1;
    }
}
