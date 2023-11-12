#include <stdio.h>
#include "function.h"



int main() {
        ListaDeTarefas lt;

        char arquivo[] = "tarefas";
        int codigo, opcao;
        int prioridadeFiltrar; // Variável para a prioridade a ser filtrada
        int estadoFiltrar; // Variável para o estado a ser filtrado
        char categoriaFiltrar[100]; // Variável para a categoria a ser filtrada
        int prioridadeExportar;

        codigo = carregarTarefas(&lt, arquivo);

        if (codigo != 0) {
            printf("Lista de tarefas não carregada\n");
            lt.qtd = 0;
        }

        do {

            printf("lista de tarefas\n");
            printf("selecione o desejado!\n");
            printf("1 - criar tarefa\n");
            printf("2 - exluir tarefas\n");
            printf("3 - vizualizar tarefas\n");
            printf("4 - Alterar tarefa\n");
            printf("5 - Filtrar por prioridade\n");
            printf("6 - Filtrar por estado\n");
            printf("7 - Filtrar por categoria\n");
            printf("8 - Filtrar por prioridade e categoria\n");
            printf("9 - Exportar por prioridade\n");
            printf("10- Exportar por categoria e ordem\n");
            printf("11- Exportar por prioridade categoria e ordem \n");
            printf("0 - Finalizar\n");

            scanf("%d", &opcao);

            switch (opcao) {
                case 0:
                    break;
                case 1:
                    codigo = crietarefa(&lt);
                    if (codigo == 1)
                        printf("Erro ao criar tarefa: sem espaço disponível\n");
                    break;
                case 2:
                    codigo = apaguetarefa(&lt);
                    if (codigo == 1)
                        printf("Erro ao deletar tarefa: não existem tarefas para deletar\n");
                    else if (codigo == 2)
                        printf("Erro ao deletar tarefa: posição inválida\n");
                    break;
                case 3:
                    codigo = listetarefa(&lt);
                    if (codigo == 1)
                        printf("Erro ao listar tarefas: não existem tarefas para listar\n");
                    break;
                case 4:
                    alterarTarefa(&lt);
                    break;
                case 5:
                    printf("Entre com a prioridade desejada: ");
                    scanf("%d", &prioridadeFiltrar);
                    codigo = filtrarPorPrioridade(&lt, prioridadeFiltrar);
                    if (codigo == 1)
                        printf("Nenhuma tarefa encontrada com prioridade %d\n", prioridadeFiltrar);
                    break;
                case 6:
                    printf("Entre com o estado desejado (0 - Não Iniciado, 1 - Em Andamento, 2 - Completo): ");
                    scanf("%d", &estadoFiltrar);
                    codigo = filtrarPorEstado(&lt, estadoFiltrar);
                    if (codigo == 1)
                        printf("Nenhuma tarefa encontrada com estado %d\n", estadoFiltrar);
                    break;
                case 7:
                    printf("Entre com a categoria desejada: ");
                    scanf("%s", categoriaFiltrar);
                    codigo = filtrarPorCategoria(&lt, categoriaFiltrar);
                    if (codigo == 1)
                        printf("Nenhuma tarefa encontrada com a categoria %s\n", categoriaFiltrar);
                    break;
                case 8:
                    printf("Digite a prioridade: ");
                    scanf("%d", &prioridadeFiltrar);
                    printf("Digite a categoria: ");
                    scanf("%s", categoriaFiltrar);
                    codigo = filtrarPorPrioridadeECategoria(&lt, prioridadeFiltrar, categoriaFiltrar);
                    if (codigo == 1)
                        printf("Erro ao filtrar tarefas: não existem tarefas que atendam aos critérios\n");
                    break;



                case 9:
                    printf("Entre com a prioridade desejada para exportar: ");
                    scanf("%d", &prioridadeExportar); // Não redeclare prioridadeExportar
                    codigo = exportarPorPrioridade(&lt, prioridadeExportar);

                    if (codigo == 1)
                        printf("Nenhuma tarefa encontrada com prioridade %d\n", prioridadeExportar);
                    else if (codigo == 0)
                        printf("Tarefas com prioridade %d exportadas com sucesso.\n");
                    break;


                case 10:
                    printf("Entre com a categoria desejada para exportar: ");
                    scanf("%s", categoriaFiltrar);
                    exportarTarefasPorCategoriaOrdenadas(&lt, categoriaFiltrar, "export_categoria.txt");
                    if (codigo == 1)
                        printf("Nenhuma tarefa encontrada com a categoria %s\n", categoriaFiltrar);
                    else if (codigo == 0)
                        printf("Tarefas com categoria %s exportadas com sucesso.\n");
                    break;
                case 11:
                    printf("Digite a prioridade desejada para exportar: ");
                    scanf("%d", &prioridadeExportar);
                    printf("Digite a categoria desejada para exportar: ");
                    scanf("%s", categoriaFiltrar);
                    exportarTarefasPorPrioridadeECategoriaOrdenadas(&lt, prioridadeExportar, categoriaFiltrar, "export_prioridade_categoria.txt");
                    if (codigo == 1)
                        printf("Erro ao exportar tarefas: não existem tarefas que atendam aos critérios\n");
                    else if (codigo == 0)
                        printf("Tarefas com prioridade %d e categoria %s exportadas com sucesso.\n", prioridadeExportar, categoriaFiltrar);
                    break;
                default:
                    printf("Opção inválida\n");
                    break;



            }

        } while (opcao != 0);

        codigo = salvarTarefas(lt, arquivo);
        if (codigo != 0)
            printf("Erro ao salvar tarefas em arquivo\n");

        return 0;
    }