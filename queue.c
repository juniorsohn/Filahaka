#include "queue_pri.h"
#include "queue_pub.h"



// "Construtor": aloca memória e inicializa as variáveis
int cQueue(ppQueue pf, int size){
    *pf = (pQueue)malloc(sizeof(struct Queue));
    (*pf)->head = NULL;
    (*pf)->tail = NULL;
    (*pf)->tamanho = size;
    (*pf)->capacidade = 0;
    (*pf)->type = 99;
    return SUCCESS;
}

// "Destrutor": libera memória da estrutura
int dQueue(ppQueue pf){
    No *remover=NULL;
    if ((*pf)->capacidade == 0){
        (*pf)->type = 99;
        (*pf)->capacidade = 0;
        (*pf)->head = NULL;
        (*pf)->tail = NULL;

        free(*pf);
        (*pf) = NULL;
        return SUCCESS;
    }

    if((*pf)->capacidade > 0){
        while ((*pf)->tail){            
            remover = (*pf)->tail;
            switch ((*pf)->type) {
                case 0:
                    printf("Elemento limpado: %d\n", remover->dado.intValue);
                    break;
                case 1:
                    printf("Elemento limpado: %.2f\n", remover->dado.floatValue);
                    break;
                case 2:
                    printf("Elemento limpado: %s\n", remover->dado.stringValue);
                    free(remover->dado.stringValue); 
                    break;
                default: 
                    printf("Sem elemento na pilha\n"); 
            }               
            (*pf)->tail = remover->proximo;
            (*pf)->capacidade-= 1;        
            free(remover);
        }
        

    }

    (*pf)->type = 99;
    (*pf)->capacidade = 0;
    (*pf)->head = NULL;
    (*pf)->tail = NULL;

    free(*pf);
    (*pf) = NULL;

    return SUCCESS;
}




// **** "Operações de manipulação" ****
// Enfiera um elemento 
int queue(ppQueue pf, char *element){
    char *testeInt=NULL;
    char *testeFloat=NULL;
    long ehnumero;
    float ehfloat;
    No *novo=NULL;

    if ((*pf)->capacidade >= (*pf)->tamanho){
        printf("Fila cheia!\n");
        return FAIL;
    }        
    novo = malloc(sizeof(No));
    if(novo){      
        ehnumero = strtol(element, &testeInt, 10);
        if (*testeInt == '\0' || *testeInt == '\n') {
            if ((*pf)->type==99){
                (*pf)->type=0;
            }
            else{
                if ((*pf)->type==1 || (*pf)->type==2){
                    printf("\nElemento nao permitido. Informe outro elemento:\n");
                    return FAIL;
                }
            }            
            novo->dado.intValue = (int)ehnumero;
        }
        else {
            ehfloat = strtof(element, &testeFloat);
            if (*testeFloat == '\0' || *testeFloat == '\n'){
                if ((*pf)->type==99){
                    (*pf)->type=1;
                }
                else{
                    if ((*pf)->type==0 || (*pf)->type==2){
                        printf("\nElemento nao permitido. Informe outro elemento:\n");
                        return FAIL;
                    }
                }
                novo->dado.floatValue = ehfloat;
            }
            else{
                if ((*pf)->type==99 || (*pf)->type==2) {
                    if ((*pf)->type==99){
                        (*pf)->type=2;
                    }
                    novo->dado.stringValue = malloc(strlen(element) + 1);
                    if (!novo->dado.stringValue) {
                        printf("Erro de alocacao.\n");
                        return FAIL;
                    }
                    strcpy(novo->dado.stringValue,element);
                    novo->dado.stringValue[strcspn(novo->dado.stringValue, "\n")] = '\0';
                }
                else{
                    printf("\nElemento nao permitido. Informe outro elemento:\n");
                    return FAIL;
                }                
            }
        }

    if ((*pf)->head == NULL) {
            (*pf)->head = novo;
            (*pf)->tail = novo;
            novo->proximo = novo;
        }
        else {
            // insere depois do head, aponta novo->proximo para tail
            novo->proximo        = (*pf)->tail;          // define próximo do novo
            (*pf)->head->proximo = novo;                 // antigo head aponta pro novo
            (*pf)->head         = novo;                  // atualiza head
        }
        (*pf)->capacidade += 1;
        return SUCCESS;
    }else{
        return FAIL;
    }
}



// Desenfilera um elemento
// Desenfilera um elemento
int unqueue(ppQueue pf){
    No *remover=NULL;
    
    // Verifica se a fila está vazia ou se o ponteiro da fila é nulo
    if ((*pf)->capacidade == 0 || pf == NULL){
        return FAIL;
    }
    
    if((*pf)->tail){
        remover = (*pf)->tail;
        
        switch ((*pf)->type) {
            case 0:
                printf("Elemento retirado: %d\n", remover->dado.intValue);
                break;
            case 1:
                printf("Elemento retirado: %.2f\n", remover->dado.floatValue);
                break;
            case 2:
                printf("Elemento retirado: %s\n", remover->dado.stringValue);
                free(remover->dado.stringValue); // Liberar string alocada
                break;
            default: 
                printf("Elemento inválido\n"); 
        }

        // Caso a fila tenha apenas um elemento
        if ((*pf)->capacidade == 1) {
            (*pf)->head = NULL; // Resetando a cabeça
            (*pf)->tail = NULL; // Resetando o tail
            (*pf)->type = 99;   // Resetando o tipo
            (*pf)->capacidade = 0; // Resetando a capacidade
            free(remover); // Liberando o nó
            return SUCCESS;  // Evita continuar após liberar o último nó
        }

        // Atualizar tail para o próximo elemento
        (*pf)->tail = remover->proximo;
        (*pf)->capacidade -= 1;

        free(remover); // Liberando a memória do nó removido

        // Se a fila estiver vazia após a remoção, resetando as variáveis
        if ((*pf)->capacidade == 0) {
            (*pf)->type = 99;
            (*pf)->head = NULL;
            (*pf)->tail = NULL;
        }
    }
    else {
        return FAIL;
    }
    return SUCCESS;
}






// Remove todos os dados da fila mantendo o descritor alocado.
int cleanQueue(ppQueue pf){
    No *remover=NULL;
    
    if ((*pf)->capacidade == 0){
        return SUCCESS;
    }

    if((*pf)->capacidade > 0){
        while ((*pf)->tail){            
            remover = (*pf)->tail;
            switch ((*pf)->type) {
                case 0:
                    printf("Elemento limpado: %d\n", remover->dado.intValue);
                    break;
                case 1:
                    printf("Elemento limpado: %.2f\n", remover->dado.floatValue);
                    break;
                case 2:
                    printf("Elemento limpado: %s\n", remover->dado.stringValue); 
                    break;
                default: 
                    printf("Sem elemento na pilha\n"); 
            }               
            (*pf)->tail = remover->proximo;
            (*pf)->capacidade-= 1;        
            free(remover);
        }
        

    }
    return SUCCESS;

}

// **** "Operações de acesso" ****
// Retorna o máximo da fila
int sizeQueue(pQueue f){
    return (f->tamanho - f->capacidade);
}


int head(pQueue f){
    No *leitura=NULL;
    leitura = f->head;
    if (!leitura){
        return FAIL;
    }
    else{
        switch (f->type) {
            case 0:
                printf("Elemento do head: %d\n", leitura->dado.intValue);
                break;
            case 1:
                printf("Elemento do head: %.2f\n", leitura->dado.floatValue);
                break;
            case 2:
                printf("Elemento do head: %s\n", leitura->dado.stringValue); 
                break;
            default: 
                printf("Sem elemento na fila\n"); 
        }   
        return SUCCESS;
    }

}

int tail(pQueue f){
    No *leitura=NULL;
    leitura = f->tail;
    if (!leitura){
        return FAIL;
    }
    else{
        switch (f->type) {
            case 0:
                printf("Elemento do tail: %d\n", leitura->dado.intValue);
                break;
            case 1:
                printf("Elemento do tail: %.2f\n", leitura->dado.floatValue);
                break;
            case 2:
                printf("Elemento do tail: %s\n", leitura->dado.stringValue); 
                break;
            default: 
                printf("Sem elemento na fila\n"); 
        }   
        return SUCCESS;
    }

}

void imprime(pQueue f){
    No *leitura=NULL;
    leitura = f->tail; 
    do{       
        if (!leitura){
            return;
        }
        else{        
            switch (f->type) {
                case 0:
                    printf("Elemento: %d\n", leitura->dado.intValue);
                    break;
                case 1:
                    printf("Elemento: %.2f\n", leitura->dado.floatValue);
                    break;
                case 2:
                    printf("Elemento: %s\n", leitura->dado.stringValue); 
                    break;
                default: 
                    printf("Sem elemento na fila\n"); 
            }   
            leitura = leitura->proximo;        
        }
    } while(f->tail != leitura);


    return;
}
