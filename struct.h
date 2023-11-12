//
#ifndef PROJETO3_STRUCT_H
#define PROJETO3_STRUCT_H
#define TOTAL_TAREFAS 100
#endif //PROJETO3_STRUCT_H
enum EstadoTarefa {
    NAO_INICIADO,
    EM_ANDAMENTO,
    COMPLETO
};
typedef struct {
    int prioridade;
    char descricao[300];
    char categoria[100];
    int estado;
} tipoTarefa;

typedef struct {
    tipoTarefa tarefas[TOTAL_TAREFAS];
    int qtd;
} ListaDeTarefas;


