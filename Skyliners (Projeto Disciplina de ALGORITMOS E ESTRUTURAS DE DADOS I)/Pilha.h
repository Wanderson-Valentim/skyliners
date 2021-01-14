typedef struct elemento *Pilha;

Pilha* criar_pilha();

void destruir_pilha(Pilha *);

int tamanho_pilha(Pilha *);

int vazia_pilha(Pilha *);

int inserir_pilha(Pilha *, int);

int remover_pilha(Pilha *);

int acessar_pilha(Pilha *, int *);
