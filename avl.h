#ifndef AVL_H
#define AVL_H

#define MAX_CATEGORIA 20

typedef struct {
    int matricula; //Número de matricula
    char nome[50]; //Nome do aluno
    float nota; // Media das provas
    float aulas_assistidas; // porcentagem de aulas assistidas
    float atividades_concluidas; // porcentagem de atividades concluidas
    char categoria[MAX_CATEGORIA]; // categoria que o aluno vai receber
} Aluno;

typedef struct no_avl {
    Aluno aluno;
    struct no_avl *esq;
    struct no_avl *dir;
    int altura;
} AVL;

// Funções básicas da AVL
AVL* criar_no_avl(Aluno aluno);
int altura_avl(AVL *no);
int maior(int a, int b);
int fator_balanceamento(AVL *no);

// Rotações
AVL* rotacao_direita(AVL *y);
AVL* rotacao_esquerda(AVL *x);

// Inserção e busca
AVL* inserir_avl(AVL *raiz, Aluno aluno);
Aluno* buscar_avl(AVL *raiz, int matricula);

// Percursos
void em_ordem_avl(AVL *raiz);
void exibir_avl_hierarquico(AVL *raiz, int nivel);

// Utilitárias
void contar_categorias(AVL *raiz, int counts[6]); 
void liberar_avl(AVL *raiz);

#endif