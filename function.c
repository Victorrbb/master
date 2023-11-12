

#include "function.h"
#include <stdio.h>
#include <string.h>
const char* getEstadoTarefa(int estado) {
    switch (estado) {
        case NAO_INICIADO:
            return "Não Iniciado";
        case EM_ANDAMENTO:
            return "Em Andamento";
        case COMPLETO:
            return "Completo";
        default:
            return "Estado Desconhecido";
    }
}
int carregarTarefas(ListaDeTarefas *lt, char nome[]) {
    FILE *fp = fopen(nome, "rb");
    if (fp == NULL)
        return 1;

    fread(lt, sizeof(ListaDeTarefas), 1, fp);
    fclose(fp);

    return 0;
}

int salvarTarefas(ListaDeTarefas lt, char nome[]) {
    FILE *fp = fopen(nome, "wb");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return 1;
    }

    fwrite(&lt, sizeof(ListaDeTarefas), 1, fp);

    if (fclose(fp) != 0) {
        printf("Erro ao fechar o arquivo.\n");
        return 2;
    }

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


// Função para exportar tarefas por prioridade em um arquivo de texto
int exportarPorPrioridade(ListaDeTarefas *lt, int prioridadeExportar) {
    if (lt->qtd == 0)
        return 1;

    char nomeArquivo[100];
    sprintf(nomeArquivo, "tarefas_prioridade_%d.txt", prioridadeExportar);

    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return 2;
    }

    for (int i = 0; i < lt->qtd; i++) {
        if (lt->tarefas[i].prioridade == prioridadeExportar) {
            fprintf(arquivo, "%d %s %d %s\n", lt->tarefas[i].prioridade, lt->tarefas[i].categoria,
                    lt->tarefas[i].estado, lt->tarefas[i].descricao);
        }
    }

    fclose(arquivo);
    printf("Tarefas de prioridade %d exportadas com sucesso para %s.\n", prioridadeExportar, nomeArquivo);
    return 0;
}

void exportarTarefasPorCategoriaOrdenadas(ListaDeTarefas *lt, char *categoria, const char *arquivo) {
    FILE *fp = fopen(arquivo, "w");
    if (fp == NULL) {
        printf("Erro ao criar o arquivo de exportação.\n");
        return;
    }

    // Criar um array de índices para as tarefas e ordená-los por prioridade
    int indices[TOTAL_TAREFAS];
    for (int i = 0; i < lt->qtd; i++) {
        indices[i] = i;
    }

    for (int i = 0; i < lt->qtd - 1; i++) {
        for (int j = i + 1; j < lt->qtd; j++) {
            if (lt->tarefas[indices[i]].prioridade < lt->tarefas[indices[j]].prioridade) {
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }

    // Escrever as tarefas no arquivo, filtrando pela categoria especificada
    for (int i = 0; i < lt->qtd; i++) {
        int index = indices[i];
        if (strcmp(lt->tarefas[index].categoria, categoria) == 0) {
            fprintf(fp, "%d, %s, %s, %s\n", lt->tarefas[index].prioridade, lt->tarefas[index].categoria, getEstadoTarefa(lt->tarefas[index].estado), lt->tarefas[index].descricao);
        }
    }

    fclose(fp);
}

void exportarTarefasPorPrioridadeECategoriaOrdenadas(ListaDeTarefas *lt, int prioridade, char *categoria, const char *arquivo) {
    FILE *fp = fopen(arquivo, "w");
    if (fp == NULL) {
        printf("Erro ao criar o arquivo de exportação.\n");
        return;
    }

    // Criar um array de índices para as tarefas e ordená-los por prioridade
    int indices[TOTAL_TAREFAS];
    for (int i = 0; i < lt->qtd; i++) {
        indices[i] = i;
    }

    for (int i = 0; i < lt->qtd - 1; i++) {
        for (int j = i + 1; j < lt->qtd; j++) {
            if (lt->tarefas[indices[i]].prioridade < lt->tarefas[indices[j]].prioridade) {
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }

    // Escrever as tarefas no arquivo, filtrando pela prioridade e categoria especificadas
    for (int i = 0; i < lt->qtd; i++) {
        int index = indices[i];
        if (lt->tarefas[index].prioridade == prioridade && strcmp(lt->tarefas[index].categoria, categoria) == 0) {
            fprintf(fp, "%d, %s, %s, %s\n", lt->tarefas[index].prioridade, lt->tarefas[index].categoria, getEstadoTarefa(lt->tarefas[index].estado), lt->tarefas[index].descricao);
        }
    }

    fclose(fp);
}

