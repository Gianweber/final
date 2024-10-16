#include <stdio.h>
#include <stdlib.h>
#include "eventos.h"

int main() {
    Node* raiz = NULL;
    int opcao, codigo;
    Data consultaData;

    do {
        printf("\nMENU:\n");
        printf("1. Inserir evento\n");
        printf("2. Consultar evento por data e hora\n");
        printf("3. Atualizar evento por código\n");
        printf("4. Visualizar todos os eventos\n");
        printf("5. Excluir evento por código\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Evento novoEvento = criarEventoManual(raiz);
                if (validarData(novoEvento.dataEvento) && validarDuracao(novoEvento.duracao)) {
                    inserirEvento(&raiz, novoEvento);
                } else {
                    printf("Erro: Data inválida ou duração negativa!\n");
                }
                break;
            }
            case 2:
                printf("Digite a data e hora do evento (dia mes ano hora minuto): ");
                scanf("%d %d %d %d %d", &consultaData.dia, &consultaData.mes, &consultaData.ano, &consultaData.hora, &consultaData.minuto);
                if (validarData(consultaData)) {
                    consultarEvento(raiz, consultaData);
                } else {
                    printf("Erro: Data inválida!\n");
                }
                break;
            case 3:
                printf("Digite o código do evento a ser atualizado: ");
                scanf("%d", &codigo);
                if (buscarEventoPorCodigo(raiz, codigo)) {
                    atualizarEvento(raiz, codigo);
                } else {
                    printf("Erro: Evento não encontrado!\n");
                }
                break;
            case 4:
                printf("\nEventos ordenados por data:\n");
                exibirEventos(raiz);
                break;
            case 5:
                printf("Digite o código do evento a ser removido: ");
                scanf("%d", &codigo);
                if (removerEvento(raiz, codigo) != NULL) {
                    printf("Evento removido com sucesso!\n");
                }
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (opcao != 6);

    return 0;
}
