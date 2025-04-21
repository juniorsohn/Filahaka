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
    No *aux=NULL;

    if ((*pf)->capacidade >= (*pf)->tamanho){
        printf("Fila cheia!\n");
        return FAIL;
    }        
    novo = malloc(sizeof(novo));
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

        if ((*pf)->head == NULL){
            (*pf)->head = novo;
            (*pf)->tail = novo;
            novo->proximo = novo;
        }
        else{
            aux = (*pf)->head;
            aux->proximo = novo;
            (*pf)->head = novo;            
        }
        novo->proximo = (*pf)->tail;            
        (*pf)->capacidade+= 1;    
    }
    else{
        return FAIL;
    }
    return SUCCESS;
}




// Desenfilera um elemento
int unqueue(ppQueue pf){
    No *remover=NULL;
    No *aux=NULL;
    
    if ((*pf)->capacidade == 0){
        return FAIL;
    }
    
    if((*pf)->tail){
        remover = (*pf)->tail;
        switch ((*pf)->type) {
            case 0:
                printf("Elemento retirado: %d\n", remover->dado.intValue);
                break;
            case 1:
                printf("Elemento retirado f: %.2f\n", remover->dado.floatValue);
                break;
            case 2:
                printf("Elemento retirado: %s\n", remover->dado.stringValue); 
                break;
            default: 
                printf("Sem elemento na pilha\n"); 
        }   

        (*pf)->tail = remover->proximo;
        (*pf)->capacidade-= 1;     
        if ((*pf)->capacidade == 1){   
            aux = (*pf)->head;
            aux->proximo = (*pf)->tail;
        }
        free(remover);
        if ((*pf)->capacidade == 0){
            (*pf)->type = 99;
            (*pf)->capacidade = 0;
            (*pf)->head = NULL;
            (*pf)->tail = NULL;
        }
    }
    else{
        return FAIL;
    }
    return SUCCESS;
}





// Remove todos os dados da fila mantendo o descritor alocado.
int cleanQueue(ppQueue pf){
    No *remover=NULL;
    
    if ((*pf)->capacidade = 0){
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
