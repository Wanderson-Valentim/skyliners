#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <string.h>
#include <locale.h>
#include "Pilha.h"
#include "Lista.h"
#include "funcoes.h"

int escolha_peca(Lista*, int);
void escolha_coordenada(Pilha***, Lista*, int, int);
void jogadores(Lista*, int);


//VALOR PEÇAS: PARQUE - 1, TETO - 2, ANDAR - 3.

int main(){
    setlocale(LC_ALL, "Portuguese");
    Pilha ***tabuleiro;

    Lista *jogador1_sul, *jogador2_oeste, *jogador3_norte, *jogador4_leste;

    int repete=1, meio, tamanho_tabuleiro=5, cont_jogador=1, pec, cont_rodada=1, cont_lista, encerra_rodada=0, pontos, maior=0, ganhador;

    jogador1_sul=criar_lista();
    jogador2_oeste=criar_lista();
    jogador3_norte=criar_lista();
    jogador4_leste=criar_lista();

    tabuleiro=criar_tabuleiro(tamanho_tabuleiro);
    meio=(tamanho_tabuleiro - 1)/2;

    inserir_pilha(tabuleiro[meio][meio],0);

    aleatorio(tabuleiro, meio);

    adiciona_pecas_lista(jogador1_sul,1,2,12);
    adiciona_pecas_lista(jogador2_oeste,1,2,12);
    adiciona_pecas_lista(jogador3_norte,1,2,12);
    adiciona_pecas_lista(jogador4_leste,1,2,12);

    while(repete){
        imprime_tabuleiro(tabuleiro,tamanho_tabuleiro);
        if(encerra_rodada > 0){
            printf("\n      +---------------+\n");
            printf("      | ÚLTIMA RODADA |\n");
            printf("      +---------------+\n");
        }
        printf("\n         %dª RODADA!",cont_rodada);

        if(cont_jogador==1){
            jogadores(jogador1_sul,cont_jogador);
            pec=escolha_peca(jogador1_sul,tamanho_tabuleiro);
            while(pec == 4){
                system("cls");
                imprime_tabuleiro(tabuleiro,tamanho_tabuleiro);
                printf("\n         %dª RODADA!",cont_rodada);
                jogadores(jogador1_sul,cont_jogador);
                printf("\n");
                imprime_vista(tabuleiro,tamanho_tabuleiro,1);
                printf("--------------------------------------------------");
                pontos = conta_pontos(tabuleiro, tamanho_tabuleiro, 1);
                printf("\n            Você possui %d pontos!\n",pontos);
                pec=escolha_peca(jogador1_sul,tamanho_tabuleiro);
            }
            escolha_coordenada(tabuleiro,jogador1_sul,tamanho_tabuleiro,pec-1);
            cont_lista=conta_item_lista(jogador1_sul,2);
            if(cont_lista==0)encerra_rodada++;
            cont_jogador++;
        }
        else if(cont_jogador==2){
            jogadores(jogador2_oeste,cont_jogador);
            pec=escolha_peca(jogador2_oeste,tamanho_tabuleiro);
            while(pec == 4){
                system("cls");
                imprime_tabuleiro(tabuleiro,tamanho_tabuleiro);
                printf("\n         %dª RODADA!",cont_rodada);
                jogadores(jogador2_oeste,cont_jogador);
                printf("\n");
                imprime_vista(tabuleiro, tamanho_tabuleiro, 2);
                printf("--------------------------------------------------");
                pontos = conta_pontos(tabuleiro, tamanho_tabuleiro, 2);
                printf("\n            Você possui %d pontos!\n",pontos);
                pec=escolha_peca(jogador2_oeste,tamanho_tabuleiro);
            }
            escolha_coordenada(tabuleiro,jogador2_oeste,tamanho_tabuleiro,pec-1);
            cont_lista=conta_item_lista(jogador2_oeste,2);
            if(cont_lista==0)encerra_rodada++;
            cont_jogador++;
        }
        else if(cont_jogador==3){
            jogadores(jogador3_norte,cont_jogador);
            pec=escolha_peca(jogador3_norte,tamanho_tabuleiro);
            while(pec == 4){
                system("cls");
                imprime_tabuleiro(tabuleiro,tamanho_tabuleiro);
                printf("\n         %dª RODADA!",cont_rodada);
                jogadores(jogador3_norte,cont_jogador);
                printf("\n");
                imprime_vista(tabuleiro,tamanho_tabuleiro,3);
                printf("--------------------------------------------------");
                pontos = conta_pontos(tabuleiro, tamanho_tabuleiro, 3);
                printf("\n            Você possui %d pontos!\n",pontos);
                pec=escolha_peca(jogador3_norte,tamanho_tabuleiro);
            }
            escolha_coordenada(tabuleiro,jogador3_norte,tamanho_tabuleiro,pec-1);
            cont_lista=conta_item_lista(jogador3_norte,2);
            if(cont_lista==0)encerra_rodada++;
            cont_jogador++;
        }
        else if(cont_jogador==4){
            jogadores(jogador4_leste,cont_jogador);
            pec=escolha_peca(jogador4_leste,tamanho_tabuleiro);
            while(pec == 4){
                system("cls");
                imprime_tabuleiro(tabuleiro,tamanho_tabuleiro);
                printf("\n         %dª RODADA!",cont_rodada);
                jogadores(jogador4_leste,cont_jogador);
                printf("\n");
                imprime_vista(tabuleiro,tamanho_tabuleiro,4);
                printf("--------------------------------------------------");
                pontos = conta_pontos(tabuleiro, tamanho_tabuleiro, 4);
                printf("\n            Você possui %d pontos!\n",pontos);
                pec=escolha_peca(jogador4_leste,tamanho_tabuleiro);
            }
            escolha_coordenada(tabuleiro,jogador4_leste,tamanho_tabuleiro,pec-1);
            cont_lista=conta_item_lista(jogador4_leste,2);
            if(cont_lista==0)encerra_rodada++;
            if(encerra_rodada > 0){
                repete=0;
            }
            else{
                cont_rodada++;
                cont_jogador=1;
            }
        }
        system("cls");
    }

    imprime_tabuleiro(tabuleiro, tamanho_tabuleiro);
    for(int i=1; i < 5; i++){
        pontos = conta_pontos(tabuleiro, tamanho_tabuleiro, i);
        if(pontos > maior){
            maior = pontos;
            ganhador = i;
        }
    }
    if(ganhador == 1){
        pontos = conta_pontos(tabuleiro, tamanho_tabuleiro, 1);
        printf("\n O GANHADOR FOI O JOGADOR DA VISTA SUL, COM %d PONTOS!\n", pontos);
        printf("\n");
        imprime_vista(tabuleiro,tamanho_tabuleiro,1);
        printf("--------------------------------------------------");
    }
    else if(ganhador == 2){
        pontos = conta_pontos(tabuleiro, tamanho_tabuleiro, 2);
        printf("\n O GANHADOR FOI O JOGADOR DA VISTA OESTE, COM %d PONTOS!\n", pontos);
        printf("\n");
        imprime_vista(tabuleiro,tamanho_tabuleiro,2);
        printf("--------------------------------------------------");
    }
    else if(ganhador == 3){
        pontos = conta_pontos(tabuleiro, tamanho_tabuleiro, 3);
        printf("\n O GANHADOR FOI O JOGADOR DA VISTA NORTE, COM %d PONTOS!\n", pontos);
        printf("\n");
        imprime_vista(tabuleiro,tamanho_tabuleiro,3);
        printf("--------------------------------------------------");
    }
    else{
        pontos = conta_pontos(tabuleiro, tamanho_tabuleiro, 4);
        printf("\n O GANHADOR FOI O JOGADOR DA VISTA LESTE, COM %d PONTOS!\n", pontos);
        printf("\n");
        imprime_vista(tabuleiro,tamanho_tabuleiro,4);
        printf("--------------------------------------------------");
    }

    destruir_lista(jogador1_sul);
    destruir_lista(jogador2_oeste);
    destruir_lista(jogador3_norte);
    destruir_lista(jogador4_leste);
    destruir_tabuleiro(tabuleiro, tamanho_tabuleiro);

    return 0;
}

int escolha_peca(Lista* lista , int tam_tabuleiro){
    int rep=1, cont_list=0, num, tam_opc;
    char opc[10];
    while(rep){
        printf("\n  Escolha qual peça deseja jogar \n  -> ");
        gets(opc);
        tam_opc = strlen(opc);
        if(tam_opc == 1){
            if(opc[0] < 49 || opc[0] > 52){
                printf("\n  Peça Inválida!\n");
            }
            else{
                if(opc[0]=='1'){
                    cont_list=conta_item_lista(lista,0);
                }
                else if(opc[0]=='2'){
                    cont_list=conta_item_lista(lista,1);
                }
                else if(opc[0]=='3'){
                    cont_list=conta_item_lista(lista,2);
                }
                else{
                    num = opc[0]-48;
                    return num;
                }

                if(cont_list==0){
                    printf("\n  Você não possui mais peças desse tipo!\n");
                }
                else{
                    rep=0;
                }
            }
        }
        else{
            printf("\n  Peça Inválida!\n");
        }
    }
    num = opc[0]-48;
    return num;
}

void escolha_coordenada(Pilha ***tabuleiro, Lista* lista , int tam_tabuleiro, int peca){
    char coordenada[10];
    int repete=1, tam_coordenada;
    while(repete){
        printf("\n  Escolha onde jogar\n  -> ");
        setbuf(stdin, NULL);
        gets(coordenada);
        tam_coordenada=strlen(coordenada);
        if(tam_coordenada==2){
            int v = valida_coordenada(tabuleiro, tam_tabuleiro, coordenada, peca);
            if(v==1){
                removerMeio(lista, peca);
                repete=0;
            }
            else{
                printf("\n  Coordenada Inválida!\n");
            }
        }
        else{
            printf("\n  Coordenada Inválida!\n");
        }
    }
}


//1 - Jogador SUL, 2 - Jogador OESTE, 3 - Jogador NORTE, 4 - Jogador LESTE.
void jogadores(Lista *lista, int num_jogador){
    switch(num_jogador){
        case 1:
            printf("\n  VEZ DO JOGADOR DO LADO SUL\n");
            break;
        case 2:
            printf("\n  VEZ DO JOGADOR DO LADO OESTE\n");
            break;
        case 3:
            printf("\n  VEZ DO JOGADOR DO LADO NORTE\n");
            break;
        case 4:
            printf("\n  VEZ DO JOGADOR DO LADO LESTE\n");
            break;
    }
    printf("\n         SUAS OPÇÕES:\n");
    printf("        1 - Parque [%d]\n",conta_item_lista(lista,0));
    printf("        2 - Teto   [%d]\n",conta_item_lista(lista,1));
    printf("        3 - Andar  [%d]\n",conta_item_lista(lista,2));
    printf("        4 - Sua Vista\n");
}

