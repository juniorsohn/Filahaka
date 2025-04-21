#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define FAIL 1

typedef struct Queue *pQueue, **ppQueue;

// "Construtor": aloca memória e inicializa as variáveis
int cQueue(ppQueue pf, int size);
// "Destrutor": libera memória da estrutura
int dQueue(ppQueue pf);

// **** "Operações de manipulação" ****
// Enfiera um elemento 
int queue(ppQueue pf, char *element);
// Desenfilera um elemento
int unqueue(ppQueue pf);
// Remove todos os dados da fila mantendo o descritor alocado.
int cleanQueue(ppQueue pf);

// **** "Operações de acesso" ****
// Retorna o máximo da fila
int sizeQueue(pQueue f);

int head(pQueue f);

int tail(pQueue f);

void imprime(pQueue f);

#endif