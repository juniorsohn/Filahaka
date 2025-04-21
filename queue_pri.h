#ifndef QUEUE_PRI_H
#define QUEUE_PRI_H


typedef struct no {
    //Dado *info;
    union {
        int intValue;
        float floatValue;
        char *stringValue;
    } dado;
    struct no *proximo;
} No;

typedef struct Queue 
{
    No *head;
    No *tail;
    int tamanho;
    int capacidade;
    int type; // 0 para int, 1 para float, 2 para string, 99 para não definido
} Queue;


#endif