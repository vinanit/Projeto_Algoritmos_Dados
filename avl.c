#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

AVL* criar_no_avl(Aluno aluno) {
    AVL *novo = (AVL*)malloc(sizeof(AVL));
    novo->aluno = aluno;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->altura = 1;
    return novo;
}

int altura_avl(AVL *no) {
    return no ? no->altura : 0;
}

int maior(int a, int b) {
    return (a > b) ? a : b;
}

int fator_balanceamento(AVL *no) {
    return no ? altura_avl(no->esq) - altura_avl(no->dir) : 0;
}

AVL* rotacao_direita(AVL *y) {
    AVL *x = y->esq;
    AVL *T2 = x->dir;
    
    x->dir = y;
    y->esq = T2;
    
    y->altura = maior(altura_avl(y->esq), altura_avl(y->dir)) + 1;
    x->altura = maior(altura_avl(x->esq), altura_avl(x->dir)) + 1;
    
    return x;
}

AVL* rotacao_esquerda(AVL *x) {
    AVL *y = x->dir;
    AVL *T2 = y->esq;
    
    y->esq = x;
    x->dir = T2;
    
    x->altura = maior(altura_avl(x->esq), altura_avl(x->dir)) + 1;
    y->altura = maior(altura_avl(y->esq), altura_avl(y->dir)) + 1;
    
    return y;
}

AVL* inserir_avl(AVL *raiz, Aluno aluno) {
    if (!raiz)
        return criar_no_avl(aluno);
    
    if (aluno.matricula < raiz->aluno.matricula)
        raiz->esq = inserir_avl(raiz->esq, aluno);
    else if (aluno.matricula > raiz->aluno.matricula)
        raiz->dir = inserir_avl(raiz->dir, aluno);
    else
        return raiz; // Chaves iguais não são permitidas
    
    raiz->altura = 1 + maior(altura_avl(raiz->esq), altura_avl(raiz->dir));
    
    int fb = fator_balanceamento(raiz);
    
    // Casos de desbalanceamento
    if (fb > 1 && aluno.matricula < raiz->esq->aluno.matricula)
        return rotacao_direita(raiz);
    
    if (fb < -1 && aluno.matricula > raiz->dir->aluno.matricula)
        return rotacao_esquerda(raiz);
    
    if (fb > 1 && aluno.matricula > raiz->esq->aluno.matricula) {
        raiz->esq = rotacao_esquerda(raiz->esq);
        return rotacao_direita(raiz);
    }
    
    if (fb < -1 && aluno.matricula < raiz->dir->aluno.matricula) {
        raiz->dir = rotacao_direita(raiz->dir);
        return rotacao_esquerda(raiz);
    }
    
    return raiz;
}

Aluno* buscar_avl(AVL *raiz, int matricula) {
    if (!raiz)
        return NULL;
    
    if (matricula == raiz->aluno.matricula)
        return &raiz->aluno;
    
    if (matricula < raiz->aluno.matricula)
        return buscar_avl(raiz->esq, matricula);
    else
        return buscar_avl(raiz->dir, matricula);
}

void em_ordem_avl(AVL *raiz) {
    if (raiz) {
        em_ordem_avl(raiz->esq);
        // MUDOU: campos atualizados
        printf("Matrícula: %d | Nome: %-20s | Nota: %6.2f | Aulas: %6.2f%% | Atividades: %6.2f%% | Categoria: %s\n",
               raiz->aluno.matricula, raiz->aluno.nome, raiz->aluno.nota,
               raiz->aluno.aulas_assistidas, raiz->aluno.atividades_concluidas, raiz->aluno.categoria);
        em_ordem_avl(raiz->dir);
    }
}

void exibir_avl_hierarquico(AVL *raiz, int nivel) {
    if (raiz) {
        exibir_avl_hierarquico(raiz->dir, nivel + 1);
        
        for (int i = 0; i < nivel; i++)
            printf("    ");
        
        printf("%d (%s)\n", raiz->aluno.matricula, raiz->aluno.categoria);
        
        exibir_avl_hierarquico(raiz->esq, nivel + 1);
    }
}

void contar_categorias(AVL *raiz, int counts[6]) {  // MUDOU: agora 6 categorias
    if (raiz) {
        contar_categorias(raiz->esq, counts);
        
        // MUDOU: novas categorias
        if (strcmp(raiz->aluno.categoria, "Desinteressado") == 0) counts[0]++;
        else if (strcmp(raiz->aluno.categoria, "Com Dificuldade") == 0) counts[1]++;
        else if (strcmp(raiz->aluno.categoria, "Autodidata") == 0) counts[2]++;
        else if (strcmp(raiz->aluno.categoria, "Pratico") == 0) counts[3]++;
        else if (strcmp(raiz->aluno.categoria, "Teórico") == 0) counts[4]++;
        else if (strcmp(raiz->aluno.categoria, "Exemplar") == 0) counts[5]++;
        
        contar_categorias(raiz->dir, counts);
    }
}

void liberar_avl(AVL *raiz) {
    if (raiz) {
        liberar_avl(raiz->esq);
        liberar_avl(raiz->dir);
        free(raiz);
    }
}
