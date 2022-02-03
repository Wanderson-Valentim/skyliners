#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "Pilha.h"
#include "Lista.h"
#include "funcoes.h"

//VALOR PEÇAS: PARQUE - 0, TETO - 1, ANDAR - 2.


Pilha*** criar_tabuleiro(int tam_tabuleiro){
    Pilha ***tabuleiro;
    tabuleiro = (Pilha***) malloc (tam_tabuleiro * sizeof(Pilha**));
    if(tabuleiro!=NULL){
        for(int i = 0; i < tam_tabuleiro; i++){
            tabuleiro[i] = (Pilha**) malloc (tam_tabuleiro * sizeof(Pilha*));
            for(int j = 0; j < tam_tabuleiro; j++){
                tabuleiro[i][j] = criar_pilha();
            }
        }
    }
    return tabuleiro;
}

void destruir_tabuleiro(Pilha ***tabuleiro, int tam_tabuleiro){
    if(tabuleiro!=NULL){
        for(int i = 0; i < tam_tabuleiro; i++){
            for(int j = 0; j < tam_tabuleiro; j++){
                destruir_pilha(tabuleiro[i][j]);
            }
            free(tabuleiro[i]);
        }
    }
}

void imprime_tabuleiro(Pilha ***tabuleiro, int tamanho_tab){
    for(int x=0; x < 3; x++){
        for(int w=0; w < (tamanho_tab*3)+2; w++){
            printf(" ");
        }
        if(x==1){
            printf("| SKYLINERS |\n");
        }
        else{
            printf("+-----------+\n");
        }
    }

    int letra=97,cont1=0,cont2=0,cont3=0,tam,v_peca,valor_pec;
    printf("\n");
    for(int k=0; k < (tamanho_tab*3)+6; k++){
        printf(" ");
    }
    printf("NORTE\n\n");
    for(int i=0; i < (tamanho_tab*2)+2; i++){
        cont2=0;
        if(i==tamanho_tab){
            printf(" OESTE");
        }
        if(i%2==0){
            printf(" \t");
            int cont=0;
            for(int z=0; z < tamanho_tab; z++){
                if(cont==0){
                    printf("+-----+");
                    cont++;
                }
                else{
                    printf("-----");
                    cont=0;
                }
            }
            printf("\n");
        }
        else if(i==(tamanho_tab*2)+1){
            printf(" \t");
            int conta=0;
            for(int y=0; y < tamanho_tab; y++){
                if(conta==0){
                    printf("   %d",y+1);
                    conta++;
                }
                else if(y > 9){
                    printf("    %d",y+1);
                }
                else{
                    printf("     %d",y+1);
                }
            }
            printf("\n\n");
            for(int b=0; b < (tamanho_tab*3)+7; b++){
                printf(" ");
            }
            printf("SUL\n");
        }

        else{
            printf(" \t");
            for(int j=0; j < (tamanho_tab*6)+2; j++){
                if(cont2 < tamanho_tab){
                    tam = tamanho_pilha(tabuleiro[cont1][cont2]);
                    if(j%2!=0 && j%3!=0 && tam!=0){
                        v_peca = acessar_pilha(tabuleiro[cont1][cont2],&valor_pec);
                        if(v_peca!=0){
                            if(valor_pec==0 || valor_pec==1){
                                if(cont3==0){
                                    printf("]");
                                }
                                else{
                                    printf("[");
                                    cont3=0;
                                }
                            }
                            else{
                                printf(" ");
                            }
                        }
                    }
                    else if(j==0){
                        printf("|");
                        cont3++;
                    }
                    else if(j > 0 && j%6==0){
                        printf("|");
                        cont2++;
                        cont3++;
                    }

                    else if(j > 0 && j%3==0){
                        if(tam==0){
                            printf(" ");
                        }
                        else{
                            printf("%d",tam);
                        }
                    }
                    else{
                        printf(" ");
                    }
                }
                else{
                    printf(" %c",letra);
                    letra++;
                }
            }
            cont1++;
            if(i!=tamanho_tab){
                printf("\n");
            }
        }
        if(i==tamanho_tab){
            printf("   LESTE\n");
        }
    }
}

void aleatorio(Pilha ***tabuleiro, int meio){
    int num_linha, num_coluna, num=2;
    srand(time(NULL));

    for(int i=0; i < 6; i++){
        num_linha=rand()%3;
        num_coluna=rand()%3;

        num_linha+=(meio-1);
        num_coluna+=(meio-1);
        if(num_coluna==meio && num_coluna==num_linha){
            i=i-1;
        }
        else{
            inserir_pilha(tabuleiro[num_linha][num_coluna],num);
        }
    }
}


//Retorna 1 se for possivel colocar a peça e 0 caso contrário.
int validar_peca(Pilha ***tabuleiro, int linha, int coluna, int valor_peca){
    int acessa;
    //Se for PARQUE
    if(valor_peca==0){
        if(vazia_pilha(tabuleiro[linha][coluna])){
            return 1;
        }
        else{
            return 0;
        }
    }
    //Se for TETO
    else if(valor_peca==1){
        if(vazia_pilha(tabuleiro[linha][coluna])){
            return 0;
        }
        else{
            acessar_pilha(tabuleiro[linha][coluna],&acessa);
            if(acessa==0){
                return 0;
            }
            else if(acessa==1){
                return 0;
            }
            else if (acessa==2){
                return 1;
            }
        }
    }
    //Se for ANDAR
    else{
        if(vazia_pilha(tabuleiro[linha][coluna])){
            return 1;
        }
        else{
            acessar_pilha(tabuleiro[linha][coluna],&acessa);
            if(acessa==0){
                return 0;
            }
            else if(acessa==1){
                return 0;
            }
            else if (acessa==2){
                return 1;
            }
        }
    }
    return 0;
}

void adiciona_pecas_lista(Lista* lista_pecas, int qtd_parque, int qtd_teto, int qtd_andar){
    if(qtd_parque!=0){
        for(int i=0; i < qtd_parque; i++){
            inserirMeio(lista_pecas,0);
        }
    }
    if(qtd_teto!=0){
        for(int i=0; i < qtd_teto; i++){
            inserirMeio(lista_pecas,1);
        }
    }
    if(qtd_andar!=0){
        for(int i=0; i < qtd_andar; i++){
            inserirMeio(lista_pecas,2);
        }
    }
}

int valida_coordenada(Pilha ***tabuleiro, int tam, char coordenada[10], int v_peca){
    int cont1=0, cont2=0, letra=97, numero=49, let=0, num=0;
    for(int i=0; i<tam; i++){
        let++;
        if(coordenada[0]==letra){
            cont1++;
            break;
        }
        letra++;
    }
    for(int j=0; j<tam; j++){
        num++;
        if(coordenada[1]==numero){
            cont2++;
            break;
        }
        numero++;
    }
    if(cont1==1 && cont2==1){
        if(validar_peca(tabuleiro,let-1,num-1,v_peca)){
            inserir_pilha(tabuleiro[let-1][num-1],v_peca);
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
}

int conta_item_lista(Lista *lista, int pec){
    if(vazia_lista(lista))return 0;
    else{
        int cont=0, v, tam;
        tam=tamanho_lista(lista);
        for(int i=0; i < tam; i++){
            acessarIndice(lista,i,&v);
            if(v==pec){
                cont++;
            }
        }
        return cont;
    }
}

int conta_pontos(Pilha*** tabuleiro, int tamanho_tab, int num_jogador){
    int tam_pilha, contador=0, pontos=0, maior=0;
    //Vista do SUL.
    if(num_jogador==1){
        for(int j=0; j < tamanho_tab; j++){
            for(int i=tamanho_tab-1; i > -1; i--){
                tam_pilha = tamanho_pilha(tabuleiro[i][j]);
                if(tam_pilha > maior){
                    maior=tam_pilha;
                    contador++;
                }
            }
            pontos += contador;
            contador=0;
            maior=0;
        }
        return pontos;
    }

    //Vista do OESTE.
    else if(num_jogador==2){
        for(int i=0; i < tamanho_tab; i++){
            for(int j=0; j < tamanho_tab; j++){
                tam_pilha = tamanho_pilha(tabuleiro[i][j]);
                if(tam_pilha > maior){
                    maior=tam_pilha;
                    contador++;
                }
            }
            pontos += contador;
            contador=0;
            maior=0;
        }
        return pontos;
    }


    //Vista do NORTE.
    else if(num_jogador==3){
        for(int j=0; j < tamanho_tab; j++){
            for(int i=0; i < tamanho_tab; i++){
                tam_pilha = tamanho_pilha(tabuleiro[i][j]);
                if(tam_pilha > maior){
                    maior=tam_pilha;
                    contador++;
                }
            }
            pontos += contador;
            contador=0;
            maior=0;
        }
        return pontos;
    }

    //Vista do LESTE
    else{
        for(int i=0; i < tamanho_tab; i++){
            for(int j=tamanho_tab-1; j >=0; j--){
                tam_pilha = tamanho_pilha(tabuleiro[i][j]);
                if(tam_pilha > maior){
                    maior=tam_pilha;
                    contador++;
                }
            }
            pontos += contador;
            contador=0;
            maior=0;
        }
        return pontos;
    }
}

int maior_predio_tab(Pilha*** tabuleiro, int tamanho_tab){
    int maior=0, tam_pilha;
    for(int i=0; i < tamanho_tab; i++){
        for(int j=0; j < tamanho_tab; j++){
            tam_pilha = tamanho_pilha(tabuleiro[i][j]);
            if(tam_pilha > maior) maior=tam_pilha;
        }
    }
    return maior;
}

void limpaString(char* str, int LARGURAMAX){
    for(int i = 0; i < LARGURAMAX; i++){
        str[i] = ' ';
    }
}

void adicionaProfundidade(char* str, int tamanho){
    int meio = tamanho / 2;
    for(int i = 0; i < tamanho - 1; i++){
        if(str[i] == '#' && str[i+1] == ' '){
            str[i+1] = '#';
            return;
        }
        else if((str[i] == ' ' && str[i + 1] == '#' ) || (i == meio - 1)){
            str[i] = '#';
        }
    }
}

void addLinha(char* matriz, char* str, int pos, int predio, int LARGURAMAX, int tamanho_tab){
    for(int i = 0; i < LARGURAMAX; i++){
        matriz[pos * (LARGURAMAX * tamanho_tab + 1) + i + (predio*tamanho_tab*2)] = str[i];
    }
}

void imprime_vista(Pilha*** tabuleiro, int tamanho_tab, int jogador){
    int ALTURAMAX = maior_predio_tab(tabuleiro, tamanho_tab), LARGURAMAX = tamanho_tab*2, tam_predio, matriz_inverte[tamanho_tab][tamanho_tab];

    char str[LARGURAMAX];

    for(int i=0; i < LARGURAMAX; i++){
        if(i == LARGURAMAX-1){
            str[i] = '\n';
        }
        else{
            str[i] = ' ';
        }
    }

    char matrizStr[ALTURAMAX][(LARGURAMAX * tamanho_tab )+ 1];

    for(int i = 0; i < ALTURAMAX; i++){
        for(int j = 0; j < LARGURAMAX * tamanho_tab + 1; j++){
            if(j == LARGURAMAX * tamanho_tab){
                matrizStr[i][j] = '\n';
            }
            else{
                matrizStr[i][j] = ' ';
            }
        }
    }

    //VISTA SUL
    if(jogador==1){
        for(int i = 0; i < tamanho_tab; i++){
            limpaString(str, LARGURAMAX);
            for(int j = 0; j < tamanho_tab; j++){
                adicionaProfundidade(str, LARGURAMAX);
                for(int k = ALTURAMAX-1; k > -1; k--){
                    tam_predio = tamanho_pilha(tabuleiro[j][i]);
                    if(k >= ALTURAMAX - tam_predio){
                        addLinha(matrizStr, str, k, i, LARGURAMAX, tamanho_tab);
                    }
                }
            }
        }
        printf("%s",matrizStr);
    }
    //VISTA OESTE
    else if(jogador==2){
        for(int i = 0; i < tamanho_tab; i++){
            limpaString(str, LARGURAMAX);
            for(int j = tamanho_tab-1; j > -1; j--){
                adicionaProfundidade(str, LARGURAMAX);
                for(int k = ALTURAMAX-1; k > -1; k--){
                    tam_predio = tamanho_pilha(tabuleiro[i][j]);
                    if(k >= ALTURAMAX - tam_predio){
                        addLinha(matrizStr, str, k, i, LARGURAMAX, tamanho_tab);
                    }
                }
            }
        }
        printf("%s",matrizStr);
    }
    //VISTA NORTE
    else if(jogador==3){
        for(int i=0, linha = tamanho_tab-1; i < tamanho_tab, linha > -1; i++, linha--){
            for(int j=0, coluna = tamanho_tab-1; j < tamanho_tab, coluna > -1; j++, coluna--){
                matriz_inverte[j][i] = tamanho_pilha(tabuleiro[coluna][linha]);
            }
        }
        for(int i = 0; i < tamanho_tab; i++){
            limpaString(str, LARGURAMAX);
            for(int j = 0; j < tamanho_tab; j++){
                adicionaProfundidade(str, LARGURAMAX);
                for(int k = ALTURAMAX-1; k > -1; k--){
                    tam_predio = matriz_inverte[j][i];
                    if(k >= ALTURAMAX - tam_predio){
                        addLinha(matrizStr, str, k, i, LARGURAMAX, tamanho_tab);
                    }
                }
            }
        }
        printf("%s",matrizStr);
    }
    //VISTA LESTE
    else{
        for(int i=0, linha = tamanho_tab-1; i < tamanho_tab, linha > -1; i++, linha--){
            for(int j=0, coluna = 0; j < tamanho_tab, coluna < tamanho_tab; j++, coluna++){
                matriz_inverte[j][i] = tamanho_pilha(tabuleiro[linha][coluna]);
            }
        }
        for(int i = 0; i < tamanho_tab; i++){
            limpaString(str, LARGURAMAX);
            for(int j = 0; j < tamanho_tab; j++){
                adicionaProfundidade(str, LARGURAMAX);
                for(int k = ALTURAMAX-1; k > -1; k--){
                    tam_predio =  matriz_inverte[j][i];
                    if(k >= ALTURAMAX - tam_predio){
                        addLinha(matrizStr, str, k, i, LARGURAMAX, tamanho_tab);
                    }
                }
            }
        }
        printf("%s",matrizStr);
    }
}
