struct aluno {
    int matricula;
    char nome[50];
    float av1;
    float av2;
    float pr;
};
typedef struct elemento *Lista;

Lista* criar();
void destruir(Lista *);
int tamanho(Lista *);
int vazia(Lista *);
int inserirFim(Lista *, struct aluno);
int inserirInicio(Lista *lse, struct aluno);
int inserirMeio(Lista *, struct aluno);
int removerFim(Lista *);
int removerInicio(Lista *);
int removerMeio(Lista *, int);
int acessarIndice(Lista *, int, struct aluno *);
int acessarValor(Lista *, int, struct aluno *);
