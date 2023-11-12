
#define TOTAL_TAREFAS 100

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



