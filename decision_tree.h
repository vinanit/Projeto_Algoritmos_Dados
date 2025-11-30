#ifndef DECISION_TREE_H
#define DECISION_TREE_H

// Função principal de classificação
const char* classificar_aluno(float nota, float aulas, float atividades);

// Funções auxiliares de decisão
int decisao_nota_alta(float nota);
int decisao_engajamento_alto(float percentual_conclusao);
int decisao_frequencia_alta(float frequencia);
int decisao_nota_media(float nota);
int decisao_engajamento_medio(float percentual_conclusao);

#endif