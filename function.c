//
// Created by victo on 27/10/2023.
//

#include "function.h"
#include <stdio.h>
#include <string.h>


int carregarTarefas(ListaDeTarefas *lt, char *nome) {
    FILE *fp = fopen(nome, "rb");
    if (fp == NULL)
        return 1;

    fread(lt, sizeof(ListaDeTarefas), 1, fp);
    fclose(fp);

    return 0;
}

int salvarTarefas(ListaDeTarefas *lt, char *nome) {
    FILE *fp = fopen(nome, "wb");
    if (fp == NULL)
        return 1;

    fwrite(lt, sizeof(ListaDeTarefas), 1, fp);
    fclose(fp);

    return 0;
}
int crietarefa(ListaDeTarefas *lt) {
    if (lt->qtd >= TOTAL_TAREFAS)
        return 1;

    tipoTarefa *t = &lt->tarefas[lt->qtd];

    printf("Entre com a prioridade da tarefa: ");
    scanf("%d", &t->prioridade);

    printf("Entre com a categoria da tarefa: ");
    scanf("%s", t->categoria);

    printf("Entre com a descrição da tarefa: ");
    scanf("%s", t->descricao);

    printf("Escolha o estado da tarefa (0 - Não Iniciado, 1 - Em Andamento, 2 - Completo): ");
    scanf("%d", &t->estado);

    lt->qtd++;

    return 0;
}


int apaguetarefa(ListaDeTarefas *lt) {
    if (lt->qtd == 0)
        return 1;

    int pos;
    printf("Entre com a posicao da tarefa que sera deletada: ");
    scanf("%d", &pos);

    if (pos < 0 || pos > lt->qtd - 1)
        return 2;

    for (; pos < lt->qtd - 1; pos++) {
        lt->tarefas[pos].prioridade = lt->tarefas[pos + 1].prioridade;
        strcpy(lt->tarefas[pos].descricao, lt->tarefas[pos + 1].descricao);
        strcpy(lt->tarefas[pos].categoria, lt->tarefas[pos + 1].categoria);
        lt->tarefas[pos].estado = lt->tarefas[pos + 1].estado;
    }

    lt->qtd--;

    return 0;
}

int listetarefa(ListaDeTarefas *lt) {
    if (lt->qtd == 0)
        return 1;

    for (int i = 0; i < lt->qtd; i++) {
        printf("Pos: %d \t Prioridade: %d \t Categoria: %s\n", i,
               lt->tarefas[i].prioridade, lt->tarefas[i].categoria);
        printf("Estado: %d\n", lt->tarefas[i].estado);
        printf("Descrição: %s\n", lt->tarefas[i].descricao);
    }

    return 0;
}

