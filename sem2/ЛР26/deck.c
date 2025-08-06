#include "deck.h"

void initDeck(StaticDeck *D) {
    D->front = 0;
    D->rear = -1;
    D->size = 0;
}

int size(StaticDeck *D) {
    return D->size;
}

bool empty(StaticDeck *D) {
    return size(D) == 0;
}

bool full(StaticDeck *D) {
    return D->size >= MAX_SIZE;
}

void pushFront(StaticDeck *D, key_type key, value_type value) {
    if (full(D)) {
        printf("Ошибка: дек переполнен\n");
        return;
    }
    D->front = (D->front - 1 + MAX_SIZE) % MAX_SIZE;
    D->data[D->front].key = key;
    D->data[D->front].value = value;
    if (D->rear == -1) D->rear = D->front;
    D->size++;
}

void pushBack(StaticDeck *D, key_type key, value_type value) {
    if (full(D)) {
        printf("Ошибка: дек переполнен\n");
        return;
    }
    D->rear = (D->rear + 1) % MAX_SIZE;
    D->data[D->rear].key = key;
    D->data[D->rear].value = value;
    if (D->size == 0) D->front = D->rear;
    D->size++;
}

value_type popFront(StaticDeck *D) {
    if (empty(D)) {
        printf("Дек пуст!\n");
        return -1;
    }
    value_type val = D->data[D->front].value;
    D->front = (D->front + 1) % MAX_SIZE;
    D->size--;
    if (D->size == 0) {
        D->front = 0;
        D->rear = -1;
    }
    return val;
}

value_type popBack(StaticDeck *D) {
    if (empty(D)) {
        printf("Дек пуст!\n");
        return -1;
    }
    value_type val = D->data[D->rear].value;
    D->rear = (D->rear - 1 + MAX_SIZE) % MAX_SIZE;
    D->size--;
    if (D->size == 0) {
        D->front = 0;
        D->rear = -1;
    }
    return val;
}

value_type topFront(StaticDeck *D) {
    if (empty(D)) {
        printf("Дек пуст!\n");
        return -1;
    }
    return D->data[D->front].value;
}

value_type topBack(StaticDeck *D) {
    if (empty(D)) {
        printf("Дек пуст!\n");
        return -1;
    }
    return D->data[D->rear].value;
}

void clearDeck(StaticDeck *D) {
    D->front = 0;
    D->rear = -1;
    D->size = 0;
}

void printDeck(StaticDeck *D) {
    if (empty(D)) {
        printf("Дек пуст!\n");
        return;
    }
    printf("Дек: ");
    int i = D->front;
    for (int count = 0; count < D->size; count++) {
        printf("[%d:%d] ", D->data[i].key, D->data[i].value);
        i = (i + 1) % MAX_SIZE;
    }
    printf("\n");
}

key_type frontKey(StaticDeck *D) {
    if (empty(D)) {
        printf("Дек пуст!\n");
        return -1;
    }
    return D->data[D->front].key;
}
