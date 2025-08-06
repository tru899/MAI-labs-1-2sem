#ifndef DECK_H
#define DECK_H

#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 10

typedef int key_type;
typedef int value_type;

typedef struct {
    key_type key;
    value_type value;
} KeyValuePair;

typedef struct {
    KeyValuePair data[MAX_SIZE];
    int front;
    int rear;
    int size;
} StaticDeck;

void initDeck(StaticDeck *D);
int size(StaticDeck *D);
bool empty(StaticDeck *D);
bool full(StaticDeck *D);
void pushFront(StaticDeck *D, key_type key, value_type value);
void pushBack(StaticDeck *D, key_type key, value_type value);
value_type popFront(StaticDeck *D);
value_type popBack(StaticDeck *D);
value_type topFront(StaticDeck *D);
value_type topBack(StaticDeck *D);
void clearDeck(StaticDeck *D);
void printDeck(StaticDeck *D);
key_type frontKey(StaticDeck *D);

#endif
