#include <stdio.h>
#include <stdlib.h>

typedef struct no{   // Estrutura para fazer o encademento do Nos e salvar um valor inteiro
    int dado;
    struct tPilhaSimples *proximo;
}tPilhaSimples;


tPilhaSimples* CriaPilha(int novo){  // Função que cria Pilha
    tPilhaSimples *topo;

    topo = malloc(sizeof(tPilhaSimples));  // Faz a alocação de memoria 
    topo->dado = novo;
    topo->proximo = NULL;

    return topo;
}


int PilhaVazia(tPilhaSimples *topo){  // Função que verifica se a pilha está vazia
    if (topo == NULL) 
        return 1;
    else
        return 0;
}


tPilhaSimples* Empilha(tPilhaSimples *topo, int novo){  // Função que empilha os NOS
    tPilhaSimples *novoTopo;

    novoTopo = malloc(sizeof(tPilhaSimples));  // Alocando memória

    if(novoTopo == NULL)
        return topo;

    novoTopo->dado = novo;
    novoTopo->proximo = topo;

    return novoTopo;  // Retorna o nó que é o novo topo da pilha
}


tPilhaSimples* Desempilha(tPilhaSimples *topo, int *quantRemovidos){  // Função que desempilha um caso
    tPilhaSimples *novoTopo;

    if(topo == NULL){
        printf("Pilha Vazia!\n");
        return topo;
    }
    
    printf("\nValor Desempilhado: %d\n", topo->dado);

    novoTopo = topo->proximo;
    //*(quantRemovidos++);
    printf("\nQuantidade de intens removidos: %d\n", *quantRemovidos+= 1);  // Adiciona mais 1 a cada nó removido
    
    free(topo);   // Liberando memória
    return novoTopo;
} 


void mostraPilha(tPilhaSimples *topo){   // Função para imprimir toda pilha
    printf("\n------------------- PILHA -------------------\n");

    while(topo != NULL)
    {
        printf("%d\n", topo->dado);
        topo = topo->proximo;  // Topo recebe próximo para acessar os dados do próximo e o programa não ficar em loop infinito
    }
    printf("\n----------------- FIM PILHA -----------------\n");
}


int main(){
    int opc, valor, *quantRemovidos = 0;
    tPilhaSimples *topo = NULL;

    do {  // Lool infinito até o usuário digitar 0
        printf("\n1 - Teste Pilha Vazia\n2 - Cria Pilha\n3 - Empilhar\n4 - Desemplihar\n5 - Mostrar Elementos\n0 - Sair\n");
        scanf("%d", &opc);

        switch (opc)   // Switch case para controlar as opções do menu
        {
        case 1:
            if(PilhaVazia(topo) == 1)
                printf("Pilha Vazia!\n");
            else
                printf("A pilha contem elementos.\n");
            break;
        
        case 2:
            if(PilhaVazia(topo) == 1){
                printf("Digite um valor: \n");
                scanf("%d", &valor);
                topo = CriaPilha(valor);
            }
            break;

        case 3:
            printf("Digite um valor: \n");
            scanf("%d", &valor);
            topo  = Empilha(topo, valor);
            break;

        case 4:
            topo = Desempilha(topo, &quantRemovidos);
            break;  

        case 5:
            mostraPilha(topo);
            break;

        case 0:
            return 0;

        default:
            printf("Opcao invalida!");
            break;
        }
    } while(opc != 0);

    return 0;
}