#include <string.h>
#include "decision_tree.h"

// Funções de decisão (nós internos da árvore)
int decisao_nota_alta(float nota) {
    return nota >= 80;
}

int decisao_engajamento_alto(float percentual_conclusao) {
    return percentual_conclusao >= 85;
}

int decisao_frequencia_alta(float frequencia) {
    return frequencia >= 80;
}

int decisao_nota_media(float nota) {
    return nota >= 60;
}

int decisao_engajamento_medio(float percentual_conclusao) {
    return percentual_conclusao >= 70;
}

// Árvore de decisão principal
const char* classificar_aluno(float nota, float aulas, float atividades) {
    /*
    NOVA ÁRVORE DE DECISÃO:
    
    Nota >= 70?
      |
      |-- NÃO (Nota baixa)
      |     |
      |     |-- Aulas < 70 E Atividades < 70? → Desinteressado
      |     |-- Caso contrário → Com Dificuldade
      |
      |-- SIM (Nota alta)
            |
            |-- Aulas < 70?
            |     |
            |     |-- Atividades < 70? → Autodidata
            |     |-- Atividades >= 70? → Pratico
            |
            |-- Aulas >= 70?
                  |
                  |-- Atividades < 70? → Teórico
                  |-- Atividades >= 70? → Exemplar
    */
    
    if (nota < 70) {
        // Ramo da esquerda: nota baixa
        if (aulas < 70 && atividades < 70) {
            return "Desinteressado";
        } else {
            return "Com Dificuldade";
        }
    } else {
        // Ramo da direita: nota alta
        if (aulas < 70) {
            if (atividades < 70) {
                return "Autodidata";
            } else {
                return "Pratico";
            }
        } else {
            if (atividades < 70) {
                return "Teórico";
            } else {
                return "Exemplar";
            }
        }
    }
}