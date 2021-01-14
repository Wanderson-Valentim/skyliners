typedef struct element *Lista;

Lista* criar_lista();

void destruir_lista(Lista *);

int tamanho_lista(Lista *);

int vazia_lista(Lista *);

int inserirMeio(Lista *, int);

int removerMeio(Lista *, int);

int acessarValor(Lista *, int, int*);

int acessarIndice(Lista *, int, int*);
