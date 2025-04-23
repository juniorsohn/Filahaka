// queue_pri.h
#ifndef QUEUE_PRI_H
#define QUEUE_PRI_H

#include "queue_pub.h"

// Nó da fila: armazena int, float ou string
typedef struct no {
    union {
        int intValue;
        float floatValue;
        char *stringValue;
    } dado;
    struct no *proximo;
} No;

// Descritor da fila genérica homogênea
// type: 0=int, 1=float, 2=string, 99=undefined
// sizedata preservado para compatibilidade
typedef struct Queue {
    No *head;
    No *tail;
    int tamanho;
    int capacidade;
    int type;
    int sizedata;
} Queue;

#endif // QUEUE_PRI_H