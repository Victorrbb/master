#include "struct.h"
int salvarTarefas(ListaDeTarefas lt,char nome[]);
int carregarTarefas(ListaDeTarefas *lt,char nome[]);
int crietarefa(ListaDeTarefas *lt);
int apaguetarefa(ListaDeTarefas *lt);
int listetarefa(ListaDeTarefas *lt);
void alterarTarefa(ListaDeTarefas *lt);
int filtrarPorPrioridade(ListaDeTarefas *lt, int prioridadeFiltrar);
int filtrarPorEstado(ListaDeTarefas *lt, int estadoFiltrar);
int filtrarPorCategoria(ListaDeTarefas *lt, char *categoriaFiltrar);
int filtrarPorPrioridadeECategoria(ListaDeTarefas *lt, int prioridade, char *categoria);
int exportarPorPrioridade(ListaDeTarefas *lt, int prioridadeExportar);
void exportarTarefasPorCategoriaOrdenadas(ListaDeTarefas *lt, char *categoria, const char *arquivo);
void exportarTarefasPorPrioridadeECategoriaOrdenadas(ListaDeTarefas *lt, int prioridade, char *categoria, const char *arquivo);






