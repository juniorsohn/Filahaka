// queue.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue_pub.h"
#include "queue_pri.h"

// Construtor: tamanho em elementos, sizedata indica sizeof(tipo)
int cQueue(ppQueue pf, int size, int sizedata) {
    if (!pf || size <= 0 || sizedata <= 0)
        return FAIL;
    *pf = malloc(sizeof(Queue));
    if (!*pf) return FAIL;
    (*pf)->head      = NULL;
    (*pf)->tail      = NULL;
    (*pf)->tamanho   = size;
    (*pf)->capacidade= 0;
    (*pf)->type      = 99;
    (*pf)->sizedata  = sizedata;
    return SUCCESS;
}

// Destrutor: limpa nós e libera descritor
int dQueue(ppQueue pf) {
    if (!pf || !*pf) return FAIL;
    cleanQueue(*pf);
    free(*pf);
    *pf = NULL;
    return SUCCESS;
}

// Enfila um elemento genérico
int queue(pQueue f, void *element) {
    if (!f || !element || f->capacidade >= f->tamanho)
        return FAIL;
    // Detecta tipo na primeira inserção via sizedata
    if (f->type == 99) {
        if (f->sizedata == sizeof(int)) f->type = 0;
        else if (f->sizedata == sizeof(float)) f->type = 1;
        else if (f->sizedata == sizeof(char *)) f->type = 2;
        else return FAIL;
    }
    // Aloca nó
    No *node = malloc(sizeof(No));
    if (!node) return FAIL;
    // Copia dado
    if (f->type == 0) {
        node->dado.intValue   = *(int *)element;
    } else if (f->type == 1) {
        node->dado.floatValue = *(float *)element;
    } else {
        char *str = *(char **)element;
        node->dado.stringValue= malloc(strlen(str)+1);
        if (!node->dado.stringValue) { free(node); return FAIL; }
        strcpy(node->dado.stringValue, str);
    }
    // Insere circularmente
    if (f->capacidade == 0) {
        node->proximo = node;
        f->head = f->tail = node;
    } else {
        node->proximo      = f->tail;
        f->head->proximo   = node;
        f->head            = node;
    }
    f->capacidade++;
    return SUCCESS;
}

// Desenfila um elemento genérico
int unqueue(pQueue f, void *element) {
    if (!f || !element || f->capacidade == 0)
        return FAIL;
    No *rem = f->tail;
    // Devolve valor
    if (f->type == 0) {
        *(int *)element     = rem->dado.intValue;
    } else if (f->type == 1) {
        *(float *)element   = rem->dado.floatValue;
    } else {
        *(char **)element   = rem->dado.stringValue;
    }
    // Ajusta ponteiros
    if (f->capacidade == 1) {
        f->head = f->tail = NULL;
    } else {
        f->tail = rem->proximo;
    }
    f->capacidade--;
    if (f->capacidade == 0) f->type = 99;
    free(rem);
    return SUCCESS;
}

// Limpa todos os dados (main mantém descritor)
int cleanQueue(pQueue f) {
    if (!f) return FAIL;
    while (f->capacidade > 0) {
        char *tmp;
        if (f->type == 2) {
            unqueue(f, &tmp);
            free(tmp);
        } else {
            int i;
            float fl;
            if (f->type == 0) unqueue(f, &i);
            else              unqueue(f, &fl);
        }
    }
    f->type = 99;
    return SUCCESS;
}

// Retorna vagas livres
int sizeQueue(pQueue f) {
    if (!f) return FAIL;
    return f->tamanho - f->capacidade;
}
