
#ifndef PROJETO3_FUNCTION_H
#define PROJETO3_FUNCTION_H

#include "struct.h"
int salvarTarefas();
int carregarTarefas();
int crietarefa(ListaDeTarefas *lt);
int apaguetarefa(ListaDeTarefas *lt);
int listetarefa(ListaDeTarefas *lt);
void alterarTarefa(ListaDeTarefas *lt);
nt filtrarPorPrioridade(ListaDeTarefas *lt, int prioridadeFiltrar);
int filtrarPorEstado(ListaDeTarefas *lt, int estadoFiltrar);
int filtrarPorCategoria(ListaDeTarefas *lt, char *categoriaFiltrar);
int filtrarPorPrioridadeECategoria(ListaDeTarefas *lt, int prioridade, char *categoria);






