#include <stdlib.h>

#include <iostream>
#include <limits>

typedef struct no {
    int dado;
    struct no *anterior, *proximo;
} tListaDupla;

using namespace std;

tListaDupla *newNode(int num);                                         // retorna o ponteiro de um nó novo
int exit(tListaDupla **head, tListaDupla **tail);                      // finaliza o programa, destruindo antes a lista
bool isEmpty(tListaDupla *head);                                       // retorna true se a lista estiver vazia
bool createUnitList(tListaDupla **head, tListaDupla **tail, int num);  // cria uma lista unitária com o numero passado
bool addNumber(tListaDupla **head, tListaDupla **tail, int num);       // adiciona o numero na lista em ordem crescente
bool rmvNumber(tListaDupla **head, tListaDupla **tail, int num);       // remove o numero da lista, sem alterar a ordem
bool isUnprecedented(tListaDupla **head, int num);                     // retorna true se o numero não estiver presente na lista
void shellClear();                                                     // limpa o terminal
void printMenu();                                                      // imprime o menu
void printList(tListaDupla **head);                                    // imprime a lista em ordem crescente
void printDecreasingOrder(tListaDupla **head);                         // imprime a lista em ordem decrescente

int main() {
    tListaDupla *headPointer = NULL, *tailPointer = NULL;
    int opt = -2, num;

    cout << "[1] para verificar se a lista está vazia." << endl;
    cout << "[2] para criar uma lista unitária." << endl;
    cout << "[3] para adicionar um número inédito." << endl;
    cout << "[4] para remover um número." << endl;
    cout << "[5] para pesquisar um número na lista." << endl;
    cout << "[6] para listar em ordem crescente." << endl;
    cout << "[7] para listar em ordem decrescente." << endl;
    cout << "[8] para exibir esse menu novamente." << endl;
    cout << "[9] para limpar o terminal." << endl;
    cout << "[0] para finalizar o programa." << endl;
    cout << "Aperte [ENTER] para continuar." << endl;
    getchar();
    shellClear();

    // cria uma lista padrão de 1 até 10, usada para testes
    // createUnitList(&headPointer, &tailPointer, 1);
    // for (int i = 2; i <= 10; i++) {
    //     addNumber(&headPointer, &tailPointer, i);
    // }

    while (opt != -1) {
        cout << " - ";
        cin >> opt;
        switch (opt) {
            case 1: {
                if (isEmpty(headPointer)) {
                    cout << "Essa lista está vazia.\n"
                         << endl;
                } else {
                    cout << "Essa lista não está vazia." << endl;
                }
                break;
            }
            case 2: {
                cout << "Diga um número para criar uma lista unitária: ";
                cin >> num;
                if (createUnitList(&headPointer, &tailPointer, num)) {
                    cout << "Lista criada com sucesso!" << endl;
                } else {
                    cout << "A lista já contém elementos." << endl;
                }
                break;
            }
            case 3: {
                cout << "Diga um número inédito na lista para ser adicionado: ";
                cin >> num;
                addNumber(&headPointer, &tailPointer, num);
                break;
            }
            case 4: {
                cout << "Digite um número existente na lista para ser removido: ";
                cin >> num;
                rmvNumber(&headPointer, &tailPointer, num);
                break;
            }
            case 5: {
                cout << "Digite um número para pesquisa-lo na lista: ";
                cin >> num;
                if (isUnprecedented(&headPointer, num)) {
                    cout << "O número não existe na lista." << endl;
                } else {
                    cout << "O número " << num << " foi encontrado." << endl;
                }
                break;
            }
            case 6: {
                printList(&headPointer);
                break;
            }
            case 7: {
                printDecreasingOrder(&tailPointer);
                break;
            }
            case 8: {
                printMenu();
                break;
            }
            case 9: {
                shellClear();
                break;
            }
            case 0: {
                cout << "Quantidade de nos liberados: " << exit(&headPointer, &tailPointer) << endl;
                opt = -1;
                break;
            }
        }
    }

    return 0;
}

// checa se o ponteiro headPointer é nulo, o que significa que a lista está vazia
bool isEmpty(tListaDupla *head) {
    if (head == NULL) {
        return true;
    }
    return false;
}

// cria um nó novo para a lista
tListaDupla *newNode(int num) {
    // aloca memória para o nó usando a função malloc
    tListaDupla *node = (tListaDupla *)malloc(sizeof(tListaDupla));

    // inicia o campo `dado` com o valor passado e os ponteiro `anterior` e `proximo` como nulos
    node->dado = num;
    node->anterior = NULL;
    node->proximo = NULL;

    return node;
}

// cria um novo nó e com o valor passado e aponta ambos headPointer e tailPointer para o mesmo
bool createUnitList(tListaDupla **head, tListaDupla **tail, int num) {
    tListaDupla *node = newNode(num);
    if (isEmpty(*head)) {
        (*head) = node;
        (*tail) = node;
        return true;
    }
    // se a lista não está vazia, ele retorna false e não cria uma lista nova
    return false;
}

// adiciona um numero inédito na lista, em ordem crescente e mantendo a lista duplamente encadeada
bool addNumber(tListaDupla **head, tListaDupla **tail, int num) {
    if (isEmpty(*head)) {
        cout << "Essa lista está vazia." << endl;
        return false;
    } else {
        tListaDupla *node = newNode(num);
        tListaDupla *current = *tail;

        // adiciona o numero no final da lista, se ele for maior do que todos
        if (node->dado > current->dado && isUnprecedented(head, num)) {
            node->anterior = current;
            current->proximo = node;
            *tail = node;
            return true;
        }

        current = *head;

        // adiciona o numero no inicio da lista, se ele for menor do que todos
        if (node->dado < current->dado && isUnprecedented(head, num)) {
            node->proximo = current;
            current->anterior = node;
            *head = node;
            return true;
        }

        // percorre a lista, procurando a posição certa para adicionar o numero
        while (!isEmpty(current->proximo)) {
            if (node->dado > current->dado && node->dado < (current->proximo)->dado && isUnprecedented(head, num)) {
                node->proximo = current->proximo;
                node->anterior = current;

                (current->proximo)->anterior = node;
                current->proximo = node;
                return true;
            }
            current = current->proximo;
        }
    }
    return false;
}

// remove um numero da lista, mantendo a ordem e a mantendo duplamente encadeada
bool rmvNumber(tListaDupla **head, tListaDupla **tail, int num) {
    if (!isEmpty(*head) && !isUnprecedented(head, num)) {
        tListaDupla *current = *tail;

        // confere se o numero está no final da lista, e o remove caso sim
        if (current->dado == num) {
            (current->anterior)->proximo = NULL;
            *tail = current->anterior;
            free(current);
            // destrói o nó que não está mais na lista, assim evitando memory leaking
            return true;
        }

        current = *head;

        // confere se o numero está no inicio da lista, e o remove caso sim
        if (current->dado == num) {
            (current->proximo)->anterior = NULL;
            *head = current->proximo;
            free(current);
            return true;
        }

        // caso ambos os casos anteriores não ocorram, percorre a lista, a fim
        // de encontrar o numero e o remover
        while (!isEmpty(current->proximo)) {
            if (current->dado == num) {
                (current->proximo)->anterior = current->anterior;
                (current->anterior)->proximo = current->proximo;
                free(current);
                return true;
            }
            current = current->proximo;
        }

        return false;
    } else {
        cout << "O número digitado não foi encontrado na lista." << endl;
        return false;
    }
}

// checa se a lista contém um nó com o valor passado, retorna false se tiver e true caso contrário
bool isUnprecedented(tListaDupla **lista, int num) {
    if (!isEmpty(*lista)) {
        tListaDupla *current = *lista;

        while (!isEmpty(current->proximo)) {
            if (current->dado == num) {
                return false;
            }
            current = current->proximo;
        }
        if (current->dado == num) {
            return false;
        }

        return true;
    }
    return true;
}

// limpa o terminal
void shellClear() {
#if _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// imprime no terminal as opções disponíveis para o usuário
void printMenu() {
    cout << "[1] para verificar se a lista está vazia." << endl;
    cout << "[2] para criar uma lista unitária." << endl;
    cout << "[3] para adicionar um número inédito." << endl;
    cout << "[4] para remover um número." << endl;
    cout << "[5] para pesquisar um número na lista." << endl;
    cout << "[6] para listar em ordem crescente." << endl;
    cout << "[7] para listar em ordem decrescente." << endl;
    cout << "[8] para exibir esse menu novamente." << endl;
    cout << "[9] para limpar o terminal." << endl;
    cout << "[0] para finalizar o programa." << endl;
    cout << "Aperte [ENTER] para continuar." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // sistema para limpar o buffer de entrada da aplicação
    cin.clear();
    getchar();  // função para simular uma espera do usuário, prosseguindo assim que ele apertar a tecla enter
    shellClear();
}

// imprime os valores da lista em ordem crescente
void printList(tListaDupla **head) {
    if (!isEmpty(*head)) {
        tListaDupla *current = *head;

        while (!isEmpty(current->proximo)) {
            cout << current->dado << " |";
            current = current->proximo;
        }
        cout << current->dado << endl;
    }
}

// imprime os valores da lista em ordem decrescente
void printDecreasingOrder(tListaDupla **tail) {
    if (!isEmpty(*tail)) {
        tListaDupla *current = *tail;

        while (!isEmpty(current->anterior)) {
            cout << current->dado << " |";
            current = current->anterior;
        }
        cout << current->dado << endl;
    }
}

// destrói a lista, usando a função free para desalocar a memória dos nós
int exit(tListaDupla **head, tListaDupla **tail) {
    int count = 0;
    tListaDupla *current = *head;
    while (current != NULL) {
        tListaDupla *temp = current;
        current = current->proximo;
        free(temp);
        count++;
    }

    // declara ambos headPointer e tailPointer como nulos
    *head = NULL;
    *tail = NULL;

    // retorna um inteiro que é o total de nós destruídos
    return count;
}