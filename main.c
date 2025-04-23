// main.h
#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue_pub.h"

#endif // MAIN_H


// main.c
#include "main.h"

int main(void) {
    pQueue Q = NULL;
    char buffer[256];
    char *endptr;
    long cap;

    // 1) Lê e valida a capacidade
    printf("Informe a capacidade da fila:\n");
    if (!fgets(buffer, sizeof(buffer), stdin)) return 1;
    buffer[strcspn(buffer, "\n")] = '\0';
    cap = strtol(buffer, &endptr, 10);
    if (*endptr != '\0' || cap <= 0) {
        fprintf(stderr, "Capacidade inválida.\n");
        return 1;
    }

    // 2) Cria fila (tipo genérico homogêneo via string)
    if (cQueue(&Q, (int)cap, sizeof(char *)) != SUCCESS) {
        fprintf(stderr, "Erro ao criar fila.\n");
        return 1;
    }

    // 3) Enfileira elementos
    printf("Digite %ld elementos, um por linha:\n", cap);
    for (int i = 0; i < cap; ) {
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            fprintf(stderr, "Erro ao ler a entrada.\n");
            dQueue(&Q);
            return 1;
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        if (queue(Q, buffer) == SUCCESS) {
            i++;
        }
        // se FAIL, mensagem já foi impressa internamente
    }

    // 4) Desenfileira e imprime
    printf("\nDesenfileirando elementos:\n");
    for (int i = 0; i < cap; i++) {
        char *out;
        if (unqueue(Q, &out) == SUCCESS) {
            printf("%s\n", out);
            free(out);
        }
    }

    // 5) Destrói fila
    if (dQueue(&Q) != SUCCESS) {
        fprintf(stderr, "Erro ao destruir fila.\n");
        return 1;
    }
    printf("Fila destruída com sucesso.\n");
    return 0;
}
