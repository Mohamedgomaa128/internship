#include <stdio.h>
#include <stdlib.h>
typedef enum TypeTag {
    ADD,
    SUB,
    MUL,
    DIV
} TypeTag;


typedef struct Node {
    enum TypeTag type;
    int value;
} Node;


Node* makeFunc(TypeTag type) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->type = type;
    return newNode;
}

int calc(Node* node) {
    if (node->type == ADD) {
        return node->value;
    } else if (node->type == SUB) {
        return -node->value;
    } else if (node->type == MUL) {
        return node->value;
    } else if (node->type == DIV) {
        return node->value;
    } else {
        return 0;
    }
}

Node* fibonacci(int n) {
    Node** fibArray = (Node**)malloc((n + 1) * sizeof(Node*));
    fibArray[0] = makeFunc(ADD);
    fibArray[0]->value = 0;
    fibArray[1] = makeFunc(ADD);
    fibArray[1]->value = 1;

    for (int i = 2; i <= n; i++) {
        fibArray[i] = makeFunc(ADD);
        fibArray[i]->value = calc(fibArray[i - 1]) + calc(fibArray[i - 2]);
    }

    Node* fibo = fibArray[n];
    free(fibArray);
    return fibo;
}

int main() {
    Node* add = makeFunc(ADD);
    add->value = 10 + 6;

    Node* mul = makeFunc(MUL);
    mul->value = 5 * 4;

    Node* sub = makeFunc(SUB);
    sub->value = calc(mul) - calc(add);

    Node* fibo = fibonacci(calc(sub));

    printf("add: %d\n", calc(add));
    printf("mul: %d\n", calc(mul));
    printf("sub: %d\n", calc(sub));
    printf("fibo: %d\n", calc(fibo));

    free(add);
    free(mul);
    free(sub);
    free(fibo);

    return 0;
}
