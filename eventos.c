#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eventos.h"

// Função para validar a data
int validarData(Data data) {
    if (data.ano < 1900 || data.ano > 2100) return 0;
    if (data.mes < 1 || data.mes > 12) return 0;
    if (data.dia < 1 || data.dia > 31) return 0;
    if (data.hora < 0 || data.hora > 23) return 0;
    if (data.minuto < 0 || data.minuto > 59) return 0;
    return 1;
}

// Função para validar a duração
int validarDuracao(float duracao) {
    return duracao > 0;
}

// Função para comparar duas datas
int comparaData(Data d1, Data d2) {
    if (d1.ano != d2.ano) return d1.ano - d2.ano;
    if (d1.mes != d2.mes) return d1.mes - d2.mes;
    if (d1.dia != d2.dia) return d1.dia - d2.dia;
    if (d1.hora != d2.hora) return d1.hora - d2.hora;
    return d1.minuto - d2.minuto;
}

// Função para inicializar um nó da árvore
void inicializaAvl(Node** node, Evento evento) {
    *node = (Node*) malloc(sizeof(Node));
    if (*node == NULL) {
        printf("Erro ao alocar memória\n");
        exit(1);
    }
    (*node)->evento = evento;
    (*node)->esq = NULL;
    (*node)->dir = NULL;
    (*node)->pai = NULL;
}

// Função para buscar evento por código
Node* buscarEventoPorCodigo(Node* raiz, int codigo) {
    if (raiz == NULL) {
        return NULL;
    }
    if (codigo == raiz->evento.codigo) {
        return raiz;
    } else if (codigo < raiz->evento.codigo) {
        return buscarEventoPorCodigo(raiz->esq, codigo);
    } else {
        return buscarEventoPorCodigo(raiz->dir, codigo);
    }
}

// Função para inserir eventos na árvore
void inserirEvento(Node** raiz, Evento novoEvento) {
    if (*raiz == NULL) {
        inicializaAvl(raiz, novoEvento);
        printf("Evento inserido com sucesso: %s\n", novoEvento.descricao);
        return;
    }

    Node* existente = buscarEventoPorCodigo(*raiz, novoEvento.codigo);
    if (existente != NULL) {
        printf("Erro: Já existe um evento com o código %d.\n", novoEvento.codigo);
        return;
    }

    int comp = comparaData(novoEvento.dataEvento, (*raiz)->evento.dataEvento);
    if (comp < 0) {
        inserirEvento(&((*raiz)->esq), novoEvento);
    } else if (comp > 0) {
        inserirEvento(&((*raiz)->dir), novoEvento);
    } else {
        printf("Erro: Já existe um evento na mesma data.\n");
    }
}

// Função para atualizar evento por código
void atualizarEvento(Node* raiz, int codigo) {
    Node* eventoExistente = buscarEventoPorCodigo(raiz, codigo);
    if (eventoExistente == NULL) {
        printf("Evento não encontrado!\n");
        return;
    }

    // Mostrar informações atuais do evento
    printf("Evento atual: %s | Data: %02d/%02d/%d %02d:%02d\n",
           eventoExistente->evento.descricao,
           eventoExistente->evento.dataEvento.dia,
           eventoExistente->evento.dataEvento.mes,
           eventoExistente->evento.dataEvento.ano,
           eventoExistente->evento.dataEvento.hora,
           eventoExistente->evento.dataEvento.minuto);

    // Criar um novo evento com os dados atualizados
    Evento novoEvento = criarEventoManual(raiz); // Pergunta ao usuário os novos dados

    // Validar a nova data e duração
    if (validarData(novoEvento.dataEvento) && validarDuracao(novoEvento.duracao)) {
        // Verificar se já existe um evento na nova data
        Node* eventoComMesmaData = buscarEventoPorCodigo(raiz, novoEvento.codigo);
        if (eventoComMesmaData != NULL) {
            printf("Erro: Já existe um evento na nova data!\n");
            return;
        }
        
        // Atualizar os dados do evento existente
        eventoExistente->evento = novoEvento;
        printf("Evento atualizado com sucesso!\n");
    } else {
        printf("Erro: Data inválida ou duração negativa!\n");
    }
}

// Função para percorrer e exibir a árvore (em ordem)
void exibirEventos(Node* raiz) {
    if (raiz != NULL) {
        exibirEventos(raiz->esq);
        printf("Evento: %s | Data: %02d/%02d/%d %02d:%02d | Duração: %.2f horas | Código: %d\n", 
               raiz->evento.descricao, 
               raiz->evento.dataEvento.dia, raiz->evento.dataEvento.mes, 
               raiz->evento.dataEvento.ano, raiz->evento.dataEvento.hora, 
               raiz->evento.dataEvento.minuto, raiz->evento.duracao, raiz->evento.codigo);
        exibirEventos(raiz->dir);
    }
}

// Função para consultar evento por data e hora
void consultarEvento(Node* raiz, Data data) {
    if (raiz == NULL) {
        printf("Evento não encontrado.\n");
        return;
    }

    int comp = comparaData(data, raiz->evento.dataEvento);
    if (comp == 0) {
        printf("Evento encontrado: %s | Data: %02d/%02d/%d %02d:%02d | Código: %d\n", 
               raiz->evento.descricao, 
               raiz->evento.dataEvento.dia, raiz->evento.dataEvento.mes, 
               raiz->evento.dataEvento.ano, raiz->evento.dataEvento.hora, 
               raiz->evento.dataEvento.minuto, raiz->evento.codigo);
    } else if (comp < 0) {
        consultarEvento(raiz->esq, data);
    } else {
        consultarEvento(raiz->dir, data);
    }
}

Node* encontrarMinimo(Node* raiz) {
    while (raiz->esq != NULL) {
        raiz = raiz->esq;
    }
    return raiz;
}

Node* removerEvento(Node* raiz, int codigo) {
    if (raiz == NULL) {
        printf("Evento não encontrado.\n");
        return NULL; // Se a raiz for nula, simplesmente retorna nula
    }

    // Se o código a ser removido é menor que o código do nó atual
    if (codigo < raiz->evento.codigo) {
        raiz->esq = removerEvento(raiz->esq, codigo);
    }
    // Se o código a ser removido é maior que o código do nó atual
    else if (codigo > raiz->evento.codigo) {
        raiz->dir = removerEvento(raiz->dir, codigo);
    }
    // Encontrou o nó a ser removido
    else {
        // Caso 1: Nó sem filhos
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            return NULL; // Retorna nulo para o nó pai
        }
        // Caso 2: Nó com apenas um filho (direito)
        if (raiz->esq == NULL) {
            Node* temp = raiz->dir;
            free(raiz);
            return temp; // Retorna o filho para o nó pai
        }
        // Caso 2: Nó com apenas um filho (esquerdo)
        if (raiz->dir == NULL) {
            Node* temp = raiz->esq;
            free(raiz);
            return temp; // Retorna o filho para o nó pai
        }
        // Caso 3: Nó com dois filhos
        //Node* temp = encontrarMinimo(raiz->dir); // Encontra o menor nó na subárvore direita
        //raiz->evento = temp->evento; // Copia os dados do menor nó para o nó a ser removido
        //raiz->dir = removerEvento(raiz->dir, temp->evento.codigo); // Remove o menor nó encontrado
    }
    return raiz; // Retorna a raiz atualizada da árvore
}

// Função para criar e preencher um novo evento
Evento criarEventoManual() {
    Evento e;

    // Leitura do código do evento
    do {
        printf("Digite o código do evento: ");
        scanf("%d", &e.codigo);
    } while (e.codigo <= 0);

    // Leitura da data do evento
    do {
        printf("Digite a data do evento (dia mes ano hora minuto): ");
        scanf("%d %d %d %d %d", &e.dataEvento.dia, &e.dataEvento.mes, &e.dataEvento.ano, &e.dataEvento.hora, &e.dataEvento.minuto);
        
        // Imprimindo os valores lidos para verificação
        printf("Valores lidos: %d/%d/%d %d:%d\n", e.dataEvento.dia, e.dataEvento.mes, e.dataEvento.ano, e.dataEvento.hora, e.dataEvento.minuto);

        if (!validarData(e.dataEvento)) {
            printf("Erro: Data inválida. Tente novamente.\n");
        }
    } while (!validarData(e.dataEvento));

    // Leitura da duração do evento
    do {
        printf("Digite a duração do evento (em horas): ");
        scanf("%f", &e.duracao);
        if (!validarDuracao(e.duracao)) {
            printf("Erro: Duração inválida. Tente novamente.\n");
        }
    } while (!validarDuracao(e.duracao));

    // Leitura da descrição do evento
    printf("Digite a descrição do evento: ");
    scanf(" %[^\n]", e.descricao);

    return e;
}

