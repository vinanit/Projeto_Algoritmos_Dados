#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "decision_tree.h"

void menu_principal() {
    printf("\n=== PLATAFORMA DE CURSOS ONLINE ===\n");
    printf("1. Cadastrar aluno\n");
    printf("2. Buscar aluno\n");
    printf("3. Atualizar dados do aluno\n");
    printf("4. Listar todos os alunos\n");
    printf("5. Exibir árvore AVL\n");
    printf("6. Estatísticas\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}

void cadastrar_aluno(AVL **avl) {
    Aluno novo;
    printf("\n--- CADASTRO DE ALUNO ---\n");
    
    printf("Matrícula: ");
    scanf("%d", &novo.matricula);
    getchar();
    
    printf("Nome: ");
    fgets(novo.nome, 50, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = 0;
    
    printf("Nota média das provas (0-100): ");
    scanf("%f", &novo.nota);
    
    printf("Aulas assistidas (0-100): ");
    scanf("%f", &novo.aulas_assistidas);
    
    printf("Atividades concluídas (0-100): ");
    scanf("%f", &novo.atividades_concluidas);
    
    strcpy(novo.categoria, classificar_aluno(novo.nota, novo.aulas_assistidas, novo.atividades_concluidas));
    
    *avl = inserir_avl(*avl, novo);
    
    printf("\nAluno cadastrado com sucesso!\n");
    printf("Categoria atribuída: %s\n", novo.categoria);
}

void buscar_aluno(AVL *avl) {
    int matricula;
    printf("\n--- BUSCAR ALUNO ---\n");
    printf("Matrícula: ");
    scanf("%d", &matricula);
    
    Aluno *aluno = buscar_avl(avl, matricula);
    if (aluno) {
        printf("\nAluno encontrado:\n");
        printf("Matrícula: %d\n", aluno->matricula);
        printf("Nome: %s\n", aluno->nome);
        printf("Nota: %.2f\n", aluno->nota);
        printf("Aulas assistidas: %.2f%%\n", aluno->aulas_assistidas);
        printf("Atividades concluídas: %.2f%%\n", aluno->atividades_concluidas);
        printf("Categoria: %s\n", aluno->categoria);
    } else {
        printf("Aluno não encontrado!\n");
    }
}

void atualizar_aluno(AVL **avl) {
    int matricula;
    printf("\n--- ATUALIZAR ALUNO ---\n");
    printf("Matrícula: ");
    scanf("%d", &matricula);
    
    Aluno *aluno = buscar_avl(*avl, matricula);
    if (aluno) {
        printf("\nDados atuais:\n");
        printf("Nome: %s\n", aluno->nome);
        printf("Nota: %.2f\n", aluno->nota);
        printf("Aulas assistidas: %.2f%%\n", aluno->aulas_assistidas);
        printf("Atividades concluídas: %.2f%%\n", aluno->atividades_concluidas);
        
        printf("\nNovos dados:\n");
        printf("Nova nota (0-100): ");
        scanf("%f", &aluno->nota);
        
        printf("Novas aulas assistidas (0-100): ");
        scanf("%f", &aluno->aulas_assistidas);
        
        printf("Novas atividades concluídas (0-100): ");
        scanf("%f", &aluno->atividades_concluidas);
        
        strcpy(aluno->categoria, classificar_aluno(aluno->nota, aluno->aulas_assistidas, aluno->atividades_concluidas));
        
        printf("Dados atualizados! Nova categoria: %s\n", aluno->categoria);
    } else {
        printf("Aluno não encontrado!\n");
    }
}

void estatisticas(AVL *avl) {
    if (!avl) {
        printf("Nenhum aluno cadastrado!\n");
        return;
    }
    
    int counts[6] = {0};
    contar_categorias(avl, counts);
    
    int total = counts[0] + counts[1] + counts[2] + counts[3] + counts[4] + counts[5];
    
    printf("\n=== ESTATÍSTICAS ===\n");
    printf("Total de alunos: %d\n", total);
    printf("\nDistribuição por categoria:\n");
    printf("Desinteressado: %d (%.1f%%)\n", counts[0], total > 0 ? (float)counts[0]/total*100 : 0);
    printf("Com Dificuldade: %d (%.1f%%)\n", counts[1], total > 0 ? (float)counts[1]/total*100 : 0);
    printf("Autodidata: %d (%.1f%%)\n", counts[2], total > 0 ? (float)counts[2]/total*100 : 0);
    printf("Pratico: %d (%.1f%%)\n", counts[3], total > 0 ? (float)counts[3]/total*100 : 0);
    printf("Teórico: %d (%.1f%%)\n", counts[4], total > 0 ? (float)counts[4]/total*100 : 0);
    printf("Exemplar: %d (%.1f%%)\n", counts[5], total > 0 ? (float)counts[5]/total*100 : 0);
}

void aguardar_enter() {
    printf("\nPressione Enter para continuar...");
    getchar();
    getchar();
}

int main() {
    AVL *avl = NULL;
    int opcao;
    
    printf("=== SISTEMA DE CLASSIFICAÇÃO DE ALUNOS ===\n");
    printf("Integração: Árvore AVL + Árvore de Decisão\n\n");
    
    do {
        menu_principal();
        scanf("%d", &opcao);
        getchar();
        
        switch(opcao) {
            case 1:
                cadastrar_aluno(&avl);
                aguardar_enter();
                break;
            case 2:
                buscar_aluno(avl);
                aguardar_enter();
                break;
            case 3:
                atualizar_aluno(&avl);
                aguardar_enter();
                break;
            case 4:
                printf("\n--- LISTA DE ALUNOS ---\n");
                em_ordem_avl(avl);
                aguardar_enter();
                break;
            case 5:
                printf("\n--- ESTRUTURA DA ÁRVORE AVL ---\n");
                exibir_avl_hierarquico(avl, 0);
                aguardar_enter();
                break;
            case 6:
                estatisticas(avl);
                aguardar_enter();
                break;
            case 0:
                printf("Encerrando sistema...\n");
                break;
            default:
                printf("Opção inválida!\n");
                aguardar_enter();
        }
    } while(opcao != 0);
    
    liberar_avl(avl);
    return 0;
}