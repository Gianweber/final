#ifndef EVENTOS_H
#define EVENTOS_H

struct _data {
    int dia;
    int mes;
    int ano;
    int hora;
    int minuto;
};
typedef struct _data Data;

struct _evento {
    int codigo;
    Data dataEvento;
    float duracao;
    char descricao[100];
};
typedef struct _evento Evento;

typedef struct node {
    Evento evento;
    struct node *esq;
    struct node *dir;
    struct node *pai;
} Node;

// Funções de validação
int validarData(Data data);
int validarDuracao(float duracao);

// Funções da árvore
int comparaData(Data d1, Data d2);
void inicializaAvl(Node** node, Evento evento);
void inserirEvento(Node** raiz, Evento novoEvento);
Node* buscarEventoPorCodigo(Node* raiz, int codigo);
void atualizarEvento(Node* raiz, int codigo);
void exibirEventos(Node* raiz);
Node* removerEvento(Node* raiz, int codigo);
Node* encontraMinimo(Node* raiz);
void consultarEvento(Node* raiz, Data data);

// Funções de criação
Evento criarEventoManual();

#endif
