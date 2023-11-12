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

void alterarTarefa(ListaDeTarefas *lt) {
    int pos;
    printf("Entre com a posição da tarefa que deseja alterar: ");
    scanf("%d", &pos);

    if (pos < 0 || pos >= lt->qtd) {
        printf("Posição inválida.\n");
        return;
    }

    int opcao;
    printf("Escolha o campo a ser alterado:\n");
    printf("1. Prioridade\n");
    printf("2. Categoria\n");
    printf("3. Descrição\n");
    printf("4. Estado\n");
    scanf("%d", &opcao);

    tipoTarefa *t = &lt->tarefas[pos];

    switch (opcao) {
        case 1:
            printf("Entre com a nova prioridade: ");
            scanf("%d", &t->prioridade);
            break;
        case 2:
            printf("Entre com a nova categoria: ");
            scanf("%s", t->categoria);
            break;
        case 3:
            printf("Entre com a nova descrição: ");
            scanf("%s", t->descricao);
            break;
        case 4:
            printf("Escolha o novo estado (0 - Não Iniciado, 1 - Em Andamento, 2 - Completo): ");
            scanf("%d", &t->estado);
            break;
        default:
            printf("Opção inválida.\n");
            break;
    }
}
int filtrarPorPrioridade(ListaDeTarefas *lt, int prioridadeFiltrar) {
    if (lt->qtd == 0)
        return 1;

    int encontrou = 0; // Flag para verificar se foram encontradas tarefas com a prioridade desejada

    printf("Tarefas com prioridade %d:\n", prioridadeFiltrar);
    for (int i = 0; i < lt->qtd; i++) {
        if (lt->tarefas[i].prioridade == prioridadeFiltrar) {
            printf("Pos: %d \t Prioridade: %d \t Categoria: %s\n", i,
                   lt->tarefas[i].prioridade, lt->tarefas[i].categoria);
            printf("Estado: %d\n", lt->tarefas[i].estado);
            printf("Descrição: %s\n", lt->tarefas[i].descricao);
            encontrou = 1; // Marcamos como encontrada uma tarefa com a prioridade desejada
        }
    }

    if (!encontrou) {
        printf("Nenhuma tarefa encontrada com prioridade %d\n", prioridadeFiltrar);
        return 2; // Retorna 2 para indicar que nenhuma tarefa foi encontrada
    }

    return 0;
}
int filtrarPorEstado(ListaDeTarefas *lt, int estadoFiltrar) {
    if (lt->qtd == 0)
        return 1;

    int encontrou = 0; // Flag para verificar se foram encontradas tarefas com o estado desejado

    printf("Tarefas com estado %d:\n", estadoFiltrar);
    for (int i = 0; i < lt->qtd; i++) {
        if (lt->tarefas[i].estado == estadoFiltrar) {
            printf("Pos: %d \t Prioridade: %d \t Categoria: %s\n", i,
                   lt->tarefas[i].prioridade, lt->tarefas[i].categoria);
            printf("Estado: %d\n", lt->tarefas[i].estado);
            printf("Descrição: %s\n", lt->tarefas[i].descricao);
            encontrou = 1; // Marcamos como encontrada uma tarefa com o estado desejado
        }
    }

    if (!encontrou) {
        printf("Nenhuma tarefa encontrada com estado %d\n", estadoFiltrar);
        return 2; // Retorna 2 para indicar que nenhuma tarefa foi encontrada
    }

    return 0;
}
int filtrarPorCategoria(ListaDeTarefas *lt, char *categoriaFiltrar) {
    if (lt->qtd == 0)
        return 1;

    int encontrou = 0; // Flag para verificar se foram encontradas tarefas com a categoria desejada

    // Crie um vetor temporário para armazenar as tarefas correspondentes à categoria
    tipoTarefa tarefasCategoria[lt->qtd];
    int qtdTarefasCategoria = 0;

    for (int i = 0; i < lt->qtd; i++) {
        if (strcmp(lt->tarefas[i].categoria, categoriaFiltrar) == 0) {
            tarefasCategoria[qtdTarefasCategoria] = lt->tarefas[i];
            qtdTarefasCategoria++;
            encontrou = 1; // Marcamos como encontrada uma tarefa com a categoria desejada
        }
    }

    if (!encontrou) {
        printf("Nenhuma tarefa encontrada com a categoria %s\n", categoriaFiltrar);
        return 2; // Retorna 2 para indicar que nenhuma tarefa foi encontrada
    }

    // Ordenar as tarefas pelo campo prioridade em ordem decrescente
    for (int i = 0; i < qtdTarefasCategoria - 1; i++) {
        for (int j = i + 1; j < qtdTarefasCategoria; j++) {
            if (tarefasCategoria[i].prioridade < tarefasCategoria[j].prioridade) {
                tipoTarefa temp = tarefasCategoria[i];
                tarefasCategoria[i] = tarefasCategoria[j];
                tarefasCategoria[j] = temp;
            }
        }
    }

    printf("Tarefas com a categoria %s (prioridade decrescente):\n", categoriaFiltrar);
    for (int i = 0; i < qtdTarefasCategoria; i++) {
        printf("Pos: %d \t Prioridade: %d \t Categoria: %s\n", i,
               tarefasCategoria[i].prioridade, tarefasCategoria[i].categoria);
        printf("Estado: %d\n", tarefasCategoria[i].estado);
        printf("Descrição: %s\n", tarefasCategoria[i].descricao);
    }

    return 0;
}
int filtrarPorPrioridadeECategoria(ListaDeTarefas *lt, int prioridade, char *categoria) {
    if (lt->qtd == 0) {
        printf("Não existem tarefas para filtrar.\n");
        return 1;
    }

    int encontrou = 0; // Flag para verificar se foram encontradas tarefas que atendem aos critérios

    printf("Tarefas com prioridade %d e categoria %s:\n", prioridade, categoria);

    for (int i = 0; i < lt->qtd; i++) {
        if (lt->tarefas[i].prioridade == prioridade && strcmp(lt->tarefas[i].categoria, categoria) == 0) {
            printf("Pos: %d \t Prioridade: %d \t Categoria: %s\n", i,
                   lt->tarefas[i].prioridade, lt->tarefas[i].categoria);
            printf("Estado: %d\n", lt->tarefas[i].estado);
            printf("Descrição: %s\n", lt->tarefas[i].descricao);
            encontrou = 1; // Marcamos como encontrada uma tarefa que atende aos critérios
        }
    }
    if (!encontrou) {
        printf("Nenhuma tarefa encontrada com prioridade %d e categoria %s\n", prioridade, categoria);
        return 2; // Retorna 2 para indicar que nenhuma tarefa foi encontrada
    }

    return 0;
}



