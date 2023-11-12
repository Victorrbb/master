#include <stdio.h>
#include "function.h"



    int main() {
        ListaDeTarefas lt;

        char arquivo[] = "tarefas";
        int codigo, opcao;
        

        codigo = carregarTarefas(&lt, arquivo);

        if (codigo != 0) {
            printf("Lista de tarefas não carregada\n");
            lt.qtd = 0;
        }

        do {

            printf("lista de tarefas\n");
            printf("selecione o desejado!\n");
            printf("1 - criar tarefa\n");
            printf("2 - vizualizar tarefas\n");
            printf("3 - excluir tarefas\n");
            
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
            default:
                    printf("Opção inválida\n");
                    break;



            }

        } while (opcao != 0);

        codigo = salvarTarefas(&lt, arquivo);
        if (codigo != 0)
            printf("Erro ao salvar tarefas em arquivo\n");

        return 0;
    }