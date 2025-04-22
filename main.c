/* Arquivo EXEMQLO DE AQlicacao */
// MODIFIQUEM-o, CORRIJAM-o!
#include "main.h"

int main() {
    
    pQueue Q = NULL;
    int ret=0;
    int rlines=0; 
    char buffer[100]; 
    int leitura=0;
    char *ptr;
    ptr = buffer;  
  
    printf("Digite o numero de elementos/capacidade da fila!\n");
    if (!fscanf(stdin, "%i", &rlines)) {
        return 1;
    }
    getchar();
    ret = cQueue(&Q,rlines);
    fflush(stdin);


    printf("Digite %d dados genericos (inteiros, float ou string), um por linha:\n", rlines);
    while (leitura < rlines) {
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            printf("Erro ao ler a entrada.\n");
            return 1;
        }
        if (strlen(buffer) == 0){
            return 1;
        }
        ret = queue(&Q,ptr);
        //printf("Push na fila %d\n", ret);
        if (ret == 0){
            leitura++;
        }        

    }    
    
    ret = head(Q);    
    ret = tail(Q);    
    ret = sizeQueue(Q);      
    
    // TESTES DIVERSOS
    printf("Force mais um elemento:\n", rlines);
    if (!fgets(buffer, sizeof(buffer), stdin)) {
        printf("Erro ao ler a entrada.\n");
        return 1;
    }
    if (strlen(buffer) == 0){
        return 1;
    }
    ret = queue(&Q,ptr);

    printf("Retirado um elemento\n", rlines);
    ret = unqueue(&Q);

    printf("Como ficou:\n", rlines);
    ret = head(Q);    
    ret = tail(Q);    
    ret = sizeQueue(Q); 

    printf("Force mais um elemento:\n", rlines);
    if (!fgets(buffer, sizeof(buffer), stdin)) {
        printf("Erro ao ler a entrada.\n");
        return 1;
    }
    if (strlen(buffer) == 0){
        return 1;
    }
    ret = queue(&Q,ptr);


    printf("Como ficou:\n");
    ret = head(Q);    
    ret = tail(Q);    
    ret = sizeQueue(Q); 

    printf("Fila toda:\n");
    imprime(Q);
    ///FIM TESTES

    for (int i=0; i<rlines;i++) {
        ret = unqueue(&Q);
        ret = head(Q);    
        ret = tail(Q);    
        ret = sizeQueue(Q); 
    }
    printf("Retirada da fila completado\n");
    ret = dQueue(&Q);
    printf("Flush na fila %d\n", ret);
  
    return 0;
}